inherit ROOM;

void create()
{
        set("short", "武器庫");
        set("long", @LONG
這裏是白駝山弟子的武器庫，白駝山弟子可以到此拿取練功用的
各種武器。不過別派弟子是不允許進來的。
LONG );
        set("exits", ([
                "east" : __DIR__"yuanzi",
        ]));
        set("objects", ([
                __DIR__"npc/shiwei" : 1,
                __DIR__"obj/zheng" : 1,
                "/clone/weapon/gangzhang" : 2,
        ]));
        set("coor/x", -49980);
        set("coor/y", 20010);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}