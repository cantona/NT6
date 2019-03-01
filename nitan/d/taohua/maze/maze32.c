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
                "east"  : __DIR__"maze40",
                "south" : __DIR__"maze57",
                "west"  : __DIR__"maze51",
                "north" : __DIR__"maze50",
        ]));

        set("item_desc", ([
                "shibei" : "
　　恆：亨，無咎，利貞，利有攸往。
　　初六：濬恆，貞兇，無攸利。
　　九二：悔亡。
　　九三：不恆其德，或承之羞，貞吝。
　　九四：田無禽。
　　六五：恆其德，貞，婦人吉，夫子兇。
　　上六：振恆，兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 32, me);
        check_count(me, 32);
        return;
}