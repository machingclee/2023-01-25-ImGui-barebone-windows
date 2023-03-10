function(find_opencv_and_torch torch_dir opencv_dir)
    # we can link torch and opencv by target_link_libraries(target PUBLIC ${TORCH_LIBRARIES} ${OpenCV_LIBS})
    set(CMAKE_PREFIX_PATH ${torch_dir})
    set(OpenCV_DIR ${opencv_dir})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${TORCH_CXX_FLAGS}")
    find_package(Torch REQUIRED)
    find_package(OpenCV REQUIRED)
    message(STATUS "TORCH_LIBRARIES = ${TORCH_LIBRARIES}")
endfunction()