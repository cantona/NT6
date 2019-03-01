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
                "east"  : __DIR__"maze47",
                "south" : __DIR__"maze50",
                "west"  : __DIR__"maze17",
                "north" : __DIR__"maze44",
        ]));

        set("item_desc", ([
                "shibei" : "
  　大過：棟橈，利有攸往，亨。
　　初六：藉用白茅，無咎。
　　九二：枯楊生□，老夫得其女妻，無不利。
　　九三：棟橈，兇。
　　九四：棟隆，吉；有它吝。
　　九五：枯楊生華，老婦得士夫，無咎無譽。
　　上六：過涉滅頂，兇，無咎。
□□ ＝ 禾 ＋ 弟
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 28, me);
        check_count(me, 28);
        return;
}