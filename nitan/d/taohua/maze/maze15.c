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
                "east"  : __DIR__"maze19",
                "west"  : __DIR__"maze2",
                "north" : __DIR__"maze52",
        ]));

        set("item_desc", ([
                "shibei" : "
　　謙：亨，君子有終。
　　初六：謙謙君子，用涉大川，吉。
　　六二：鳴謙，貞吉。
　　九三：勞謙君子，有終吉。
　　六四：無不利，□□謙。
　　六五：不富，以其鄰，利用侵伐，無不利。
　　上六：鳴謙，利用行師，征邑國。
□□  ＝ □＋為
\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 15, me);
        check_count(me, 15);
        return;
}