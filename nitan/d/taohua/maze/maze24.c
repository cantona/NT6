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
                "east"  : __DIR__"maze46",
                "west"  : __DIR__"maze19",
                "north" : __DIR__"maze27",
        ]));

        set("item_desc", ([
                "shibei" : "
　　復：亨。 出入無疾，朋來無咎。 反復其道，七日來復，利有攸往。
　　初九：不復遠，無只悔，元吉。
　　六二：休復，吉。
　　六三：頻復，厲無咎。
　　六四：中行獨復。
　　六五：敦復，無悔。
    上六：迷復，兇，有災眚。用行師，終有大敗，以其國君，兇；至于
          十年，不克征。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 24, me);
        check_count(me, 24);
        return;
}