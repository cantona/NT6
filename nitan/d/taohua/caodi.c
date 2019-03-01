// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "草地");
        set("long", @LONG
這是一塊極普通的草地，地上只有一些尋常隨處可見的小石子和小樹
枝。東面有一條小徑，西面是茂密的樹林，北面則是一座鬆柏林，鬆柏林
中一條小路蜿蜒向北，不知所終。
LONG );
         set("exits", ([
                "west"  : __DIR__"shucong",
                "east"  : __DIR__"xiaojing",
                "north" : __DIR__"songlin",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8990);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}