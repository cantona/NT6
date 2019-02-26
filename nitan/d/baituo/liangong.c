inherit ROOM;

void create()
{
        set("short", "練功場");
        set("long", @LONG
這裏是白駝山弟子的練功場。東邊是一個練功房。北邊是個門廊，
西邊連着一條長廊，雕樑畫柱，非常氣派。南面可見巍巍大廳。
LONG );
        set("outdoors", "baituo");
        set("exits", ([
                "east"  : __DIR__"fang",
                "north" : __DIR__"menlang",
                "west"  : __DIR__"changlang",
                "south" : __DIR__"dating",
        ]));
        set("objects", ([
                __DIR__"npc/li" : 1,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        // replace_program(ROOM);
}

int valid_leave(object me, string dir)
{
    object guarder;

    if (objectp(guarder = present("li guanjia", this_object())) &&
        (dir == "east" || dir == "west"))
    {
        return guarder->permit_pass(me, dir);
    }

    return 1;
}
