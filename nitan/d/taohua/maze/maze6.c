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
                "east"  : __DIR__"maze13",
                "south" : __DIR__"maze47",
                "west"  : __DIR__"maze44",
        ]));

        set("item_desc", ([
                "shibei" : "
　　訟：有孚，窒。 惕中吉。 終兇。 利見大人，不利涉大川。
　　初六：不永所事，小有言，終吉。
　　九二：不克訟，歸而逋，其邑人三百户，無眚。
　　六三：食舊德，貞厲，終吉，或從王事，無成。
　　九四：不克訟，復自命，渝安貞，吉。
　　九五：訟元吉。
　　上九：或錫之□帶，終朝三褫之。

□  ＝ 上般 下革
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 6, me);
        check_count(me, 6);
        return;
}