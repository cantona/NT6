inherit ROOM;

void create()
{
        set("short", "庭院");
        set("long", @LONG
這是一個不大的庭院，庭院的中央有一條碎石舖成的小路，
四周種著幾株小樹。西面是一間寬大的正廳，南面是出售
藥材及成藥的南廳，北面是藥舖帳房的北廳。
LONG );

        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"beiting",
                "south" : __DIR__"nanting",
                "west" : __DIR__"zhengting",
                "east" : __DIR__"huichun",
        ]));
        set("objects", ([
                __DIR__"npc/zhanggui" : 1,
        ]));
        set("outdoors", "yaowang");
        setup();
        replace_program(ROOM);
}
