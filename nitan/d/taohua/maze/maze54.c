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
                "east"  : __DIR__"maze51",
                "south" : __DIR__"maze61",
                "west"  : __DIR__"maze62",
                "north" : __DIR__"maze38",
        ]));

        set("item_desc", ([
                "shibei" : "
　　歸妹：徵兇，無攸利。
　　初九：歸妹以娣，跛能履，徵吉。
　　九二：眇能視，利幽人之貞。
　　六三：歸妹以須，反歸以娣。
　　九四：歸妹愆期，遲歸有時。
　　六五：帝乙歸妹，其君之袂，不如其娣之袂良，月幾望，吉。
　　上六：女承筐無實，士□羊無血，無攸利。
□  ＝ 圭 ＋ 刂
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 54, me);
        check_count(me, 54);
        return;
}