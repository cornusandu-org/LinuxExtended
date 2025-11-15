#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>
#include <syslog.h>

#define info(...) syslog(LOG_INFO, __VA_ARGS__)
#define err(...) syslog(LOG_ERR, __VA_ARGS__)

namespace fs = std::filesystem;

int main() {
    openlog("fastpackagemanager", LOG_PID | LOG_CONS, LOG_DAEMON);

    const std::string stateFile = "/var/lib/fastpackagemanager/state";

    if (!fs::exists(stateFile)) {
        info("Running initial setup...\n");

        // 1. Mount /packages
        // Replace with actual mount command or system call
        int mountStatus = system("mount /packages");
        if (mountStatus != 0) {
            err("Failed to mount /packages\n");
            return 1;
        }

        // 2. Create /var/cache/packagecache
        fs::create_directories("/var/cache/packagecache");

        // 3. Create /etc/fastpackagemanager/permissions.ini directory + file
        fs::create_directories("/etc/fastpackagemanager");
        std::ofstream ini("/etc/fastpackagemanager/permissions.ini");
        ini << "; initial permissions file\n";
        ini.close();

        // 4. Write state marker
        fs::create_directories("/var/lib/fastpackagemanager");
        std::ofstream state(stateFile);
        state << "initialized=true\n";
        state.close();

        info("Initialization completed.\n");
    };

    closelog();
    return 0;
}
