//room: qinyun.c

inherit ROOM;

void create()
{
        set("short","琴韻小築");
        set("long", @LONG
這是一間小巧玲瓏的房舍，頗為精雅。周圍稀稀落落的四五間小
房屋，建造在一個不知是小島還是半島上。
LONG );
        set("exits", ([
                "westdown"  : __DIR__"muti",
                "east"      : __DIR__"xiaoting",
                "south"     : __DIR__"neitang",
        ]));

        set("objects", ([
                 __DIR__"npc/bao"  : 1,
                __DIR__"npc/feng" : 1,
        ]));

        setup();
}

int valid_leave(object me, string dir)
{
        object guard;

        if (dir != "east"
           || ! objectp(guard = present("bao butong", this_object())))
                return ::valid_leave(me, dir);

        return guard->permit_pass(me, dir);
}

