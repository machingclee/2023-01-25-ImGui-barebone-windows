from blaze_face_landmark import BlazeFaceLandmark
from torchsummary import summary
import torch
import os

if __name__ == "__main__":
    model = BlazeFaceLandmark()
    img = torch.randn((1, 3, 128, 128))
    state_dict_loc = os.path.sep.join([os.path.dirname(__file__), "weight", "blazeface_landmark.pth"])
    state_dict = torch.load(state_dict_loc)
    model.load_state_dict(state_dict)
    result = model(img)
    print(result)
