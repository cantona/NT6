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
                "east"  : __DIR__"maze55",
                "south" : __DIR__"maze59",
                "west"  : __DIR__"maze32",
                "north" : __DIR__"maze64",
        ]));

        set("item_desc", ([
                "shibei" : "
　　解：利西南，無所往，其來複吉。 有攸往，夙吉。
　　初六：無咎。
　　九二：田獲三狐，得黃矢，貞吉。
　　六三：負且乘，致寇至，貞吝。
　　九四：解而拇，朋至斯孚。
　　六五：君子維有解，吉；有孚於小人。
　　上六：公用射隼，於高墉之上，獲之，無不利。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 40, me);
        check_count(me, 40);
        return;
}