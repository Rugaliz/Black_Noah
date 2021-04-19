#include "os_tools.h"
#ifdef linux // Checks if running on a Linux system
static bool Linux_OS = true;
#endif
using namespace std;
extern std::string OperatingSystem;
OS_Check::OS_Check()
{

}

std::string OS_Check::CheckOS() {
    if (Linux_OS == true) {
        std::string OperatingSystem = "Linux";
    }
    std::string OperatingSystem = "Linux";
    return OperatingSystem;
}

string Get_dir_from_file (string file) {
    string temp;
    const size_t last_slash_idx = file.rfind('\/');
    if (std::string::npos != last_slash_idx)
    {
        temp = file.substr(0, last_slash_idx);
    }
    return temp;
}
