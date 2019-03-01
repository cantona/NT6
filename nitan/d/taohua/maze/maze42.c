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
                "east"  : __DIR__"maze57",
                "south" : __DIR__"maze3",
                "west"  : __DIR__"maze61",
                "north" : __DIR__"maze51",
        ]));

        set("item_desc", ([
                "shibei" : "
　　益：利有攸往，利涉大川。
　　初九：利用為大作，元吉，無咎。
　　六二：或益之，十朋之龜弗克違，永貞吉。 王用享于帝，吉。
　　六三：益之用兇事，無咎。 有孚中行，告公用圭。
　　六四：中行，告公從。 利用為依遷國。
　　九五：有孚惠心，勿問元吉。 有孚惠我德。
　　上九：莫益之，或擊之，立心勿恆，兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 42, me);
        check_count(me, 42);
        return;
}