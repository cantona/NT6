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
                "east"  : __DIR__"maze27",
                "south" : __DIR__"maze19",
                "west"  : __DIR__"maze52",
                "north" : __DIR__"maze60",
        ]));

        set("item_desc", ([
                "shibei" : "
　　損：有孚，元吉，無咎，可貞，利有攸往？  曷之用，二簋可用享。
　　初九：已事遄往，無咎，酌損之。
　　九二：利貞，征兇，弗損益之。
　　六三：三人行，則損一人；一人行，則得其友。
　　六四：損其疾，使遄有喜，無咎。
　　六五：或益之，十朋之龜弗克違，元吉。
　　上九：弗損益之，無咎，貞吉，利有攸往，得臣無家。
\n",
        ]));

        setup();
}

void init()
{
        object me;
        me = this_player();
        
        addn_temp("taohua/count", 41, me);
        check_count(me, 41);
        return;
}