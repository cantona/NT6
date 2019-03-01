#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "祝融殿");
        set("long", @LONG
祝融殿，又名老聖殿，祠火神祝融。花崗石砌牆，鐵瓦覆頂，殿
宇凌空傲雪，巍然屹立在衡山絕頂。殿門的石楹上刻著有「[1；37m寅賓日出，
峻極于天[2；37；0m」的字樣，遠遠看去字峰雄渾而有力。殿上還立有「[1；31m聖德重
華[2；37；0m」的楣額。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"wangritai",
                "northdown"  : __DIR__"wangyuetai",
                "westup"     : __DIR__"shanlu003",
                "east"       : __DIR__"changlang",
        ]));

        set("objects", ([
                CLASS_D("henshan") + "/mi" : 1,
                CLASS_D("henshan") + "/first" : 1,
                __DIR__"npc/dizi1"   : 4,
                __DIR__"npc/xiangke" : 2,
        ]));
        set("no_clean_up", 0);
	set("coor/x", -6930);
	set("coor/y", -5490);
	set("coor/z", 40);
	setup();

        "/clone/board/henshan_b"->foo();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir == "northdown" || dir == "southdown"
           || ! objectp(guard = present("mi weiyi", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}
