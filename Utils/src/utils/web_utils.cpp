#include "utils/web_utils.h"
#include "config/global.h"

namespace WebUtils {
static std::atomic<bool> stop_web_service_thread = false;
static std::thread web_server_thread;
int start_web_server_thread() {
    auto start_web_server = []() {
        WebServer webServer("0.0.0.0", Global::local_server_port);
        int webServerInitResult = webServer.init();
        if (webServerInitResult != 0) {
            std::cerr << webServerInitResult << std::endl;
        }
        print("Started web server at port ", Global::local_server_port);
        webServer.run(stop_web_service_thread);
    };
    print("Starting web server");
    web_server_thread = std::thread(start_web_server);
    print("Started web server");
    return 0;
};

int stop_web_server_thread() {
    print("Stopping web server");
    stop_web_service_thread = true;
    web_server_thread.join();
    print("Stopped web server");
    stop_web_service_thread = false;
    return 0;
}
} // namespace WebUtils