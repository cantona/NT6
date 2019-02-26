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
                "east"  : __DIR__"maze60",
                "south" : __DIR__"maze52",
                "west"  : __DIR__"maze8",
                "north" : __DIR__"maze53",
        ]));

        set("item_desc", ([
                "shibei" : "
　　蹇：利西南，不利東北；利見大人，貞吉。
　　初六：往蹇，來譽。
　　六二：王臣蹇蹇，匪躬之故。
　　九三：往蹇來反。
　　六四：往蹇來連。
　　九五：大蹇朋來。
　　上六：往蹇來碩，吉；利見大人。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 39, me);
        check_count(me, 39);
        return;
}