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
                "east"  : __DIR__"maze48",
                "south" : __DIR__"maze27",
                "west"  : __DIR__"maze60",
                "north" : __DIR__"maze42",
        ]));

        set("item_desc", ([
                "shibei" : "
　　屯：元，亨，利，貞，勿用，有攸往，利建侯。
　　初九：磐桓；利居貞，利建侯。
　　六二：屯如□如，乘馬班如。 匪寇婚媾，女子貞不字，十年乃字。
　　六三：既鹿無虞，惟入於林中，君子幾不如舍，往吝。
　　六四：乘馬班如，求婚媾，無不利。
  　九五：屯其膏，小貞吉，大貞兇。
　　上六：乘馬班如，泣血漣如。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 3, me);
        check_count(me, 3);
        return;
}