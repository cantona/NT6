// TIE@FY3
#include <ansi.h>
inherit F_CLEAN_UP;
int main(object me, string arg)
{
        string msg;
        delete_temp("block_msg/all", me);
        write(CLR);
        delete_temp("boss_screen", me);
        write("泥潭告訴你：運氣如何？被抓住了嗎？哈哈！\n");
//        message("channel:chat",GRN"【警鈴】"+me->name(1)+"得意洋洋地打開屏幕，看著老板在門外消失：拜拜了您哪。\n"NOR,users());
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式: bossgone

    這個指令讓你(玩家)在老板走後恢復正常泥潭遊戲。

有關指令：boss
HELP
        );
        return 1;
}