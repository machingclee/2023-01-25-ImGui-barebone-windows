#include "torch/torch.h"
#include <vector>
#include "npy.hpp"
#include <iostream>
#include "utils/npy_utils.h"

using namespace torch::indexing;
int main() {
    at::Tensor anchors = npy_utils::load_anchors_face();
    std::cout << anchors[0] << std::endl;

    std::string face_detector_modelpath = "C:\\Users\\user\\Repos\\C++\\2023-01-25-ImGui-barebone-windows\\cpp_torch_models\\face_detector.zip";
    torch::jit::script::Module face_detector = torch::jit::load(face_detector_modelpath);

    torch::Tensor fake_cam_img = torch::randn({1, 3, 128, 128});
    // torch::Tensor y = torch::randn({1, 100});
    // torch::Tensor inputs = torch::cat({x, y});
    std::vector<torch::IValue> x_{inputs};
    torch::Tensor yTensor = net.forward(x_).toTensor();
    size_t ySize = yTensor.sizes()[0];
    float* yDataPtr = (float*)yTensor.data_ptr();
    try {
        // float result = output.toTensor().item<float>();
        for (int i = 0; i < ySize; i++) {
            float value = yDataPtr[i];
            std::cout << "The Float Value output: " << value << std::endl;
        }
    } catch (const c10::Error& e) {
        std::cerr << e.msg() << std::endl;
    }
}
