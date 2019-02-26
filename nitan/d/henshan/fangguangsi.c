inherit ROOM;

void create()
{
        set("short", "方廣寺");
        set("long", @LONG
方廣寺在蓮花峯之下。蓮花峯有八個山頭，猶如金蓮瓣瓣，方廣
寺就建在這蓮花中心的一片平地上。深邃幽雅，有「不遊方廣寺，不
知南嶽之深」之説，故「方廣寺之深」為衡山大四絕之一。
LONG );
        set("exits", ([
                "southdown"  : __DIR__"shanjian",
                "eastup"     : __DIR__"shanlu10",
        ]));

        set("objects", ([
                __DIR__"npc/youke" : 4,
        ]));

        set("outdoors", "henshan");

        set("no_clean_up", 0);

	set("coor/x", -6990);
	set("coor/y", -5550);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}