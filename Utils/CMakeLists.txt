set(
  SOURCE
  "include/utils/capture_utils.h"
  "include/utils/common.h"
  "include/utils/web_utils.h"
  "include/utils/win_reg.h"
  src/utils/capture_utils.cpp
  src/utils/common.cpp
  src/utils/web_utils.cpp
  src/utils/register_protocol.cpp
)


add_library(${UTILS_LIB} ${SOURCE}) 
target_link_libraries(${UTILS_LIB} PUBLIC ${TORCH_LIBRARIES} ${OpenCV_LIBS} ${WEB_SERVER_LIB} ${CONFIG})
target_include_directories(${UTILS_LIB} PUBLIC include)