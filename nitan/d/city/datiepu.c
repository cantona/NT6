// Room: /city/datiepu.c
// sun
inherit ROOM;

void create()
{
        set("short", "打鐵舖");
        set("long", @LONG
這是一家簡陋的打鐵舖，中心擺著一個火爐，爐火把四周照得一
片通紅，一走進去就感到渾身火熱。牆角堆滿了已完工和未完工的菜
刀、鐵錘、鐵棍、匕首、盔甲等物。一位鐵匠滿頭大汗揮舞著鐵錘，
專心致志地在打鐵。
LONG );

        set("exits", ([
                "south" : "/d/city/wofang",
                "north" : "/d/city/dongdajie2",
        ]));
        set("objects", ([
                 "/d/city/npc/smith": 1,]));

	set("coor/x", 20);
	set("coor/y", -10);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{

        if( query_temp("smith_times", me) && dir == "north" )
                return notify_fail("你已經答應幫鐵匠打鐵了，不要到處亂跑。\n");

        if( !query_temp("smith_times", me) && dir == "south" )
                return notify_fail("不要在別人家裡亂躥！\n");

        return ::valid_leave(me, dir);
}