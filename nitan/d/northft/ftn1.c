// Room: /d/northft/ftn1.c

inherit ROOM;

void create()
{
	set("short", "青石小路");
	set("long", @LONG
這是奉天城北門外一條青石鋪成的小路，南面就是奉天城的
北門了。路邊稀疏的長着一些荒草，路上滿是沙礫，陣陣北風呼
嘯而過，越發給人一種淒涼的感覺。
LONG
	);
	set("exits", ([
  "south" : "/d/fengtian/out_fengtian_n",
  "north" : __DIR__"ftn2",
]));

	set("outdoors", "northft");

	setup();
}
