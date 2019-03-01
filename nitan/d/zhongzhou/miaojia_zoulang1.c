inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是一條木制的走廊，地面很是光滑，被打整得一塵不染。
幾個苗家的丫鬟在此走動。走廊的兩邊分接正廳和後廳。
LONG);
        set("exits", ([
                  "east"  : __DIR__"miaojia_houting",
                  "west" : __DIR__"miaojia_zhengting",
                  "north" : __DIR__"miaojia_jushi",
        ]));
        set("objects", ([
                __DIR__"npc/yahuan" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -9000);
	set("coor/y", -960);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}