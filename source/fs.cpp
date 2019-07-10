// Copied from SwitchThemeInjector
#include "fs.hpp"
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

using namespace std;

string CfwFolder = "";

vector<string> SearchCfwFolders() {
    vector<string> res;
    DIR * dir = nullptr;

    #define CHECKFOLDER(f) dir = opendir(f); \
    if (dir) { res.push_back(f); closedir(dir); dir = nullptr; }
    CHECKFOLDER("/atmosphere")
    CHECKFOLDER("/reinx")
    CHECKFOLDER("/sxos")
    #undef CHECKFOLDER

    if (res.size() == 1)
        CfwFolder = res[0];
    return res;
}
