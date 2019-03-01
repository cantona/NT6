// Room: /d/suzhou/beidajie1.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
你走在一條繁忙的街道上，看著操著南腔北調的人們行色匆匆，許
多人都往南邊走去，那裡有一個熱鬧的亭子。西南面是一家戲園子，不
時傳來叫好聲，來自各地的人們進進出出。在東面是一個客店。西面是
一個馬廄。
LONG );
        set("outdoors", "suzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "east"      : __DIR__"kedian",
                "west"      : __DIR__"majiu",
                "north"     : __DIR__"beidajie2",
                "south"     : __DIR__"canlangting",
                "southwest" : __DIR__"xiyuan",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}