// mishi3.c 密室
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "密室");
        set("long", @LONG
這裏是古墓中的密室，四周密不透風，你只能藉着牆上昏暗的燈光
來勉強分辨方向。牆是用整塊的青石砌合起來的，接合的甚是完美，你
難以從中找出一絲縫隙。牆上好像雕有一些圖形。
LONG        );
        set("exits", ([
                "west"  : __DIR__"mishi2",
                "east"  : __DIR__"mishi4",
                "north" : __DIR__"mishi5",
                "south" : __DIR__"mishi6",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3100);
        set("coor/y", 30);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}