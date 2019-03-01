inherit ROOM;

void create()
{
        set("short", "馬莊大院");
        set("long", @LONG
你走進大院，迎面是一個假山水池，池上擺著一塊奇形怪
狀的石頭，據說是當年花石綱的遺石。水池的兩旁種滿了花草。
東邊是一棵槐樹，鬱鬱蔥蔥，遮蓋了大半個院子。前方是一條
長廊走道通往後院，有幾個丐幫弟子把守。
LONG);
        set("outdoors", "yangzhou");
        set("region", "yangzhou");
        set("exits", ([
                "east"  : __DIR__"ma_chufang",
                "south" : __DIR__"ma_houyuan",
                "north" : __DIR__"ma_damen",
        ]));
        set("objects", ([
                "/d/gaibang/npc/3dai" : 1,
                "/d/gaibang/npc/4dai" : 1,
        ]));
	set("coor/x", 30);
	set("coor/y", -20);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}