inherit ROOM;

void create()
{
        set("short", "走廊");
        set("long", @LONG
這是商家堡內的一條木制的走廊，紅漆地面很是光滑，整個
走廊被打整得一塵不染。你不時能夠看到幾個商家堡的家丁在此
走動，忙碌個不停。
LONG);
        set("exits", ([
                "north"  : __DIR__"shang_houyuan",
                "south"  : __DIR__"shang_zoulang1",
        ]));
	set("coor/x", -6750);
	set("coor/y", 1910);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}