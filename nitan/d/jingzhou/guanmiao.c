inherit ROOM;

void create()
{
        set("short", "關聖廟");
        set("long", @LONG
相傳關老爺子舊年曾在這裡和周倉爭關廟首席之位。周倉說提議
誰先跑到廟裡，誰就為大。關公答應後，待周倉跑到門口大叫：別佔
我的門旮。周倉本是你說不，我偏要之人，往門旮旮一站，關公也就
到前面去了。這些不表，且看這廟裡，香火繚繞，長年不斷，來進香
的人絡繹不絕，也可知關二爺在當地人心中是多英雄的人物。
LONG );
        set("exits", ([
                "south" : __DIR__"xidajie2",
                "north" :__DIR__"houdian",
        ]));
        set("objects", ([
                "/d/beijing/npc/xiangke" : 1,
        ]));
        set("coor/x", -7120);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}