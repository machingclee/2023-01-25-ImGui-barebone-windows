#pragma once
#include "capture_utils.h"
#include "opencv2/opencv.hpp"
#include <iostream>

int start_screen_capture(std::string filename = "./desktop_capture.avi") {
    cv::Mat ui(40, 400, CV_8UC3, cv::Scalar(0, 130, 0));
    cv::putText(ui, "Press Esc to stop capturing", cv::Point(30, 30), cv::FONT_HERSHEY_COMPLEX, 0.7,
                cv::Scalar(0, 0, 255), 1);
    cv::Mat bgrImg;
    hwnd2Mat capDesktop(GetDesktopWindow());

    cv::VideoWriter writer;
    int codec = cv::VideoWriter::fourcc('X', 'V', 'I', 'D');
    double fps = 10.0;
    writer.open(filename, codec, fps, capDesktop.image.size(), true);
    // check if we succeeded
    if (!writer.isOpened()) {
        std::cerr << "Could not open the output video file for write\n";
        return -1;
    }

    while (true) {
        capDesktop.read();
        cvtColor(capDesktop.image, bgrImg, cv::COLOR_BGRA2BGR);
        writer << bgrImg;
        imshow("desktop capture", ui);
        int key = cv::waitKey(5);

        if (key == 27) {
            break; // esc
        }
    }

    std::cout << "screen capture done" << std::endl;
    return 0;
}

int start_webcam_capture(int camera_index = 0) {
    torch::jit::script::Module module;
    cv::VideoCapture cap(camera_index);

    if (!cap.isOpened()) {
        std::cout << "Cannot open camera\n";
        return 1;
    }

    cv::Mat frame;
    cv::Mat gray;

    while (true) {
        bool ret = cap.read(frame);
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        imshow("camera", frame);

        int key = cv::waitKey(5);
        if (key == 27 || cv::getWindowProperty("camera", cv::WND_PROP_AUTOSIZE) == -1) {
            break; // esc
        }
    }
    return 0;
}