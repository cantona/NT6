//Room: nanan-dadao.c

inherit ROOM;

void create ()
{
        set ("short", "南安大道");
        set("long", @LONG
長安城的主街南安大道頗為熱鬧，除了本城的居民外，還有不少
外來的旅客和商人。南安大道再向南就是長安城的南城門，往北是故
皇宮的青龍街。
LONG );
        set("exits", 
        ([ //sizeof() == 2
                "south" : "/d/changan/nanan-daokou",
                "north" : "/d/changan/qinglong2",
                "east"  : __DIR__"gongbu",
        ]));

        set("outdoors", "changan");
        set("coor/x", -10720);
	set("coor/y", 1900);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}