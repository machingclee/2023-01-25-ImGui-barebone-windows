cmake_minimum_required(VERSION 3.0.0)
project(trial VERSION 0.1.0)


set(WEB_SERVER_LIB web_server_lib)
set(UTILS_LIB utils)
set(IMGUI_LIB imgui_lib)
set(OPENCV_AND_TORCH_LIB opencv_and_torch_lib)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_C_STANDARD_LIBRARIES wsock32.lib ws2_32.lib)

include(opencv_and_torch/cmake/link_opencv_and_torch.cmake)

add_executable(trial main.cpp)
add_subdirectory(imgui)
add_subdirectory(opencv_and_torch)
add_subdirectory(WebServer)
add_subdirectory(Utils)

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