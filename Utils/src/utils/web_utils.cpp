#include "utils/web_utils.h"
#include "config/global.h"

namespace WebUtils {
static std::jthread web_server_thread;
int start_web_server_thread() {
    auto start_web_server = [](std::stop_token stop_token) {
        WebServer webServer("0.0.0.0", Global::local_server_port);
        int webServerInitResult = webServer.init();
        if (webServerInitResult != 0) {
            std::cerr << webServerInitResult << std::endl;
        }
        print("Started web server at port ", Global::local_server_port);
        webServer.run(stop_token);
    };
    print("Starting web server");
    web_server_thread = std::jthread(start_web_server);
    print("Started web server");
    return 0;
};

int stop_web_server_thread() {
    print("Stopping web server");
    web_server_thread.request_stop();
    print("Stopped web server");
    return 0;
}
} // namespace WebUtils