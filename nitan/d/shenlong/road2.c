inherit ROOM;

void create()
{
	set("short", "山道");
	set("long", @LONG
這是一條狹窄的山道，向着北方一座山峯行去。轉過了幾個山坡，抬
頭遙見峯頂建着幾座大竹屋。
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

