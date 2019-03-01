// Room: /d/northft/ftn7.c

inherit ROOM;

void create()
{
	set("short", "山路");
	set("long", @LONG
這是一條窄窄的上山小路，兩旁怪石嶙峋，中間的路倒是很
平坦，看樣子是被人專門開掘出來的。
LONG
	);
	set("exits", ([ /* sizeof() == 2 */
  "eastup" : __DIR__"ftn8",
  "southwest" : __DIR__"ftn6",
]));

	set("outdoors", "northft");
	setup();
	replace_program(ROOM);
}