inherit ROOM;

void create()
{
        set("short", "西大街");
        set("long", @LONG
開封府內西面的主要交通要道，街道兩邊店鋪林立，行人車馬如
梭。商販的吆喝，市民與小販的討價還價喧鬧無比。西面就是延慶觀，
東面可以上到角樓。
LONG );
        set("objects", ([
                  __DIR__"npc/qigai" : 1,
        ]));
        set("outdoors", "kaifeng");
        set("exits", ([
                  "eastup" : __DIR__"jiaolou",
                  "west" : __DIR__"yanqing",
                  "north" : __DIR__"wroad3",
                  "south" : __DIR__"wroad1",
        ]));
        set("no_clean_up", 0);

	set("coor/x", -5070);
	set("coor/y", 2240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}