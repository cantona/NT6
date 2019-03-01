// Room: /d/northft/ftn13.c

inherit ROOM;

void create()
{
	set("short", "小徑");
	set("long", @LONG
這是一條窄窄的上山小路，兩旁怪石嶙峋，中間的路倒是很
平坦，看樣子是被人專門開掘出來的。向東望去是一大片亂石崗。
LONG
	);
	set("exits", ([
	"west" : __DIR__"ftn12",
	"east" : __DIR__"iron_mine/entry",
]));

	setup();
	replace_program(ROOM);
}
