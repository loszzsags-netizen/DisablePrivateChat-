#include <llapi/EventAPI.h>
#include <llapi/LoggerAPI.h>
#include <llapi/LLAPI.h>
#include <llapi/mc/Player.hpp>
#include <string>
#include <vector>
#include <algorithm>

Logger logger("DisablePrivateChat");

static const std::vector<std::string> blockedCmds = {
    "/w ", "/w\t", "/tall ", "/tall\t", "/me ", "/me\t", "/msg ", "/msg\t"
};

bool isBlockedCommand(const std::string& cmd) {
    if (cmd.empty()) return false;
    std::string lowerCmd = cmd;
    std::transform(lowerCmd.begin(), lowerCmd.end(), lowerCmd.begin(), ::tolower);
    for (const auto& prefix : blockedCmds) {
        std::string lowerPrefix = prefix;
        std::transform(lowerPrefix.begin(), lowerPrefix.end(), lowerPrefix.begin(), ::tolower);
        if (lowerCmd.rfind(lowerPrefix, 0) == 0) return true;
        std::string exactCmd = lowerCmd;
        exactCmd.erase(exactCmd.find_last_not_of(" \t") + 1);
        std::string exactPrefix = lowerPrefix;
        exactPrefix.erase(exactPrefix.find_last_not_of(" \t") + 1);
        if (exactCmd == exactPrefix) return true;
    }
    return false;
}

void PluginInit() {
    ll::registerPlugin("DisablePrivateChat", u8"禁用私聊指令插件", ll::Version(1, 0, 0));
    logger.info(u8"[DisablePrivateChat] 插件已加载!");
    Event::PlayerCmdEvent::subscribe([](const Event::PlayerCmdEvent& ev) {
        if (!ev.mPlayer) return true;
        if (isBlockedCommand(ev.mCommand)) {
            ev.mPlayer->sendText(u8"§c§l[提示] §r§e服务器已禁用私聊");
            logger.info(u8"玩家 {} 尝试使用私聊指令: {}", ev.mPlayer->getRealName(), ev.mCommand);
            return false;
        }
        return true;
    });
}
