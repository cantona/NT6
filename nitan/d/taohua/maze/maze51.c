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
                "east"  : __DIR__"maze32",
                "south" : __DIR__"maze42",
                "west"  : __DIR__"maze54",
                "north" : __DIR__"maze21",
        ]));

        set("item_desc", ([
                "shibei" : "
　　震：亨。 震來□①□①，笑言啞啞。 震驚百里，不喪匕鬯。
　　初九：震來□①□①，後笑言啞啞，吉。
　　六二：震來厲，億喪貝，躋於九陵，勿逐，七日得。
　　六三：震蘇蘇，震行無眚。
　　九四：震遂泥。
　　六五：震往來厲，億無喪，有事。
　　上六：震索索，視矍矍，徵兇。 震不於其躬，於其鄰，無咎。 婚媾
          有言。
□① ＝ 左上小 左中曰 左下小 右虎
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 51, me);
        check_count(me, 51);
        return;
}