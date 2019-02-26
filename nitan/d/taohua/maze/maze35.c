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
                "east"  : __DIR__"maze56",
                "south" : __DIR__"maze16",
                "west"  : __DIR__"maze14",
                "north" : __DIR__"maze45",
        ]));

        set("item_desc", ([
                "shibei" : "
　　晉：康侯用錫馬蕃庶，晝日三接。
　　初六：晉如，摧如，貞吉。 罔孚，裕無咎。
　　六二：晉如，愁如，貞吉。 受茲介福，於其王母。
　　六三：眾允，悔亡。
　　九四：晉如碩鼠，貞厲。
　　六五：悔亡，失得勿恤，往吉無不利。
　　上九：晉其角，維用伐邑，厲吉無咎，貞吝。
\n",
        ]));
        
        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 35, me);
        check_count(me, 35);
        return;
}