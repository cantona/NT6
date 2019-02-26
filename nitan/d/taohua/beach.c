// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "海濱");
        set("long", @LONG
這裏是一片空闊的海灘。一面是海，一面是一片桃花林。一些大青石
東一塊，西一塊的散放在海灘上。北面是一座高台。
LONG );
         set("exits", ([
                "west"    : __DIR__"citeng",
                "northup" : __DIR__"guanchao",
        ]));
         
        set("objects", ([
                //  __DIR__"obj/shizi" : 3,
        ]));
        
        set("outdoors", "taohua");

        set("coor/x", 9040);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}