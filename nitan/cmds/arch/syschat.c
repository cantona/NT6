#include <ansi.h>
inherit F_CLEAN_UP;

int main(object me, string arg)
{
       if (! SECURITY_D->valid_grant(me, "(arch)"))
                return notify_fail("ARCH以上的巫師才可以發布系統提示。\n");
        if (!arg) return notify_fail("你想要大叫什麼?\n");
                                message_system(arg);
        return 1;
}
int help(object me)
{
  write(@HELP
指令格式 : syschat <訊息>
 
這個指令讓你將 <訊息> 傳送出去, 所有正在遊戲中的人都
會聽見你的話.
 
HELP
    );
    return 1;
}