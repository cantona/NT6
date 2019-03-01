inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
開封府內西面的主要交通要道，街道兩邊店舖林立，行人車馬如
梭。商販的吆喝，市民與小販的討價還價喧鬧無比。此地向北不遠就
到了延慶觀的大門。
LONG );
        set("objects", ([
                  __DIR__"npc/lisi" : 1,
        ]));
        set("outdoors", "kaifeng");
        set("exits", ([
                  "north" : __DIR__"wroad2",
                  "south" : __DIR__"wroad",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5070);
	set("coor/y", 2230);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}