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
                "east"  : __DIR__"maze16",
                "south" : __DIR__"maze9",
                "north" : __DIR__"maze14",
        ]));

        set("item_desc", ([
                "shibei" : "
　　大壯：利貞。
　　初九：壯于趾，征兇，有孚。
　　九二：貞吉。
　　九三：小人用壯，君子用罔，貞厲。 羝羊觸藩，羸其角。
　　九四：貞吉悔亡，藩決不羸，壯于大輿之□。
　　六五：喪羊于易，無悔。
　　上六：羝羊觸藩，不能退，不能遂，無攸利，艱則吉。
□  ＝ 車 ＋ 復
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 34, me);
        check_count(me, 34);
        return;
}