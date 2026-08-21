#include <ll/api/Plugin.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/player/PlayerChatEvent.h>
#include <ll/api/Logger.h>
#include <mc/Player.hpp>

using namespace ll::event;

namespace disable_private_chat {

ll::Logger logger("DisablePrivateChat");

bool onEnable(ll::Plugin& self) {
    logger.info("DisablePrivateChat 已加载，拦截私聊消息");

    EventBus::getInstance().subscribe<PlayerChatEvent>(
        EventPriority::Normal,
        [](PlayerChatEvent& ev) {
            auto msg = ev.getMessage();
            if (msg.starts_with("/msg") || msg.starts_with("/tell") || msg.starts_with("/w")) {
                ev.cancel();
                ev.getPlayer().sendMessage("§c服务器已关闭私聊功能！");
            }
        }
    );
    return true;
}

bool onDisable(ll::Plugin& self) {
    logger.info("DisablePrivateChat 已卸载");
    return true;
}

} // namespace disable_private_chat

LL_PLUGIN_INFO(
    disable_private_chat,
    1,
    0,
    "Disable Private Chat",
    "拦截 /msg /tell /w 私聊指令",
    ""
);
LL_PLUGIN_ENABLE(disable_private_chat::onEnable);
LL_PLUGIN_DISABLE(disable_private_chat::onDisable);
