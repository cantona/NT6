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
                "east"  : __DIR__"maze53",
                "south" : __DIR__"maze8",
                "west"  : __DIR__"maze9",
                "north" : __DIR__"maze16",
        ]));

        set("item_desc", ([
                "shibei" : "
　　觀：盥而不薦，有孚□若。
　　初六：童觀，小人無咎，君子吝。
　　六二：窺觀，利女貞。
　　六三：觀我生，進退。
　　六四：觀國之光，利用賓于王。
　　九五：觀我生，君子無咎。
　　上九：觀其生，君子無咎。
□  ＝ 禺 ＋ 頁
\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 20, me);
        check_count(me, 20);
        return;
}