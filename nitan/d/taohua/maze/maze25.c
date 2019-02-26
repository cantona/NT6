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
                "east"  : __DIR__"maze44",
                "south" : __DIR__"maze17",
                "west"  : __DIR__"maze10",
        ]));

        set("item_desc", ([
                "shibei" : "
  　無妄：元，亨，利，貞。 其匪正有眚，不利有攸往。
　　初九：無妄，往吉。
　　六二：不耕穫，不□畲，則利有攸往。
　　六三：無妄之災，或繫之牛，行人之得，邑人之災。
　　九四：可貞，無咎。
　　九五：無妄之疾，勿藥有喜。
　　上九：無妄，行有眚，無攸利。
□  ＝  上 艹 下甾

\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 25, me);
        check_count(me, 25);
        return;
}