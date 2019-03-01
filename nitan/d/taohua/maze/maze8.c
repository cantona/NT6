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
                "east"  : __DIR__"maze39",
                "south" : __DIR__"maze23",
                "west"  : __DIR__"maze5",
                "north" : __DIR__"maze20",
        ]));

        set("item_desc", ([
                "shibei" : "
　　比：吉。 原筮元永貞，無咎。 不寧方來，後夫兇。
　　初六：有孚比之，無咎。 有孚盈缶，終來有他，吉。
　　六二：比之自內，貞吉。
　　六三：比之匪人。
　　六四：外比之，貞吉。
　　九五：顯比，王用三驅，失前禽。 邑人不誡，吉。
　　上六：比之無首，兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 8, me);
        check_count(me, 8);
        return;
}