// Room: /d/suzhou/.c
// Last Modified by winder on Mar. 8 2001

inherit ROOM;

void create()
{
        set("short", "內宅");
        set("long", @LONG
這裏是衙門的內宅，住着知府的家眷。外人到此就該止步了。
LONG
        );

        set("exits", ([
                "south" : __DIR__"yamen",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1100);
	set("coor/y", -1030);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}