// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
這是一片普通樹林，與島上一入就迷失方向的桃林不大一樣。林中一
條小路橫貫東西。東北面地勢越來越高，似乎有座山峯；往東走樹林愈現
茂密，看來不太好走。
LONG );
         set("exits", ([
                "west" : __DIR__"shulin",
                "east" : __DIR__"citeng",
        ]));

        set("outdoors", "taohua");

        set("coor/x", 9020);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}