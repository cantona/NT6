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
                "east"  : __DIR__"maze37",
                "south" : __DIR__"maze29",
                "west"  : __DIR__"maze57",
                "north" : __DIR__"maze40",
        ]));

        set("item_desc", ([
                "shibei" : "
　　渙：亨。 王假有廟，利涉大川，利貞。
　　初六：用拯馬壯，吉。
　　九二：渙奔其機，悔亡。
　　六三：渙其躬，無悔。
　　六四：渙其羣，元吉。 渙有丘，匪夷所思。
　　九五：渙汗其大號，渙王居，無咎。
　　上九：渙其血，去逖出，無咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 59, me);
        check_count(me, 59);
        return;
}