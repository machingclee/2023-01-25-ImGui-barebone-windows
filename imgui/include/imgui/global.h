#pragma once

#include "imconfig.h"
#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"
#include "imgui_internal.h"
#include "imstb_rectpack.h"
#include "imstb_textedit.h"
#include "imstb_truetype.h"
#include <d3d11.h>
#include <iostream>

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