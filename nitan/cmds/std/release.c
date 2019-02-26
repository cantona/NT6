// fang.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;

        if (! arg)
                return notify_fail("你要和誰脱離關係？\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要和誰脱離關係？\n");

        if( query_temp("owner", ob) != query("id", me) )
                return notify_fail("你並不是" + ob->name() + "的主人啊，發什麼話？\n");

        if( query("can_speak", ob) )
                message_vision("$N道：走吧，" + ob->name() +
                               "，你走吧。\n", me, ob);
        else
                message_vision("$N很慈悲地把$n放離，任其迴歸自然了。\n", me, ob);

        if( query_temp("comedby", me) == ob )
                delete_temp("comedby", me);

        delete_temp("owner", ob);
        delete_temp("owner_name", ob);
        ob->set_leader(0);
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : release <對象>

此指令可用於讓你的跟隨者或是馴養的動物結束主奴狀態。

HELP );
        return 1;
}