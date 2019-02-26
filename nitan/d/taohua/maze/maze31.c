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
                "east"  : __DIR__"maze58",
                "south" : __DIR__"maze56",
                "west"  : __DIR__"maze45",
                "north" : __DIR__"maze33",
        ]));

        set("item_desc", ([
                "shibei" : "
　　鹹：亨，利貞，取女吉。
　　初六：鹹其拇。
　　六二：鹹其腓，兇，居吉。
　　九三：鹹其股，執其隨，往吝。
　　九四：貞吉悔亡，憧憧往來，朋從爾思。
　　九五：鹹其□，無悔。
　　上六：鹹其輔，頰，舌。
□  ＝ 月 ＋ 每
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 31, me);
        check_count(me, 31);
        return;
}