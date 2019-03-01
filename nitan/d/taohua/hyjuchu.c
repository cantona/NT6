// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "黃藥師居處");
        set("long", @LONG
這是桃花島主黃藥師的臥室，一張竹榻靠在屋東北角，窗前一幾，幾
上一張瑤琴，一本琴譜。瑤琴顏色黯舊，琴尾已完全燒焦，琴譜裡夾著一
張紙，可以看見一些字跡。向窗外望去，隱隱可以看見一座墳塋。
LONG );
        set("objects", ([
                // __DIR__"obj/paper2"       : 1,
                CLASS_D("taohua") + "/huang" : 1,
                "/d/taohua/npc/shitong" : 2,
        ]));
         set("exits", ([
                "south" : __DIR__"wofang",
                "east" : __DIR__"changlang2",
        ]));
        
        set("coor/x", 8970);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
         "/clone/board/taohua_b"->foo();
}
int valid_leave(object me, string dir)
{
        object guarder;

        if (! objectp(guarder = present("huang yaoshi", this_object())))
        {
                return 1;
        }

        if (dir == "south")
                return guarder->permit_pass(me, dir);

        return 1;
}
