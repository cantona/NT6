inherit ROOM;

void create()
{
        set("short", "打鐵舖");
        set("long", @LONG
這是一家簡陋的打鐵舖，中心擺著一個火爐，爐火把四周照得一
片通紅，你一走進去就感到渾身火熱。牆角堆滿了已完工和未完工的
菜刀、鐵錘、鐵棍、匕首、盔甲等物。一位鐵匠滿頭大汗揮舞著鐵錘，
專心致志地在打鐵。
LONG );
        set("exits", ([
                "west" : __DIR__"nandajie1",
        ]));
        set("objects", ([
                 __DIR__"npc/smith": 1,
        ]));
        set("coor/x", -7090);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}