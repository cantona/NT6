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
                "south" : __DIR__"maze22",
                "west"  : __DIR__"maze29",
                "north" : __DIR__"maze37",
        ]));

        set("item_desc", ([
                "shibei" : "
　　既濟：亨，小利貞，初吉終亂。
　　初九：曳其輪，濡其尾，無咎。
　　六二：婦喪其□①，勿逐，七日得。
　　九三：高宗伐鬼方，三年克之，小人勿用。
　　六四：□②有衣□③，終日戒。
　　九五：東鄰殺牛，不如西鄰之□④祭，實受其福。
　　上六：濡其首，厲。
□① ＝ 上髟 下弗
□② ＝ 糹 ＋ 需
□③ ＝ 衤 ＋ 如
□④ ＝ 礻 ＋ 龠
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 63, me);
        check_count(me, 63);
        return;
}