// Room: /u/a/agah/kezhan2.c

inherit ROOM;

void create()
{
        set("short", "客棧二樓");
        set("long", @LONG
這裡是二樓雅座，比起樓下就要高雅多了，景德鎮的餐具，紅木的桌
椅，在光照之下反射出淡淡的的光澤。推窗望去，洛陽城中心盡收眼底。
一群酒客推杯換盞，正喝的熱鬧。四周是客房，供人睡覺休息之用。
LONG
        );
        set("no_clean_up", 0);
        set("exits", ([ /* sizeof() == 5 */
  "east" : __DIR__"kefang1",
  "down" : __DIR__"kezhan",
  "south" : __DIR__"kefang2",
  "west" : __DIR__"kefang3",
  "north" : __DIR__"kefang4",
]));

	set("coor/x", -6980);
	set("coor/y", 2170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}