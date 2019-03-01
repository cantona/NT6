// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是一道長長的由翠綠青竹搭成的走廊，周圍種滿翠竹，鳳尾森森，
龍吟細細，令人精神為之一振。前面不知什麼地方飄來一股香氣，你不由
得有點餓了，左右兩面分別是桃花島弟子的練功房，南面是水龍軒。
LONG );
         set("exits", ([
                "south" : __DIR__"shuilong",
                "north" : __DIR__"chufang",
                "west"  : __DIR__"liangong1",
                "east"  : __DIR__"liangong2",
        ]));
        /*
         set("objects", ([
                __DIR__"obj/tiexiao" : 1,
                __DIR__"obj/zhuxiao" : 2,
                __DIR__"obj/yijing3" : 1,
                __DIR__"obj/yijing4" : 1,
        ]));

        set("no_fight", 1);
        */
        
        set("coor/x", 8990);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}