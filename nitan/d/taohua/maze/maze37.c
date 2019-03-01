// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from the
// Slough develop group

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
                "south" : __DIR__"maze63",
                "west"  : __DIR__"maze59",
                "north" : __DIR__"maze55",
        ]));

        set("item_desc", ([
                "shibei" : "
　　家人：利女貞。
　　初九：閒有家，悔亡。
　　六二：無攸遂，在中饋，貞吉。
　　九三：家人□□，悔厲吉；婦子嘻嘻，終吝。
　　六四：富家，大吉。
　　九五：王假有家，勿恤吉。
　　上九：有孚威如，終吉。
□  ＝ 口 ＋ 高
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 37, me);
        check_count(me, 37);
        return;
}