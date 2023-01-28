cmake_minimum_required(VERSION 3.0.0)
project(trial VERSION 0.1.0)

include(opencv_and_torch/cmake/link_opencv_and_torch.cmake)

add_executable(trial main.cpp)
add_subdirectory(imgui)
add_subdirectory(opencv_and_torch)

target_link_libraries(trial PUBLIC imgui_lib opencv_and_torch_lib)
include(CPack)

if (MSVC)
  message("copying dll files")
  file(GLOB TORCH_DLLS "${TORCH_INSTALL_PREFIX}/lib/*.dll")
  add_custom_command(TARGET trial
                     POST_BUILD
                     COMMAND ${CMAKE_COMMAND} -E copy_if_different
                     ${TORCH_DLLS}
                     $<TARGET_FILE_DIR:trial>)
endif (MSVC)