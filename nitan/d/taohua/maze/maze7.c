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
                "east"  : __DIR__"maze36",
                "west"  : __DIR__"maze46",
                "north" : __DIR__"maze4",
        ]));

        set("item_desc", ([
                "shibei" : "
　　師：貞，丈人，吉無咎。
　　初六：師出以律，否臧兇。
　　九二：在師中，吉無咎，王三錫命。
　　六三：師或輿屍，兇。
　　六四：師左次，無咎。
　　六五：田有禽，利執言，無咎。長子帥師，弟子輿屍，貞兇。
　　上六：大君有命，開國承家，小人勿用。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 7, me);
        check_count(me, 7);
        return;
}