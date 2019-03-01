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
                "east"  : __DIR__"maze17",
                "south" : __DIR__"maze38",
                "west"  : __DIR__"maze31",
                "north" : __DIR__"maze10",
        ]));

        set("item_desc", ([
                "shibei" : "
　　兌：亨，利貞。
　　初九：和兌，吉。
　　九二：孚兌，吉，悔亡。
　　六三：來兌，兇。
　　九四：商兌，未寧，介疾有喜。
　　九五：孚于剝，有厲。
　　上六：引兌。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 58, me);
        check_count(me, 58);
        return;
}