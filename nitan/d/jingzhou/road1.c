inherit ROOM;

void create()
{
        set("short", "大道");
        set("long", @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。往東通向脂粉
之都的襄陽，折向西南則通往西南重鎮荊洲。
LONG );
        set("exits", ([
                "northeast" : "/d/xiangyang/caodi6",
                "southwest" : __DIR__"road2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "city");

        set("coor/x", -300);
        set("coor/y", -160);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
