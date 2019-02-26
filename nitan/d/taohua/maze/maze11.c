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
                "east"  : __DIR__"maze2",
                "north" : __DIR__"maze26",
        ]));

        set("item_desc", ([
                "shibei" : "
　　泰：小往大來，吉亨。
　　初九：拔茅茹，以其夤，徵吉。
　　九二：包荒，用馮河，不遐遺，朋亡，得尚於中行。
　　九三：無平不陂，無往不復，艱貞無咎。 勿恤其孚，於食有福。
　　六四：翩翩不富，以其鄰，不戒以孚。
　　六五：帝乙歸妹，以祉元吉。
　　上六：城復於隍，勿用師。 自邑告命，貞吝。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 11, me);
        check_count(me, 11);
        return;
}