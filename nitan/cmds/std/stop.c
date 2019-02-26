// stop.c

#include <ansi.h>

inherit F_CLEAN_UP;

int main(object me, string arg)
{
        object ob;
        int cost, i = 0;

        seteuid(getuid());

        if (! arg)
                return notify_fail("你要命令誰？\n");

        if (! objectp(ob = present(arg, environment(me))))
                return notify_fail("你要命令誰？\n");

        if( query_temp("owner", ob) != query("id", me) )
                return notify_fail("人家不會聽你的話的。\n");

        if (! ob->is_fighting())
                return notify_fail(ob->name() + "現在並沒有和別人搏鬥。\n");

        if( query("can_speak", ob) )
                message_vision("$N大喝一聲道：“" + ob->name() + "，住手！”\n",
                               me);
        else
                message_vision("只見$N衝着$n口中一聲呼哨，$n向後一竄，不咬了！\n",
                               me, ob);

        ob->force_me("halt");
        return 1;
}

int help(object me)
{
        write(@HELP
指令格式 : stop <對象>

此指令可用於讓你的跟隨者或是馴養的動物停止攻擊他人。
HELP );
        return 1;
}