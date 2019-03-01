inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
你走在一條碎石鋪成的大道上。四周的田野已經被積雪覆蓋，放眼望去
發現自己已經置身於無邊無際的雪原中。狂風夾雜着雪花呼嘯而過，凍得人
渾身發抖。北面的天邊似乎有一縷炊煙升起。
LONG );
        set("exits", ([
                "north" : __DIR__"muqiao",
                "south" : __DIR__"road7",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 3990);
	set("coor/y", 9210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}