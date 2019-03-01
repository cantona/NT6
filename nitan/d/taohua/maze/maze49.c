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
                "south" : __DIR__"maze30",
                "west"  : __DIR__"maze47",
                "north" : __DIR__"maze13",
        ]));

        set("item_desc", ([
                "shibei" : "
　　革：己日乃孚，元亨利貞，悔亡。
　　初九：鞏用黃牛之革。
　　六二：己日乃革之，征吉，無咎。
　　九三：征兇，貞厲，革言三就，有孚。
　　九四：悔亡，有孚改命，吉。
　　九五：大人虎變，未佔有孚。
　　上六：君子豹變，小人革面，征兇，居貞吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 49, me);
        check_count(me, 49);
        return;
}