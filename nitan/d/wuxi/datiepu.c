// Room: /d/wuxi/datiepu.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "打鐵鋪");
        set("long", @LONG
這是一家簡陋的打鐵鋪，中心擺着一個火爐，爐火把四周照得一片
通紅，你一走進去，就感到渾身火熱。牆角堆滿了已完工和未完工的菜
刀、鐵錘、鐵棍、匕首、盔甲等物。一位鐵匠滿頭大汗揮舞着鐵錘，專
心致志地在打鐵。
LONG );
        set("exits", ([
                "north" : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/d/city/npc/smith": 1,
        ]));
        set("coor/x", 1060);
	set("coor/y", -740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}