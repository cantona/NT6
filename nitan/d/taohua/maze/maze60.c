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
                "east"  : __DIR__"maze3",
                "south" : __DIR__"maze41",
                "west"  : __DIR__"maze39",
                "north" : __DIR__"maze61",
        ]));

        set("item_desc", ([
                "shibei" : "
　　節：亨。 苦節不可貞。
　　初九：不出戶庭，無咎。
　　九二：不出門庭，兇。
　　六三：不節若，則嗟若，無咎。
　　六四：安節，亨。
　　九五：甘節，吉；往有尚。
　　上六：苦節，貞兇，悔亡。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 60, me);
        check_count(me, 60);
        return;
}