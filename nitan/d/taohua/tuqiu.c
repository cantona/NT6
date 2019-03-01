// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "小土丘");
        set("long", @LONG
走到這裡，地勢才略見起伏。土丘之上雖然沒有什麼高大樹木，但碧
草茵茵，間雜著一些奇花異草，散發出陣陣沁人心肺的異香，令人精神為
之一振。居高臨下朝北邊望去似乎有一片小小竹林。
LONG );
         set("exits", ([
                "south" : __DIR__"xiaojing",
                "north" : __DIR__"zhulin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}