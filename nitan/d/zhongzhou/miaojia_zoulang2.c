inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條木制的走廊，地面很是光滑，被打整得一塵不染。
幾個苗家的丫鬟在此走動。走廊的北邊是一個院子。
LONG);
        set("exits", ([
                  "south" : __DIR__"miaojia_houting",
                  "north" : __DIR__"miaojia_houyuan",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8990);
	set("coor/y", -950);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}