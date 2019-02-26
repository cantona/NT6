// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

#include "maze.h"

void create()
{
        set("short", "石陣");
        set("long", @LONG
這是一座由約莫兩人多高的大石塊構成的亂石陣，規模似乎不大，但
抬眼望去，四周盡是重重疊疊的嶙峋怪石，完全看不出有路通向石陣之外，
加之陣中常年霧氣瀰漫，更讓人摸不清頭緒。石塊下有一塊斜倒的石碑(s
hibei)，半埋在浮土中。
LONG );

        set("exits", ([
                "east"  : __DIR__"maze33",
                "south" : __DIR__"maze45",
                "west"  : __DIR__"maze1",
        ]));

        set("item_desc", ([
                "shibei" : "
　　否：否之匪人，不利君子貞，大往小來。
　　初六：拔茅茹，以其夤，貞吉亨。
　　六二：包承。 小人吉，大人否亨。
　　六三：包羞。
　　九四：有命無咎，疇離祉。
　　九五：休否，大人吉。 其亡其亡，繫於苞桑。
　　上九：傾否，先否後喜。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 12, me);
        check_count(me, 12);
        return;
}