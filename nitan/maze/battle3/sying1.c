// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

#include <ansi.h>
#include <command.h>

#define RIDE_CMD        "/cmds/std/ride"

inherit ROOM;


void create()
{
        set("short", HIW"元帥帳營"NOR);
        set("long", @LONG
這裡就是「大宋」元帥的帳營，兩邊分立著眾將領軍士，大宋元
帥在這裡負責調兵遣將，抗擊蒙古軍的入侵，不時有傳令兵匆忙地進
出，傳遞著前線的軍情。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
              "north" :   __DIR__"sying",
              "south" :   __DIR__"sying4",
              "west"  :   __DIR__"sying2",
              "east"  :   __DIR__"sying3",
        ]));

        setup();
}

void init()
{
        object me = this_player();

        if (me == WAR_D->query_marshal())
        {
                message_vision(HIW "帳中的將士看見$N走了進來，連忙將身體站得筆直，尊敬地向$N行禮致敬！\n" NOR, me);

                add_action("do_assign", ({ "appoint", "paiqian", "assign" }));
                add_action("do_convene", ({ "convene", "dianjiang" }));
        }
}

// recruit 招募
int do_assign(string arg)
{
        object me;

        me = this_player();
        tell_object(me, WAR_D->do_assign(me, arg));
        return 1;
}

int do_convene(string arg)
{
        object ob, me;
        object *total;
        int i;

        me = this_player();
        message_vision(HIR "$N召來傳令兵，下令道：火速傳令各營統領到本帥帳前候令！！\n", me);

        total = WAR_D->query_generals();
        for (i = 0; i < sizeof(total); i++)
        {
                if (! objectp(total[i])) continue;

                ob = total[i];
                if( query_temp("warquest/guard", ob) || 
                    query_temp("warquest/recon", ob) || 
                    query_temp("warquest/purchase", ob) || 
                    query_temp("warquest/battle", ob) )
                        continue;

                if (sscanf(base_name(environment(ob)), "/maze/battle3/sy%*s"))
                {
                        message_vision(HIR "一位傳令兵急匆匆得趕來對$N道：三軍將領" +
                                       "火速至元帥帳營侯令！！\n" NOR, ob);

                        ob->start_call_out((: call_other, __FILE__, "go_back", ob :), 5);
                }
        }

        return 1;
}

void go_back(object ob)
{
        if (! objectp(ob)) return;

        message_vision(HIY "$N趕忙批盔帶甲，趕至元帥帳營，還好沒誤了時辰。\n" NOR, ob);
        ob->move(__DIR__"sying1");

        return;
}


