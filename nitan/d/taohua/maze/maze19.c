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
                "east"  : __DIR__"maze24",
                "west"  : __DIR__"maze15",
                "north" : __DIR__"maze41",
        ]));

        set("item_desc", ([
                "shibei" : "
　　臨：元，亨，利，貞。 至於八月有兇。
　　初九：鹹臨，貞吉。
　　九二：鹹臨，吉無不利。
　　六三：甘臨，無攸利。 既憂之，無咎。
　　六四：至臨，無咎。
　　六五：知臨，大君之宜，吉。
　　上六：敦臨，吉無咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 19, me);
        check_count(me, 19);
        return;
}