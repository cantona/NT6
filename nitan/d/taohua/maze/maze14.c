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
                "east"  : __DIR__"maze35",
                "south" : __DIR__"maze34",
                "north" : __DIR__"maze43",
        ]));

        set("item_desc", ([
                "shibei" : "
　　大有：元亨。 
　　初九：無交害，匪咎，艱則無咎。
　　九二：大車以載，有攸往，無咎。
　　九三：公用亨于天子，小人弗克。
　　九四：匪其彭，無咎。
　　六五：厥孚交如，威如；吉。
　　上九：自天佑之，吉無不利。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 14, me);
        check_count(me, 14);
        return;
}