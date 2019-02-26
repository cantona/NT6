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
                "east"  : __DIR__"maze18",
                "south" : __DIR__"maze24",
                "west"  : __DIR__"maze41",
                "north" : __DIR__"maze3",
        ]));

        set("item_desc", ([
                "shibei" : "
　　頤：貞吉。 觀頤，自求口實。
　　初九：舍爾靈龜，觀我朵頤，兇。
　　六二：顛頤，拂經，於丘頤，徵兇。
　　六三：拂頤，貞兇，十年勿用，無攸利。
　　六四：顛頤吉，虎視眈眈，其欲逐逐，無咎。
　　六五：拂經，居貞吉，不可涉大川。
 　 上九：由頤，厲吉，利涉大川。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 27, me);
        check_count(me, 27);
        return;
}