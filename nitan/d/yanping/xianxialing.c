// Room: /d/yanping/xianxialing.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "仙霞嶺");
        set("long", @LONG
這裏就是閩浙分水的仙霞嶺。向陽的坡面鬱鬱葱葱，長滿了長長的
馬尾松。沿途的山路十分難行，來往的口音也漸漸帶有閩音，越來越難
以辯識了。
LONG );
        set("exits", ([
                "northdown" : "/d/jiaxing/jnroad4",
                "south"     : __DIR__"erbapu",
        ]));
        set("objects", ([
                "/d/wudang/npc/yetu" : 2,
        ]));
        set("outdoors", "jiangnan");
        set("coor/x", 1500);
        set("coor/y", -3000);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}