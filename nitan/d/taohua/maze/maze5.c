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
                "east"  : __DIR__"maze8",
                "south" : __DIR__"maze26",
                "north" : __DIR__"maze9",
        ]));

        set("item_desc", ([
                "shibei" : "
　　需：有孚，光亨，貞吉。 利涉大川。
　　初九：需於郊。 利用恆，無咎。
　　九二：需於沙。 小有言，終吉。
　　九三：需於泥，致寇至。
　　六四：需於血，出自穴。
　　九五：需於酒食，貞吉。
　　上六：入於穴，有不速之客三人來，敬之終吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 5, me);
        check_count(me, 5);
        return;
}