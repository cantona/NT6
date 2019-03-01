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
                "east"  : __DIR__"maze25",
                "south" : __DIR__"maze58",
                "west"  : __DIR__"maze33",
        ]));

        set("item_desc", ([
                "shibei" : "
　　履：履虎尾，不□□人，亨。
　　初九：素履，往無咎。
　　九二：履道坦坦，幽人貞吉。
　　六三：眇能視，跛能履，履虎尾，□□人，兇。 武人為于大君。
　　九四：履虎尾，□□□□終吉。
　　九五：□□履，貞厲。
　　上九：視履考祥，其旋元吉。
□□  ＝ 口 ＋ 至
□□ ＝ 上朔 ＋ 下心
□□  ＝ 炔 － 火 
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 10, me);
        check_count(me, 10);
        return;
}