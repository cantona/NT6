inherit ROOM;

void create ()
{
        set ("short","南門");
        set ("long", @LONG
這裏是九江的南門。這裏的行人很多。雖是戰亂年代，但九江還是
很繁華。不時有行人在這裏出出進進，幾個官兵耀武揚威地站在這裏，
檢查着來往的行人。
LONG);

        set("exits", ([
                "north":__DIR__"hzjie5",
        ]));
        set("objects",([
                "/d/city/npc/bing":2,
        ]));
        set("outdoors", "wuchang");

	set("coor/x", -5090);
	set("coor/y", -1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}