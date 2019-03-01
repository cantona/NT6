// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.
// 增加(discuss <對象> <次數> )功能 

inherit ROOM;

#include "discuss.h"
#include <ansi.h>

void create()
{
        set("short", "練功房");
        set("long", @LONG
這是桃花島弟子的練功房。屋子東半部散放著幾個蒲團，供諸弟子打
坐吐納，調氣養息，修練內功之用。西半部地上則繪著伏羲六十四卦的方
位卦象，大概是修習奇門遁甲所用。書架上有一些經書。
LONG );
         set("exits", ([
                "east" : __DIR__"changlang",
        ]));

         set("objects", ([
                __DIR__"obj/tiexiao" : 1,
                "/clone/weapon/zhuxiao" : 1,
                __DIR__"obj/yijing4" : 1,
                "/clone/misc/bagua"   : 1,
                "/clone/misc/xiang"   : 1,
                "/d/taohua/obj/zhuxiao" : 1,
                "/d/taohua/obj/taojian" : 1,
        ]));

        set("no_fight", 1);
        set("coor/x", 8980);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
//        replace_program(ROOM);
}

void init()
{
        add_action("do_discuss", "discuss");
        add_action("do_answer", "answer");
        add_action("do_answer", "da");
}
