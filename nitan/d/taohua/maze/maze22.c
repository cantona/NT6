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
                "south" : __DIR__"maze36",
                "west"  : __DIR__"maze4",
                "north" : __DIR__"maze63",
        ]));

        set("item_desc", ([
                "shibei" : "
　　賁：亨。 小利有所往。
　　初九：賁其趾，舍車而徒。
　　六二：賁其須。
　　九三：賁如濡如，永貞吉。
　　六四：賁如皤如，白馬翰如，匪寇婚媾。
　　六五：賁於丘園，束帛戔戔，吝，終吉。
　　上九：白賁，無咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 22, me);
        check_count(me, 22);
        return;
}