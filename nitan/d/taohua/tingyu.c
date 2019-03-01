// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;
int do_jump(string arg);

void create()
{
        set("short", "聽魚石");
        set("long", @LONG
這裡已接近碧波池的中心，一塊形如臥獅的大石立于水畔，側面有兩
個大篆--“聽魚”。大概因為經常有人使用，石面已經十分光滑。池中白
蓮盛放，清香陣陣，蓮葉田田。你在石上坐了下來，一陣微風拂過，池中
荷葉倏倏作響，幾尾金色錦鯉戲于荷間。北面池中央有一間重檐六角亭(t
ing)，可是似乎無路通向此亭。
LONG );

        set("item_desc", ([
                "ting" : "亭上一匾，依稀可以看出上有“試劍亭”三字。\n"
                         "你看看距離不算太遠，應該可以用輕功飛掠(fly)過去。\n",
        ]));
        /*        
        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));
        */
        set("exits", ([
                "west"  : __DIR__"bibochi",
                "south" : __DIR__"zhulin3",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -2960);
        set("coor/z", 0);
        setup();

}

void init()
{
        add_action("do_jump", "fly");
}

int do_jump(string arg)
{
        object me = this_player();

        if ( !arg || arg != "ting" )
                return notify_fail( "什麼？\n");

        message_vision("$N縱身往試劍亭跳去。\n", me);
        if ( me->query_skill("dodge",1) <= 50 ) {
                message_vision("$N一個不留神，“噗□”一聲掉進水裡，吃了一嘴爛泥。\n", me);
                message_vision("$N落湯雞似的從池子裡爬起來，滿足的抹了抹嘴。\n", me);
        }

        if ( me->query_skill("dodge",1) > 50 ) {
                me->move(__DIR__"shijian");
                message("vision", me->name() + "縱身由聽魚石跳了過來。\n",environment(me), ({me}) );
        }

        return 1;
}