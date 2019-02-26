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
                "east"  : __DIR__"maze38",
                "south" : __DIR__"maze62",
                "west"  : __DIR__"maze35",
                "north" : __DIR__"maze31",
        ]));

        set("item_desc", ([
                "shibei" : "
　　旅：小亨，旅貞吉。
　　初六：旅瑣瑣，斯其所取災。
　　六二：旅即次，懷其資，得童僕貞。
　　九三：旅焚其次，喪其童僕，貞厲。
　　九四：旅於處，得其資斧，我心不快。
　　六五：射雉一矢亡，終以譽命。
　　上九：鳥焚其巢，旅人先笑後號啕。 喪牛於易，兇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 56, me);
        check_count(me, 56);
        return;
}