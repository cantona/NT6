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
                "west"  : __DIR__"maze7",
                "north" : __DIR__"maze22",
        ]));

        set("item_desc", ([
                "shibei" : "
　　明夷：利艱貞。
　　初九：明夷于飛，垂其翼。 君子於行，三日不食， 有攸往，主人有
          言。
　　六二：明夷，夷於左股，用拯馬壯，吉。
　　九三：明夷於南狩，得其大首，不可疾貞。
　　六四：入於左腹，獲明夷之心，出於門庭。
　　六五：箕子之明夷，利貞。
　　上六：不明晦，初登於天，後入於地。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 36, me);
        check_count(me, 36);
        return;
}