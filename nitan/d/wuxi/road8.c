// Room: /d/wuxi/road8.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "鄉間小道");
        set("long", @LONG
路兩邊的樹都低矮了許多，許多不知名的小野花在輕風中點來點
去，透過樹枝看到兩邊都是一望無際的田野。你怎麼也不會想到這裏
就是孕育吳越文化的梅村了。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"road7",
                "west"   : __DIR__"road9",
        ]));
        set("objects", ([
                "/d/village/npc/dog" : 1,
        ]));
        set("coor/x", 1030);
	set("coor/y", -790);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}