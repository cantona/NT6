inherit ROOM;

void create()
{
        set("short", "打鐵舖");
        set("long", @LONG
這是一家生意興隆的打鐵舖，中心擺著一個火爐，爐火把四周照得一
片通紅，你一走進去就感到渾身火熱。牆角堆滿了已完工和未完工的菜刀、
鐵錘、鐵棍、匕首、盔甲等物。一位鐵匠滿頭大汗揮舞著鐵錘，專心致志
地在打鐵。洛陽城裡的習武之人都喜歡在這裡打造稱手的鐵器。牆上有塊
牌子(paizi)。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "east" : __DIR__"sroad5",
        ]));
        set("item_desc",([
                "paizi" : "修補武器防具(repair xxx)。\n",
        ]));
        set("objects", ([
                __DIR__"npc/smith" : 1,
        ]));
	set("coor/x", -7000);
	set("coor/y", 2130);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}