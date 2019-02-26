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
                "east"  : __DIR__"maze31",
                "south" : __DIR__"maze35",
                "west"  : __DIR__"maze43",
                "north" : __DIR__"maze12",
        ]));

        set("item_desc", ([
                "shibei" : "
　　萃：亨。 王假有廟，利見大人，亨，利貞。 用大牲吉，利有攸往。
　　初六：有孚不終，乃亂乃萃，若號一握為笑，勿恤，往無咎。
　　六二：引吉，無咎，孚乃利用□①。
　　六三：萃如，嗟如，無攸利，往無咎，小吝。
　　九四：大吉，無咎。
　　九五：萃有位，無咎。 匪孚，元永貞，悔亡。
　　上六：□②諮涕□③，無咎。
□① ＝ 礻 ＋ 龠
□② ＝ 繁體字 齊 下半部 丿和丨 間夾一貝字
□③ ＝ 氵 ＋ 夷
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 45, me);
        check_count(me, 45);
        return;
}