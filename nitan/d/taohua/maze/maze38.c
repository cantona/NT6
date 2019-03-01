// Copyright (C) 2003, by Slough1 group. All rights reserved.
// This software can not be used, copied, or modified in any
// form without the written permission from authors.

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
                "east"  : __DIR__"maze21",
                "south" : __DIR__"maze54",
                "west"  : __DIR__"maze56",
                "north" : __DIR__"maze58",
        ]));

        set("item_desc", ([
                "shibei" : "
　　睽：小事吉。
　　初九：悔亡，喪馬勿逐，自復；見惡人無咎。
　　九二：遇主于巷，無咎。
　　六三：見輿曳，其牛掣，其人天且劓，無初有終。
　　九四：睽孤，遇元夫，交孚，厲無咎。
　　六五：悔亡，厥宗噬膚，往何咎。
　　上九：睽孤， 見豕負塗，載鬼一車， 先張之弧，後說之弧，匪寇婚
          媾，往遇雨則吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 38, me);
        check_count(me, 38);
        return;
}