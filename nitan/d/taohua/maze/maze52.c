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
                "east"  : __DIR__"maze41",
                "south" : __DIR__"maze15",
                "west"  : __DIR__"maze23",
                "north" : __DIR__"maze39",
        ]));

        set("item_desc", ([
                "shibei" : "
　　艮：艮其背，不獲其身，行其庭，不見其人，無咎。
　　初六：艮其趾，無咎，利永貞。
　　六二：艮其腓，不拯其隨，其心不快。
　　九三：艮其限，列其夤，厲薰心。
　　六四：艮其身，無咎。
　　六五：艮其輔，言有序，悔亡。
　　上九：敦艮，吉。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 52, me);
        check_count(me, 52);
        return;
}