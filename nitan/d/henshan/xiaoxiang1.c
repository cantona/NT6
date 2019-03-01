inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
這是衡陽城內一條偏僻的小巷，平時很少有人來，只見這條小巷
彎彎曲曲不知道通向何處。
LONG );
        set("outdoors", "henshan");

        set("exits", ([
                "south"  : __DIR__"xiaoxiang2",
                "north"  : __DIR__"hengyang2",
        ]));

	set("coor/x", -6880);
	set("coor/y", -5710);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}