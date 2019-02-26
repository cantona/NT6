// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "小徑");
        set("long", @LONG
這是一條由大青條石鋪成的小路，雖不能説是一塵不染，但也整整潔
潔，看來經常有人打掃。東北面有一個小土丘，西面是一塊草地，東面有
一座樹林。
LONG );
        set("exits", ([
                "west"  : __DIR__"caodi",
                "east"  : __DIR__"shulin",
                "north" : __DIR__"tuqiu",
                "south" : __DIR__"haitan",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9000);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
}