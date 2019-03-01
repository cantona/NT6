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
                "east"  : __DIR__"maze64",
                "south" : __DIR__"maze32",
                "west"  : __DIR__"maze21",
                "north" : __DIR__"maze28",
        ]));

        set("item_desc", ([
                "shibei" : "
　　鼎：元吉，亨。
　　初六：鼎顛趾，利出否，得妾以其子，無咎。
　　九二：鼎有實，我仇有疾，不我能即，吉。
　　九三：鼎耳革，其行塞，雉膏不食，方雨虧悔，終吉。
　　九四：鼎折足，覆公□，其形渥，兇。
　　六五：鼎黃耳金鉉，利貞。
　　上九：鼎玉鉉，大吉，無不利。
□  ＝ □ ＋ 束  
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 50, me);
        check_count(me, 50);
        return;
}