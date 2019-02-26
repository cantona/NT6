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
                "east"  : __DIR__"maze62",
                "south" : __DIR__"maze20",
                "west"  : __DIR__"maze34",
                "north" : __DIR__"maze35",
        ]));

        set("item_desc", ([
                "shibei" : "
　　豫：利建侯行師。
　　初六：鳴豫，兇。
　　六二：介於石，不終日，貞吉。
　　六三：盱豫，悔。 遲有悔。
　　九四：由豫，大有得。勿疑。 朋盍簪。
　　六五：貞疾，恆不死。
　　上六：冥豫，成有渝，無咎。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 16, me);
        check_count(me, 16);
        return;
}