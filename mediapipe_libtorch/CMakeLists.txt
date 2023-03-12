set(
    sources 
    src/blazebase.h
    src/blazebase.cpp
)
add_library(${MEDIAPIPE_LIBTORCH_LIB} ${sources})
target_link_libraries(${MEDIAPIPE_LIBTORCH_LIB} PUBLIC ${TORCH_LIB} ${OpenCV_LIBS})
target_include_directories(${MEDIAPIPE_LIBTORCH_LIB} PUBLIC src)