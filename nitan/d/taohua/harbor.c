// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "港灣");
        set("long", @LONG
這是一個不大的港灣，裡面已大大小小的停泊著六七艘船。另有一艘
大船船尾高聳，形象華美，船身漆得金碧輝煌，象是新打造好的，但卻遠
遠停在一旁，不知作什麼用。這裡有幾個啞巴水手忙來忙去，都不願理你。
LONG );

        set("outdoors", "taohua");

        set("exits", ([
                "east" : __DIR__"shucong",
                "north" : __DIR__"enter_m",
        ]));

        set("item_desc", ([
                "chuan" : "這是一艘海船，可載人渡海，但是船家在平時也用它來打魚。\n",
        ]));

        set("coor/x", 8970);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}