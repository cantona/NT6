// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "長廊");
        set("long", @LONG
這是一道長長的由翠綠青竹搭成的走廊，周圍種滿翠竹，鳳尾森森，
龍吟細細，令人精神為之一振。不知什麼地方飄來陣陣藥香，似乎有一個
藥房，左面有一間廂房，右面是水龍軒，北面是桃花弟子休息室。
LONG );
         set("exits", ([
                "north" : __DIR__"xiuxishi",
                "west"  : __DIR__"hyjuchu",
                "east"  : __DIR__"shuilong",
                "south" : __DIR__"yaofang",
        ]));
        /*
         set("objects", ([
                __DIR__"obj/tiexiao" : 1,
                __DIR__"obj/zhuxiao" : 2,
                __DIR__"obj/yijing3" : 1,
                __DIR__"obj/yijing4" : 1,
        ]));

        set("no_fight", 1);
        */
        set("coor/x", 8980);
        set("coor/y", -2950);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
        mapping myfam;
        myfam=query("family", me);

        if ( (!myfam || myfam["family_name"] != "桃花島") && dir == "north" )
                return notify_fail("桃花島不留外客，你不能住在這裏！\n");

        if( query("gender", me) == "無性" && dir == "north" )
                return notify_fail("你不能住在這裏！\n");

        return ::valid_leave(me, dir);
}