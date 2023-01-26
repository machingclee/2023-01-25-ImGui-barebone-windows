#pragma once
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")

#include "font.h"
#include "iconcpp.h"
#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"

#include <iostream>
#include <tchar.h>

template <class F, class First, class... Rest>
void do_for(F f, First first, Rest... rest) {
    f(first);
    do_for(f, rest...);
}
template <class F>

void do_for(F f) {
    std::cout << "\n";
}

template <class... Args>
void print(Args... args) {
    do_for([](auto& arg) {
        std::cout << arg;
    },
           args...);
}

namespace Global {

} // namespace Global