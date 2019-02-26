inherit ROOM;

void create()
{
        set("short", "南大街");
        set("long", @LONG
這裏是汝州城的南大街。北去是汝州城中心，東面是紅娘莊，西面
也沒有什麼店鋪，南面是汝州的南城門。
LONG
        );

        set("exits", ([
                "north" : __DIR__"ruzhou",
                "south" : __DIR__"nanmen",
                "east"  : __DIR__"hong-damen",
        ]));

        set("outdoors", "ruzhou");
	set("coor/x", -6760);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
