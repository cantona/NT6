// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條平緩的山路，你慢慢向上行去，山路兩旁種植著鬆柏樺之類
的高大喬木，間雜以各種罕見藥草，如靈芝、首烏之類。越往上行，山路
越見陡峭，但幸好還不算太難走。
LONG );
         set("exits", ([
                "south"   : __DIR__"citeng",
                "northup" : __DIR__"shanlu2",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}