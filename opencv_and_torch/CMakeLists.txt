add_library(
  opencv_and_torch_lib 
  capture_utils.cpp
  capture_utils.h
)

target_link_libraries(opencv_and_torch_lib ${TORCH_LIBRARIES} ${OpenCV_LIBS})
target_include_directories(opencv_and_torch_lib PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(opencv_and_torch_lib PUBLIC .)

set(TARGET opencv_and_torch_lib PROPERTY CXX_STANDARD 14)