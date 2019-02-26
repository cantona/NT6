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
                "east"  : __DIR__"maze29",
                "south" : __DIR__"maze18",
                "west"  : __DIR__"maze3",
                "north" : __DIR__"maze57",
        ]));

        set("item_desc", ([
                "shibei" : "
　　井：改邑不改井，無喪無得，往來井井。汔至，亦未□①井，羸其瓶，
        兇。
　　初六：井泥不食，舊井無禽。
　　九二：井谷射鮒，甕敝漏。
　　九三：井渫不食，為我民惻，可用汲，王明，並受其福。
　　六四：井□②，無咎。
　　九五：井冽，寒泉食。
　　上六：井收勿幕，有孚無吉。
□②  ＝ 上 秋 下 瓦
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 48, me);
        check_count(me, 48);
        return;
}