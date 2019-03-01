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
加之陣中常年霧氣彌漫，更讓人摸不清頭緒。石塊下有一塊斜倒的石碑(s
hibei)，半埋在浮土中。
LONG );

        set("exits", ([
                "east"  : __DIR__"maze12",
                "south" : __DIR__"maze43",
        ]));

        set("item_desc", ([
                "shibei" : "
　　乾：元，亨，利，貞。

　　初九：潛龍，勿用。
　　九二：見龍再田，利見大人。
　　九三：君子終日乾乾，夕惕若，厲無咎。
　　九四：或躍在淵，無咎。
　　九五：飛龍在天，利見大人。
　　上九：亢龍有悔。
　　用九：見群龍無首，吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();

        addn_temp("taohua/count", 1, me);
        check_count(me,1);
        return;
}