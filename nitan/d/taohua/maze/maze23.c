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
                "east"  : __DIR__"maze52",
                "south" : __DIR__"maze2",
                "west"  : __DIR__"maze26",
                "north" : __DIR__"maze8",
        ]));

        set("item_desc", ([
                "shibei" : "
　　剝：不利有攸往。
　　初六：剝□以足，蔑貞兇。
　　六二：剝□以辨，蔑貞兇。
　　六三：剝之，無咎。
　　六四：剝□以膚，兇。
　　六五：貫魚，以宮人寵，無不利。
　　上九：碩果不食，君子得輿，小人剝廬。
□  ＝ 爿 ＋ 木
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 23, me);
        check_count(me, 23);
        return;
}