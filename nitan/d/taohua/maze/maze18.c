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
                "east"  : __DIR__"maze4",
                "south" : __DIR__"maze46",
                "west"  : __DIR__"maze27",
                "north" : __DIR__"maze48",
        ]));

        set("item_desc", ([
                "shibei" : "
　　蠱：元亨，利涉大川。 先甲三日，後甲三日。
　　初六：幹父之蠱，有子，考無咎，厲終吉。
　　九二：幹母之蠱，不可貞。
　　九三：幹父小有晦，無大咎。
　　六四：裕父之蠱，往見吝。
　　六五：幹父之蠱，用譽。
　　上九：不事王侯，高尚其事。 
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        if (! me) return;
        addn_temp("taohua/count", 18, me);
        check_count(me, 18);
        return;
}