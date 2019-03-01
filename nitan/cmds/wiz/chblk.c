// channel block command..
// Modified by Marz, 04/18/96
// updated by doing

#include <getconfig.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        
        if (! SECURITY_D->valid_grant(me, "(wizard)"))
                return 0;

        if (! arg)
                return notify_fail("指令格式: chblk <player id>\n");
    
        ob = UPDATE_D->global_find_player(arg);
        if (! ob)
                return notify_fail(LOCAL_MUD_NAME() + "並沒有這個人！\n");

        if (wiz_level(ob) > 0)
        {
                UPDATE_D->global_destruct_player(ob);
                return notify_fail("你不能關閉巫師的頻道。\n");
        }

        if( query("chblk_on", ob) )
        {
                UPDATE_D->global_destruct_player(ob);
                return notify_fail("這個人的頻道已經被關閉了。\n");
        }

        set("chblk_on", 1, ob);
        set("chblk_by", geteuid(me), ob);
        write("你關閉了" + ob->name(1) + "的頻道。\n");
        tell_object(ob, me->name(1) + "關閉了你的頻道。\n");

        UPDATE_D->global_destruct_player(ob, 1);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : chblk <玩家>

此命令將關閉某個玩家的頻道。

HELP );
        return 1;
}