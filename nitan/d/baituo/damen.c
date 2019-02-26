inherit ROOM;

void create()
{
        set("short", "大門");
        set("long", @LONG
這就是聞名天下的白駝山莊的大門。只見大門樑上雕龍刻鳳，美
奐美崙，不知凝聚着多少能工巧匠的心血。更顯出莊主的富有與顯貴。
門前左右各蹲着一隻威武莊嚴的石獅子。
LONG );
        set("outdoors", "baituo");

        set("exits", ([
                "north" : __DIR__"yuanzi",
                "southdown" : __DIR__"shijie",
        ]));

        set("objects", ([
                CLASS_D("ouyang") + "/first" : 1,
                __DIR__"npc/menwei" : 2,
        ]));
        set("coor/x", -49970);
        set("coor/y", 20000);
        set("coor/z", 20);
        setup();
}

int valid_leave(object me, string dir)
{
        object guarder;

        if (objectp(guarder = present("men wei", this_object()))
           && dir == "north")
                return guarder->permit_pass(me, dir);

        return 1;
}
