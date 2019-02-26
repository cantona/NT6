inherit ROOM;

void create()
{
        set("short", "老僧書店");
        set("long", @LONG
這裏的老闆剛從南陽搬來，聽説以前他曾在嵩山少林寺出過家，後不
知什麼原因又還了俗，專門賣書為生。只見書店面積很大，以前曾是一座
勾欄。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"wroad7",
        ]));
        set("objects", ([
                __DIR__"npc/shudianboss" : 1,
        ]));

	set("coor/x", -7040);
	set("coor/y", 2190);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}