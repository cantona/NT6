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
                "east"  : __DIR__"maze63",
                "south" : __DIR__"maze4",
                "west"  : __DIR__"maze48",
                "north" : __DIR__"maze59",
        ]));

        set("item_desc", ([
                "shibei" : "
　　坎：習坎，有孚，維心亨，行有尚。
　　初六：習坎，入于坎□□，兇。
　　九二：坎有險，求小得。
　　六三：來之坎坎，險且枕，入于坎□□，勿用。
　　六四：樽酒簋貳，用缶，納約自牖，終無咎。
　　九五：坎不盈，只既平，無咎。
 　 上六：□用徽□□，置于叢棘，三歲不得，兇。
□□ ＝ 上穴 ＋ 下陷 － □
□□ ＝ □ ＋ 墨
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 29, me);
        check_count(me, 29);
        return;
}