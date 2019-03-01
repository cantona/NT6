// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是桃花島弟子的休息室。幾張木床整整齊齊的排列于屋角，茶幾花
瓶中插著幾枝疏密相間的新開桃花，散發出陣陣花香。地下纖塵不染，看
來是常常打掃。
LONG );

        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits", ([
                "south" : __DIR__"changlang2",
        ]));
        set("coor/x", 8980);
        set("coor/y", -2940);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}