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
                "east"  : __DIR__"maze59",
                "south" : __DIR__"maze48",
                "west"  : __DIR__"maze42",
                "north" : __DIR__"maze32",
        ]));

        set("item_desc", ([
                "shibei" : "
　　巽：小亨，利攸往，利見大人。
　　初六：進退，利武人之貞。
　　九二：巽在□下，用史巫紛若，吉無咎。
　　九三：頻巽，吝。
　　六四：悔亡，田獲三品。
　　九五：貞吉悔亡，無不利。 無初有終，先庚三日，後庚三日，吉。
　　上九：巽在□下，喪其資斧，貞兇。
□  ＝ 爿 ＋ 木
\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 57, me);
        check_count(me, 57);
        return;
}