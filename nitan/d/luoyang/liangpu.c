inherit ROOM;

void create()
{
        set("short", "糧鋪");
        set("long", @LONG
這家糧鋪是洛陽城附近唯一的一家糧鋪，靠近武德道，街道另一邊便
是官府。由此可見官府管理甚嚴。當地居民買米買面都要到這裏來買，所
以生意興隆，客源滾滾。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"nroad2",
        ]));
        set("objects", ([
                __DIR__"npc/liangcao" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}