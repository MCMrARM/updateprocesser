#include <iostream>
#include <fstream>
#include <git2.h>

#include "play_manager.h"
#include "discord_state.h"
#include "telegram_state.h"
#include "win10_store_manager.h"
#include "win10_versiondb_manager.h"

#include "job_manager.h"

int main() {

    std::cout << "Starting up!" << std::endl;
    git_libgit2_init();


    JobManager jobManager;
    jobManager.startTimeOutThread();

    PlayManager playManager;
    ApkManager apkManager (playManager, jobManager);

//    apkManager.downloadAndProcessApk(playManager.getBetaDeviceARM(), 943160055, false);

    Win10StoreManager win10Manager;
    win10Manager.init();
    Win10VersionDBManager win10VdbManager;
    win10VdbManager.addWin10StoreMgr(win10Manager);

    static DiscordState* discordState = new DiscordState(playManager, apkManager);
    discordState->addWin10StoreMgr(win10Manager);
    TelegramState telegramState(apkManager);

    apkManager.startChecking();
    win10Manager.startChecking();

    signal(SIGINT, [](int signo) { discordState->storeSessionInfo(); exit(0); });
    signal(SIGTERM, [](int signo) { discordState->storeSessionInfo(); exit(0); });
    discordState->loop();

    delete discordState;
    return 0;
}