// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified
// in any form without the written permission from authors.

inherit ROOM;
#include <ansi.h>

void create()
{
        set("short", "石陣入口");
        set("long", @LONG
這是一片空闊的砂石灘，南邊有一個小小的港灣，北邊似乎是一座亂
石陣，但是一股薄霧常年籠罩着石陣，使人看不真切陣中究竟。通入陣中
的唯一小路又被一塊大石碑(shibei)擋住。
LONG );

        set("exits", ([
                "south" : __DIR__"harbor",
        ]));

        set("item_desc", ([
                "shibei" : "
石碑表面十分光滑，似乎經常有人用手摩挲，上面有幾行字：
天道左旋，地道右旋，數往者順，知來者逆。
\n",
        ]));

        set("coor/x", 8970);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
}

void init()
{
         add_action("do_push", "push");
}


int do_push(string arg)
{
        object me = this_player();

        if (!arg || arg != "shibei")
                return notify_fail("什麼？\n");

        if( me->query_str()<25 && query("combat_exp", me)>100000 )
        {
                return notify_fail("你沒那麼大力氣搬動石碑。\n");
        }

        /*
        if( (query("age", me)-query("taohua_maze", me))<query("taohua_maze2", me) )
                return notify_fail("你今年已通過桃花混沌大陣，明年再來吧\n");
        */

        message_vision(HIW "石碑緩緩沉入地面，石陣中湧出一股怪風挾着濃霧向$N捲來！\n"
                       "$N身影頓時消失在濃霧之中......\n\n\n\n\n" NOR, me);

        if( query("taohua_maze", me) )
                me->move("/d/taohua/maze/zhongshu");
        else
                me->move("/d/taohua/maze/maze"+(random(63)+1));

        return 1;
}