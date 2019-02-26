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
                "east"  : __DIR__"maze49",
                "south" : __DIR__"maze64",
                "west"  : __DIR__"maze28",
                "north" : __DIR__"maze6",
        ]));

        set("item_desc", ([
                "shibei" : "
　　困：亨，貞，大人吉，無咎，有言不信。
　　初六：臀困於株木，入於幽谷，三歲不見。
　　九二：困於酒食，朱紱方來，利用亨祀，徵兇，無咎。
　　六三：困於石，據於蒺藜，入於其宮，不見其妻，兇。
　　九四：來徐徐，困於金車，吝，有終。
　　九五：劓刖，困於赤紱，乃徐有説，利用祭祀。
　　上六：困於葛□①，於□②□③，曰動悔。 有悔，徵吉。
□① ＝ 上 艹 ＋ 三個品字形的 田
□② ＝ 臬 ＋ 危 
□③ ＝ 兀 ＋ 危
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 47, me);
        check_count(me, 47);
        return;
}