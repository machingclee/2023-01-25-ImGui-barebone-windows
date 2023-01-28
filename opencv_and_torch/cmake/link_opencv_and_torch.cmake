set(CMAKE_CXX_STANDARD 14)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_PREFIX_PATH "C:\\Users\\user\\Repos\\C++Libraries\\libtorch")
set(OpenCV_DIR "C:\\Users\\user\\Repos\\C++Libraries\\opencv\\build\\x64\\vc16")
find_package(Torch REQUIRED)
find_package(OpenCV REQUIRED)
message(STATUS "OpenCV_INCLUDE_DIRS = ${OpenCV_INCLUDE_DIRS}")
message(STATUS "OpenCV_LIBS = ${OpenCV_LIBS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")