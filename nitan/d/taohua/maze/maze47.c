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
                "east"  : __DIR__"maze49",
                "south" : __DIR__"maze64",
                "west"  : __DIR__"maze28",
                "north" : __DIR__"maze6",
        ]));

        set("item_desc", ([
                "shibei" : "
　　困：亨，貞，大人吉，無咎，有言不信。
　　初六：臀困于株木，入于幽谷，三歲不見。
　　九二：困于酒食，朱紱方來，利用亨祀，征兇，無咎。
　　六三：困于石，據于蒺藜，入于其宮，不見其妻，兇。
　　九四：來徐徐，困于金車，吝，有終。
　　九五：劓刖，困于赤紱，乃徐有說，利用祭祀。
　　上六：困于葛□□，于□□□□，曰動悔。 有悔，征吉。
□□ ＝ 上 □ ＋ 三個品字形的 田
□□ ＝ 臬 ＋ 危 
□□ ＝ 兀 ＋ 危
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