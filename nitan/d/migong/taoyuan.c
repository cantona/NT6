// taoyuan.c
//tomcat
inherit ROOM;

void create()
{
	set("short", "世外桃源");
	set("long", @LONG
這裡就是世外桃源。
LONG
	);
	set("no_clean_up", 0);

	set("exits",([
	"east" : __DIR__"zhanchang/exit",
]));
set("objects", 
        ([ //sizeof() == 2
                __DIR__"npc/yaowang" : 1,
			 __DIR__"npc/berserker" : 1,
			 __DIR__"npc/dragon" : 1,
                        
        ]));
	setup();
	replace_program(ROOM);
}

