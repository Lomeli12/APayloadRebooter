// A good chunk of this copied from SwitchThemeInjector
#include <stdio.h>
#include <stdlib.h>
#include <switch.h>
#include <algorithm>
#include "fs.hpp"
#include "PayloadReboot.hpp"

bool appRunning = true;

int main(int argc, char **argv) {
    consoleInit(NULL);

    bool showError = false;
    bool canReboot = false;

    auto v = SearchCfwFolders();
    bool hasAtmos = false;

    if (std::find(v.begin(), v.end(), "/atmosphere") != v.end()) {
        showError = false;
        hasAtmos = true;
    }

    if (hasAtmos) {
        if (!PayloadReboot::Init()) {
            showError = true;
        } else {
            canReboot = true;
        }

        if (canReboot) {
            PayloadReboot::Reboot();
        } else if (showError) {
            printf("This feature isn't available with your current setup, you need to use Atmosphere >= 0.8.3 and the "
                   "reboot payload placed in your sd card at /atmosphere/reboot_payload.bin");
            printf("Press + to exit...");
        }
    }

    if (appRunning) {
        while(appletMainLoop()) {
            hidScanInput();
            u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

            if (kDown & KEY_PLUS)
                break;

            consoleUpdate(NULL);
        }
    }
    consoleExit(NULL);
    return 0;
}

void QuitApp() {
    appRunning = false;
}
