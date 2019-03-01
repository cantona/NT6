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
                "east"  : __DIR__"maze61",
                "south" : __DIR__"maze39",
                "west"  : __DIR__"maze20",
                "north" : __DIR__"maze62",
        ]));

        set("item_desc", ([
                "shibei" : "
　　漸：女歸吉，利貞。
　　初六：鴻漸于幹，小子厲，有言，無咎。
　　六二：鴻漸于磐，飲食□□，吉。
　　九三：鴻漸于陸，夫征不復，婦孕不育，兇；利御寇。
　　六四：鴻漸于木，或得其桷，無咎。
　　九五：鴻漸于陵，婦三歲不孕，終莫之勝，吉。
　　上九：鴻漸于逵，其羽可用為儀，吉。
□  ＝ 彳 ＋ 幹 ＋ 亍
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 53, me);
        check_count(me, 53);
        return;
}