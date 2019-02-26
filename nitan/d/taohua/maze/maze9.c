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
                "east"  : __DIR__"maze20",
                "south" : __DIR__"maze5",
                "north" : __DIR__"maze34",
        ]));

        set("item_desc", ([
                "shibei" : "
　　小畜：亨。 密雲不雨，自我西郊。
　　初九：復自道，何其咎，吉。
　　九二：牽復，吉。
　　九三：輿説輻，夫妻反目。
　　六四：有孚，血去惕出，無咎。
　　九五：有孚攣如，富以其鄰。
　　上九：既雨既處，尚德載，婦貞厲。 月幾望，君子徵兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 9, me);
        check_count(me, 9);
        return;
}