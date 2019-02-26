// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "石洞");
        set("long", @LONG
樹叢之後是一塊光禿禿的石壁，四周無花無樹，與其他地方形成強烈
反差。石壁上有一個巖洞，巖洞裏黑黝黝的，看不清楚到底有什麼，但似
乎有人影晃動。
LONG );

         set("exits", ([
                "south" : __DIR__"shucong",
        ]));


        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -2990);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}