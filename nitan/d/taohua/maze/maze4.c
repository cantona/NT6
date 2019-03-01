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
                "east"  : __DIR__"maze22",
                "south" : __DIR__"maze7",
                "west"  : __DIR__"maze18",
                "north" : __DIR__"maze29",
        ]));

        set("item_desc", ([
                "shibei" : "
　　蒙：亨。 匪我求童蒙，童蒙求我。 初噬告，再三瀆，瀆則不告。利
　　    貞。
　　初六：發蒙，利用刑人，用說桎梏，以往吝。
　　九二：包蒙吉；納婦吉；子克家。
　　六三：勿用娶女；見金夫，不有躬，無攸利。
　　六四：困蒙，吝。
　　六五：童蒙，吉。
　　上九：擊蒙；不利為寇，利御寇。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 4, me);
        check_count(me, 4);
        return;
}