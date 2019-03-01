// Filename : /cmds/std/unride.c

#include <ansi.h>

inherit F_CLEAN_UP;

void create() { seteuid(getuid()); }

int main(object me)
{
        object ob, follower;

        if( !objectp(ob=query_temp("is_riding", me)) )
                return notify_fail("你下什麼下！根本就沒座騎！\n");

        message_vision("$N從$n上飛身跳下。\n", me, ob);
        ob->move( environment(me) );
        ob->delele_temp("is_rided_by");
        delete_temp("is_riding", me);
        // 讓所有的人也下馬
        if (objectp(follower = query_temp("is_rided_follow", ob)))
        {
                delete_temp("is_riding_follow", follower);
                delete_temp("is_rided_follow", ob);
                //message_vision("$N強行要求所有人下馬。\n", me);
                message_vision("$N從$n上飛身跳下。\n", follower, ob);
        }
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : unride | xia
 
這個指令可以讓你從騎著的已馴養的動物上跳下來。
 
HELP );
    return 1;
}
