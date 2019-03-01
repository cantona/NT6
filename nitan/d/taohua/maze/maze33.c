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
                "east"  : __DIR__"maze10",
                "south" : __DIR__"maze31",
                "west"  : __DIR__"maze12",
        ]));

        set("item_desc", ([
                "shibei" : "
　　□：亨，小利貞。
　　初六：□尾，厲，勿用有攸往。
　　六二：執之用黃牛之革，莫之勝說。
　　九三：系□，有疾厲，畜臣妾吉。
　　九四：好□君子吉，小人否。
　　九五：嘉□，貞吉。
　　上九：肥□，無不利。
□ ＝  □ ＋ □ ＋ 豚 
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 33, me);
        check_count(me, 33);
        return;
}