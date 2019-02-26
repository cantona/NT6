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
                "east"  : __DIR__"maze45",
                "south" : __DIR__"maze14",
                "north" : __DIR__"maze1",
        ]));

        set("item_desc", ([
                "shibei" : "
　　□①：揚於王庭，孚號，有厲，告自邑，不利即戎，利有攸往。
　　初九：壯於前趾，往不勝為吝。
　　九二：惕號，莫夜有戎，勿恤。
　　九三：壯於□②，有兇。 君子□①□①，獨行遇雨，若濡有愠，無咎。
　　九四：臀無膚，其行次且。 牽羊悔亡，聞言不信。
　　九五：莧陸□①□①，中行無咎。
　　上六：無號，終有兇。
□① ＝ 炔 － 火
□② ＝ 九 ＋ 頁
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 43, me);
        check_count(me, 43);
        return;
}