// mccp.c
#include <ansi.h> 
inherit F_CLEAN_UP;

int main(object me, string arg)
{
#ifdef MCCP_SUPPORT
        object *mccp, *user;
        
        user = filter_array(users(), (: interactive($1) :));
        mccp = filter_array(user, (: compressedp($1) :));
        
        write(sprintf("你的 MCCP 狀態為：" HIR "%s\n" NOR, compressedp(me) ? "ON" : "OFF"));
        write(sprintf("現在共 " HIC "%d" NOR "/%d 個使用者開啟 MCCP。\n", sizeof(mccp), sizeof(user)));
#else
        write("驅動程序目前不支持網路傳輸壓縮功能。\n");
#endif
        return 1;
}

int help(object me)
{
        write(@HELP
指令説明:
    檢查玩家的程式是否有啟動 MCCP(Mud Client Compression Protocol)功能
此功能可以加速網路傳輸速度

HELP );
    return 1;
}