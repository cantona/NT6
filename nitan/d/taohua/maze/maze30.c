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
                "south" : __DIR__"maze55",
                "west"  : __DIR__"maze64",
                "north" : __DIR__"maze49",
        ]));

        set("item_desc", ([
                "shibei" : "
　　離：利貞，亨。 畜牝牛，吉。
　　初九：履錯然，敬之無咎。
　　六二：黃離，元吉。
　　九三：日昃之離，不鼓缶而歌，則大耋之嗟，兇。
　　九四：突如其來如，焚如，死如，棄如。
　　六五：出涕沱若，戚嗟若，吉。
　　上九：王用出征，有嘉折首，獲其匪醜，無咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 30, me);
        check_count(me, 30);
        return;
}