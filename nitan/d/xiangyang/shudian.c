// Room: /d/xiangyang/shudian.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "書店");
        set("long", @LONG
這裏的老闆剛從南陽搬來，聽説以前他曾在嵩山少林寺出過家，
後不知什麼原因又還了俗，專門賣書為生。只見書店面積很大，以前
曾是一座勾欄。
LONG );
        set("exits", ([
                "east" : __DIR__"westroad2",
        ]));
        set("objects", ([
                __DIR__"npc/shudianboss" : 1,
        ]));
        set("coor/x", -7840);
	set("coor/y", -750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}