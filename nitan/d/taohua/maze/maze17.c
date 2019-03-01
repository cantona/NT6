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
                "east"  : __DIR__"maze28",
                "south" : __DIR__"maze21",
                "west"  : __DIR__"maze58",
                "north" : __DIR__"maze25",
        ]));

        set("item_desc", ([
                "shibei" : "
　　隨：元亨利貞，無咎。
　　初九：官有渝，貞吉。 出門交有功。
　　六二：系小子，失丈夫。
　　六三：系丈夫，失小子。 隨有求得，利居貞。
　　九四：隨有獲，貞兇。有孚在道，以明，何咎。 
　　九五：孚于嘉，吉。
　　上六：拘系之，乃從維之。 王用亨于西山。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 17, me);
        check_count(me, 17);
        return;
}