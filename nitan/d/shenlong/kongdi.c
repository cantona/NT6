inherit ROOM;
 
void create()
{
	set("short", "空地");
	set("long",@LONG
這是一片空地，四周都是亂石，雜草叢生。北邊是一間小屋。南
面是深深的灌木林。東面有一條工整的大道，西面是一片草坪。
LONG);
	set("exits", ([
		"west" : __DIR__"caoping",
		"east" : __DIR__"road",
		"north" : __DIR__"caodi",
		"south" : __DIR__"lin2",
	]) );

	set("objects", ([
		CLASS_D("shenlong")+"/xu": 1,
		__DIR__"npc/dizi": random(3),
	]) );
	set("outdoors", "shenlong");
	setup();
	replace_program(ROOM);
}

