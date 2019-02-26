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
                "east"  : __DIR__"maze54",
                "south" : __DIR__"maze53",
                "west"  : __DIR__"maze16",
                "north" : __DIR__"maze56",
        ]));

        set("item_desc", ([
                "shibei" : "
　　小過：亨，利貞，可小事，不可大事。飛鳥遺之音，不宜上宜下，大
          吉。
　　初六：飛鳥以兇。
　　六二：過其祖，遇其妣；不及其君，遇其臣；無咎。
　　九三：弗過防之，從或戕之，兇。
　　九四：無咎，弗過遇之。 往厲必戒，勿用永貞。
　　六五：密雲不雨，自我西郊，公弋取彼在穴。
　　上六：弗遇過之，飛鳥離之，兇，是謂災眚。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 62, me);
        check_count(me, 62);
        return;
}