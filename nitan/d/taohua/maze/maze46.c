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
                "east"  : __DIR__"maze7",
                "west"  : __DIR__"maze24",
                "north" : __DIR__"maze18",
        ]));

        set("item_desc", ([
                "shibei" : "
　　升：元亨，用見大人，勿恤，南征吉。
　　初六：允升，大吉。
　　九二：孚乃利用□，無咎。
　　九三：升虛邑。
　　六四：王用亨於岐山，吉無咎。
　　六五：貞吉，升階。
　　上六：冥升，利於不息之貞。
□  ＝ 礻 ＋ 龠
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 46, me);
        check_count(me, 46);
        return;
}