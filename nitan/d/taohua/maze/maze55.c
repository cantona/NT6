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
                "south" : __DIR__"maze37",
                "west"  : __DIR__"maze40",
                "north" : __DIR__"maze30",
        ]));

        set("item_desc", ([
                "shibei" : "
　　豐：亨，王假之，勿憂，宜日中。
　　初九：遇其配主，雖旬無咎，往有尚。
　　六二：豐其□①，日中見鬥，往得疑疾，有孚發若，吉。
　　九三：豐其沛，日中見昧，折其右肱，無咎。
　　九四：豐其□①，日中見鬥，遇其夷主，吉。
　　六五：來章，有慶譽，吉。
　　上六：豐其屋，□①其家，窺其户，□②其無人，三歲不見，兇。
□① ＝ 上艹 下部
□② ＝ 外門 內臭  闃的誤筆?
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 55, me);
        check_count(me, 55);
        return;
}