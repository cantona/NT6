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
                "east"  : __DIR__"maze30",
                "south" : __DIR__"maze40",
                "west"  : __DIR__"maze50",
                "north" : __DIR__"maze47",
        ]));

        set("item_desc", ([
                "shibei" : "
　　未濟：亨，小狐汔濟，濡其尾，無攸利。
　　初六：濡其尾，吝。
　　九二：曳其輪，貞吉。
　　六三：未濟，徵兇，利涉大川。
　　九四：貞吉，悔亡，震用伐鬼方，三年有賞於大國。
　　六五：貞吉，無悔，君子之光，有孚，吉。
　　上九：有孚於飲酒，無咎，濡其首，有孚失是。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 64, me);
        check_count(me, 64);
        return;
}