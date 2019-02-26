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
                "east"  : __DIR__"maze6",
                "south" : __DIR__"maze28",
                "west"  : __DIR__"maze25",
        ]));

        set("item_desc", ([
                "shibei" : "
　　□①：女壯，勿用取女。
　　初六：繫於金□②，貞吉，有攸往，見兇，羸豕踟躅。
　　九二：包有魚，無咎，不利賓。
　　九三：臀無膚，其行次且，厲，無大咎。
　　九四：包無魚，起兇。
　　九五：以杞包瓜，含章，有隕自天。
　　上九：□①其角，吝，無咎。
□① ＝ 女 ＋ 後
□② ＝ 木 ＋ 尼
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 44, me);
        check_count(me, 44);
        return;
}