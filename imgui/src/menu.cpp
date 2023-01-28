#pragma once
#include "menu.h"
#include "capture_utils.h"
#include "icons.h"
#include "imguipp.h"
#include "settings.h"
#include "text_editor.h"
#include <string>
#include <vector>

hwnd2Mat::hwnd2Mat(HWND hwindow, float scale) {
    hwnd = hwindow;
    hwindowDC = GetDC(hwnd);
    hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
    SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

    RECT windowsize; // get the height and width of the screen
    GetClientRect(hwnd, &windowsize);

    srcheight = windowsize.bottom;
    srcwidth = windowsize.right;
    height = (int)(windowsize.bottom * scale);
    width = (int)(windowsize.right * scale);

    image.create(height, width, CV_8UC4);

    // create a bitmap
    hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
    bi.biSize = sizeof(BITMAPINFOHEADER); // http://msdn.microsoft.com/en-us/library/windows/window/dd183402%28v=vs.85%29.aspx
    bi.biWidth = width;
    bi.biHeight = -height; // this is the line that makes it draw upside down or not
    bi.biPlanes = 1;
    bi.biBitCount = 32;
    bi.biCompression = BI_RGB;
    bi.biSizeImage = 0;
    bi.biXPelsPerMeter = 0;
    bi.biYPelsPerMeter = 0;
    bi.biClrUsed = 0;
    bi.biClrImportant = 0;

    // use the previously created device context with the bitmap
    SelectObject(hwindowCompatibleDC, hbwindow);
    read();
};

void hwnd2Mat::read() {
    // copy from the window device context to the bitmap device context
    StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY); // change SRCCOPY to NOTSRCCOPY for wacky colors !
    GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, image.data, (BITMAPINFO*)&bi, DIB_RGB_COLORS);   // copy from hwindowCompatibleDC to hbwindow
};

hwnd2Mat::~hwnd2Mat() {
    // avoid memory leak
    DeleteObject(hbwindow);
    DeleteDC(hwindowCompatibleDC);
    ReleaseDC(hwnd, hwindowDC);
};

void Menu::Render() {
    ImGui::Columns(2);
    ImGui::SetColumnOffset(1, 230);

    {
        // Left side

        static ImVec4 active = imguipp::to_vec4(41, 40, 41, 255);
        static ImVec4 inactive = imguipp::to_vec4(31, 30, 31, 255);

        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 1 ? active : inactive);
        if (ImGui::Button("Camera Selection", ImVec2(230 - 15, 41))) {
            Settings::Tab = 0;
        }

        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Button, Settings::Tab == 2 ? active : inactive);
        if (ImGui::Button("Eye Tracking Backend", ImVec2(230 - 15, 41))) {
            Settings::Tab = 1;
        }

        ImGui::PopStyleColor(2);

        ImGui::SetCursorPosY(ImGui::GetWindowHeight() - 30);
        imguipp::center_text_ex("DeCuttMutt2", 230, 1, false);
    }

    ImGui::NextColumn();

    // Right side
    {
        if (Settings::Tab == 0) {
            static int device_counts = 0;
            static int device_enumeration_complete = false;
            static bool camera_started = false;
            static std::vector<std::string> items;

            if (!device_enumeration_complete) {
                cv::VideoCapture camera;

                while (true) {
                    if (!camera.open(device_counts)) {
                        device_enumeration_complete = true;
                        break;
                    }
                    std::string device_name = std::string("Device ") + std::to_string(device_counts);
                    items.push_back(device_name);
                    device_counts++;
                }
                camera.release();
            }

            static int selectedIndex = 0;
            static const char* current_item = items[selectedIndex].c_str();

            if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
            {
                for (int n = 0; n < items.size(); n++) {
                    bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(items[n].c_str(), is_selected)) {
                        current_item = items[n].c_str();
                        selectedIndex = n;
                    }

                    if (is_selected) {
                        ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                    }
                }
                ImGui::EndCombo();
            }

            if (ImGui::Button("Start Camera", ImVec2(200, 35))) {
                try {
                    start_webcam_capture(selectedIndex);
                } catch (std::exception& e) {
                    std::cout << e.what() << std::endl;
                }
            }

            if (ImGui::Button("Start Screen Capture", ImVec2(200, 35))) {
                start_screen_capture("./test001.avi");
            }
        }

        else if (Settings::Tab == 1) {
            static ImGuiTextFilter filter;
            static std::vector<std::string> resources =
                {
                    "_cfx_internal",
                    "mysql-async",
                    "essentialmode",
                    "async",
                    "es_extended"};

            filter.Draw(ICON_FA_SEARCH " Search", 240);
            ImGui::PushStyleColor(ImGuiCol_FrameBg, IM_COL32(0, 0, 0, 0));
            if (ImGui::ListBoxHeader("##ResourcesList", ImVec2(imguipp::getx(), imguipp::gety() - 35))) {
                for (const auto& resource : resources) {
                    if (filter.PassFilter(resource.c_str())) {
                        if (ImGui::TreeNode(resource.c_str()))
                            ImGui::TreePop();
                    }
                }
                ImGui::ListBoxFooter();
            }
            ImGui::PopStyleColor();
            if (ImGui::Button(ICON_FA_FOLDER_OPEN " Save to folder", ImVec2(205, 34))) {
            }
        }

        // Executor tab
        if (Settings::Tab == 2) {
            static TextEditor editor;

            editor.SetShowWhitespaces(false);
            editor.SetReadOnly(false);
            editor.SetPalette(TextEditor::GetDarkPalette());
            editor.SetLanguageDefinition(TextEditor::LanguageDefinition::Lua());

            if (ImGui::Button(ICON_FA_FILE " Execute from file", ImVec2(200, 35))) {
            }

            ImGui::Spacing();
            ImGui::PushStyleVar(ImGuiStyleVar_ScrollbarRounding, 0);
            editor.Render("##EditorWindow", ImVec2(imguipp::getx(), 300));
            ImGui::PopStyleVar();
            ImGui::Spacing();
            ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(7, 7));

            static const std::vector<std::string> items = {"_cfx_internal",
                                                           "_cfx_internal2"};
            static int selectedIndex = 0;
            static const char* current_item = items[selectedIndex].c_str();

            if (ImGui::BeginCombo("##combo", current_item)) // The second parameter is the label previewed before opening the combo.
            {
                for (int n = 0; n < items.size(); n++) {
                    bool is_selected = (current_item == items[n]); // You can store your selection however you want, outside or inside your objects
                    if (ImGui::Selectable(items[n].c_str(), is_selected)) {
                        current_item = items[n].c_str();
                    }

                    if (is_selected) {
                        selectedIndex = n;
                        ImGui::SetItemDefaultFocus(); // You may set the initial focus when opening the combo (scrolling + for keyboard navigation support)
                    }
                }
                ImGui::EndCombo();
            }

            std::cout << current_item << std::endl;

            ImGui::PopStyleVar();
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_CHECK " Execute", ImVec2(115, 34))) {
            }
            ImGui::SameLine();
            if (ImGui::Button(ICON_FA_SQUARE " Stop", ImVec2(imguipp::getx(), 34))) {
            }
        }

        // Dumper Tab
    }
}

void Menu::Theme() {
    ImGuiStyle* style = &ImGui::GetStyle();

    style->WindowBorderSize = 0;
    style->WindowTitleAlign = ImVec2(0.5, 0.5);
    style->WindowMinSize = ImVec2(900, 430);

    style->FramePadding = ImVec2(8, 6);

    style->Colors[ImGuiCol_TitleBg] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgActive] = ImColor(255, 101, 53, 255);
    style->Colors[ImGuiCol_TitleBgCollapsed] = ImColor(0, 0, 0, 130);

    style->Colors[ImGuiCol_Button] = ImColor(31, 30, 31, 255);
    style->Colors[ImGuiCol_ButtonActive] = ImColor(41, 40, 41, 255);
    style->Colors[ImGuiCol_ButtonHovered] = ImColor(41, 40, 41, 255);

    style->Colors[ImGuiCol_Separator] = ImColor(70, 70, 70, 255);
    style->Colors[ImGuiCol_SeparatorActive] = ImColor(76, 76, 76, 255);
    style->Colors[ImGuiCol_SeparatorHovered] = ImColor(76, 76, 76, 255);

    style->Colors[ImGuiCol_FrameBg] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgActive] = ImColor(37, 36, 37, 255);
    style->Colors[ImGuiCol_FrameBgHovered] = ImColor(37, 36, 37, 255);

    style->Colors[ImGuiCol_Header] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderActive] = ImColor(0, 0, 0, 0);
    style->Colors[ImGuiCol_HeaderHovered] = ImColor(46, 46, 46, 255);
}