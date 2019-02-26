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
                "east"  : __DIR__"maze23",
                "south" : __DIR__"maze11",
                "north" : __DIR__"maze5",
        ]));

        set("item_desc", ([
                "shibei" : "
    大畜：利貞，不家食吉，利涉大川。
　　初九：有厲利已。
　　九二：輿説輻。
　　九三：良馬逐，利艱貞。 曰閒輿衞，利有攸往。
　　六四：童豕之牿，元吉。
　　六五：□豕之牙，吉。
　　上九：何天之衢，亨。
□  ＝ 豕 ＋ 賁

\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 26, me);
        check_count(me, 26);
        return;
}