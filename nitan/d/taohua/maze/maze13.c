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
                "south" : __DIR__"maze49",
                "west"  : __DIR__"maze6",
        ]));

        set("item_desc", ([
                "shibei" : "
　　同人：同人于野，亨。 利涉大川，利君子貞。
　　初九：同人于門，無咎。
　　六二：同人于宗，吝。
　　九三：伏戎于莽，升其高陵，三歲不興。
　　九四：乘其墉，弗克攻，吉。
　　九五：同人，先號啕而後笑。 大師克相遇。
　　上九：同人于郊，無悔。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 13, me);
        check_count(me, 13);
        return;
}