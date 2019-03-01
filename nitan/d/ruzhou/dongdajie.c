inherit ROOM;

void create()
{
        set("short", "東大街");
        set("long", @LONG
這裡是汝州城的東大街，街的北面是一家打鐵舖，西去是汝州城中
心，東面是去往嵩山的東門，南面也沒有什麼店舖。
LONG
        );

        set("exits", ([
                "north" : __DIR__"datiepu",
                "west" : __DIR__"ruzhou",
                "east" : __DIR__"dongmen",
        ]));


        set("outdoors", "ruzhou");
	set("coor/x", -6750);
	set("coor/y", 1860);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
