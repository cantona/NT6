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
                "east"  : __DIR__"maze15",
                "west"  : __DIR__"maze11",
                "north" : __DIR__"maze23",
        ]));

        set("item_desc", ([
                "shibei" : "
　　坤：元，亨，利牝馬之貞。 君子有攸往，先迷後得主，利西南得朋，
      東北喪朋。 安貞，吉。
　　初六：履霜，堅冰至。
　　六二：直，方，大，不習無不利。
　　六三：含章可貞。 或從王事，無成有終。
　　六四：括囊；無咎，無譽。
　　六五：黃裳，元吉。
　　上六：戰龍於野，其血玄黃。
　　用六：利永貞。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 2, me);
        check_count(me, 2);
        return;
}