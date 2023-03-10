#pragma once
#include "torch/torch.h"
#include <vector>
#include <string>

namespace npy_utils {

std::vector<double> load_1d_array_from_npy_file(std::string& npy_filepath);

at::Tensor load_anchors_face();
} // namespace npy_utils
