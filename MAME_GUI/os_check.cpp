#include "os_check.h"
#ifdef linux // Checks if running on a Linux system
static bool Linux_OS = true;
#endif

extern std::string OperatingSystem;
OS_Check::OS_Check()
{

}

std::string OS_Check::CheckOS() {
    if (Linux_OS == true) {
        std::string OperatingSystem = "Linux";
        int numberB = 666;
    }
    std::string OperatingSystem = "Linux";
    return OperatingSystem;
}
