set(
  SOURCES
  "include/imgui/global.h"
  "include/imgui/imconfig.h"
  "include/imgui/imgui_impl_dx11.h"
  "include/imgui/imgui_impl_win32.h"
  "include/imgui/imgui_internal.h"
  "include/imgui/imgui.h"
  "include/imgui/imstb_rectpack.h"
  "include/imgui/imstb_textedit.h"
  "include/imgui/imstb_truetype.h"
  src/imgui_demo.cpp
  src/imgui_draw.cpp
  src/imgui_impl_dx11.cpp
  src/imgui_impl_win32.cpp
  src/imgui_tables.cpp
  src/imgui_widgets.cpp
  src/imgui.cpp
)

add_library(imgui ${SOURCES})
target_include_directories(imgui PUBLIC ../imgui/include/imgui)