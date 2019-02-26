// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
山路走到這裏已非常陡峭，山路也東彎西曲，盤旋往復，好不怪異，
每走幾步都要費不少力氣。抬頭望去，上面已是峯頂。
LONG );
         set("exits", ([
                "southdown" : __DIR__"shanlu1",
                "northup"   : __DIR__"tzfeng",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9030);
        set("coor/y", -2980);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}