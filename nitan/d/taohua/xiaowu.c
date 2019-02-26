inherit ROOM;

void create()
{
        set("short", "小屋");
        set("long", @LONG
這是專供僕人休息的小屋。屋裏放着五六張牀，擠擠地佔
掉了屋子的一大半地方。屋角很散亂地放了一些日常生活用具。
中央放着一張桌子，上面擺一茶壺和幾個杯子。
LONG);
        set("exits", ([
                "east"  : __DIR__"houyuan",
        ]));
        set("objects", ([
                __DIR__"npc/puren" : 3,
        ]));    

        set("sleep_room", 1);
        setup();
        replace_program(ROOM);
}