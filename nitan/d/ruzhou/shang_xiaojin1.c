inherit ROOM;

void create()
{
        set("short", "碎石小徑");
        set("long", @LONG
商家堡廣場後面的一條碎石鋪砌的小徑，可以由它前往商家
堡的大廳所在。不時有商家堡的下人過往於此。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_xiaojin2",
                "south"  : __DIR__"shang_qgc",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}