// Room: /d/northft/ftn2.c

inherit ROOM;

void create()
{
	set("short", "青石小路");
	set("long", @LONG
這是奉天城北門外一條青石舖成的小路，南面就是奉天城的
北門了。路邊稀疏的長著一些荒草，路上滿是沙礫，陣陣北風呼
嘯而過，越發給人一種凄涼的感覺。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "south" : __DIR__"ftn1",
  "north" : __DIR__"ftn3",
]));

	set("outdoors", "northft");

	setup();
}
