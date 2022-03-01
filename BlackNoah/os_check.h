#ifndef OS_CHECK_H
#define OS_CHECK_H
#include <string>
using namespace std;
class OS_Check
{
public:
    OS_Check();
    string CheckOS();
    string OperatingSystem();
    string Get_dir_from_file (string file);
    int numberB;

};

#endif
