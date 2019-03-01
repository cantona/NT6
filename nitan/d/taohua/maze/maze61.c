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
                "east"  : __DIR__"maze42",
                "south" : __DIR__"maze60",
                "west"  : __DIR__"maze53",
                "north" : __DIR__"maze54",
        ]));

        set("item_desc", ([
                "shibei" : "
　　中孚：豚魚吉，利涉大川，利貞。
　　初九：虞吉，有他不燕。
　　九二：鳴鶴在陰，其子和之，我有好爵，吾與爾靡之。
　　六三：得敵，或鼓或罷，或泣或歌。
　　六四：月幾望，馬匹亡，無咎。
　　九五：有孚攣如，無咎。
　　上九：翰音登于天，貞兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 61, me);
        check_count(me, 61);
        return;
}