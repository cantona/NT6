// caoyuana.c 草原
inherit ROOM;
void create()
{
        set("short", "草原邊緣");
        set("long", @LONG
這裡是大草原和沙漠接壤之地，青草由稀至密，向西綿綿延伸而去。
地上有幾行駱駝踏過的蹄印，看樣子這裡常常有商隊來往。西南方好象有
些炊煙。
LONG);
        set("exits", ([
           "east" : __FILE__,
            "southwest" : __DIR__"caoyuan1",
            "northwest" : __DIR__"caoyuan2",
            "northup" : __DIR__"caoyuan3",
            "north" : __DIR__"caoyuan",
            "south" : __DIR__"caoyuan",
        ]));
        set("outdoors", "hasake");
        setup();
}