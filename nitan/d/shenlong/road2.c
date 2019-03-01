inherit ROOM;

void create()
{
	set("short", "山道");
	set("long", @LONG
這是一條狹窄的山道，向著北方一座山峰行去。轉過了幾個山坡，抬
頭遙見峰頂建著幾座大竹屋。
LONG );
	set("exits", ([
		"north" : __DIR__"damen",
		"south" : __DIR__"road",
	]));
	set("objects", ([
		__DIR__"npc/dizi": random(4),
		__DIR__"npc/old": random(3),
	]) );
	setup();
	replace_program(ROOM);
}

