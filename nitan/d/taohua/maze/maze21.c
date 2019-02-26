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
                "east"  : __DIR__"maze50",
                "south" : __DIR__"maze51",
                "west"  : __DIR__"maze38",
                "north" : __DIR__"maze17",
        ]));

        set("item_desc", ([
                "shibei" : "
  　噬嗑：亨。 利用獄。
　　初九：履校滅趾，無咎。
　　六二：噬膚滅鼻，無咎。
　　六三：噬臘肉，遇毒；小吝，無咎。
　　九四：噬乾□，得金矢，利艱貞，吉。
　　六五：噬乾肉，得黃金，貞厲，無咎。
　　上九：何校滅耳，兇。
□  ＝ 月 ＋ 姊 － 女
\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 21, me);
        check_count(me, 21);
        return;
}