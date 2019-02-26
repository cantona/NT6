inherit ROOM;

void create()
{
        set("short", "小道");
        set("long", @LONG
這裏是一條林間小道，在樹叢中蜿蜒。東面是嶺南重鎮佛山，西
邊通向廣西。
LONG );
        set("objects", ([
                   __DIR__"obj/shuzhi": 1,
        ]));
        set("outdoors", "foshan");
        set("exits", ([
                    "west" : __DIR__"road6",
                    "east" : __DIR__"westgate",
        ]));
	set("coor/x", -6610);
	set("coor/y", -9750);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}