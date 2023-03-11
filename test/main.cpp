#include "NumCpp.hpp"

int main(){
    auto npy_file = nc::load<float>("C:\\Users\\user\\Repos\\C++\\2023-01-25-ImGui-barebone-windows\\test\\anchors_face_back.npy");
    print(npy_file);
}