// Copyright (C) 2003, by Lonely. All rights reserved.
// This software can not be used, copied, or modified 
// in any form without the written permission from authors.

inherit ROOM;

void create()
{
        set("short", "樹叢");
        set("long", @LONG
這是一片花樹繁密的樹叢，枝葉密密重重，一眼望去，除了花樹還是
花樹，完全看不清對面。突然，前面約莫兩丈遠處一對眼睛碧瑩瑩的閃閃
發光。你大吃一驚，往後跳開幾步，那眼睛卻一閃就不見了。你有點害怕，
還是回去吧。
LONG );
        set("exits", ([
                "north" : __DIR__"shidong",
                     "east"  : __DIR__"caodi",
                "west"  : __DIR__"harbor",
        ]));

        set("objects", ([
                __DIR__"obj/taoshu" : 1,
        ]));

        set("outdoors", "taohua");

        set("coor/x", 8980);
        set("coor/y", -3000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}