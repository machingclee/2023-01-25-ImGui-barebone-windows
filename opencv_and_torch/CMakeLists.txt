add_library(
  opencv_and_torch_lib 
  capture_utils.cpp
  capture_utils.h
)

target_link_libraries(${OPENCV_AND_TORCH_LIB} ${TORCH_LIBRARIES} ${OpenCV_LIBS})
target_include_directories(${OPENCV_AND_TORCH_LIB} PUBLIC ${OpenCV_INCLUDE_DIRS})
target_include_directories(${OPENCV_AND_TORCH_LIB} PUBLIC .)

set(TARGET ${OPENCV_AND_TORCH_LIB} PROPERTY CXX_STANDARD 14)