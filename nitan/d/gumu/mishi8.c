// mishi8.c 密室
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裡是古墓中的密室，四周密不透風，你只能借著牆上昏暗的燈光
來勉強分辨方向。牆是用整塊的青石砌合起來的，接合的甚是完美，你
難以從中找出一絲縫隙。密室中擺放著一些簡單的家居用具，原來這是
古墓派祖師林朝英的居室。
LONG        );
        set("exits", ([
                "west" : __DIR__"mishi7",
                "out"  : "/d/city/guangchang",
        ]));
        set("objects", ([
                CLASS_D("gumu")+"/lin" : 1,
        ]));
        set("coor/x", -3000);
        set("coor/y", 0);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}