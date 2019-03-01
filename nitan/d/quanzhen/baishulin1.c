// baishulin1.c 柏樹林
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "柏樹林");
        set("long", @LONG
繞過翠屏谷的山壁，眼前是一片大柏樹林，想是由于山壁擋住了
視線，在山下的山路上根本想不到這裡的柏樹竟會有這麼密這麼高。
你踏進柏樹林中，陽光全被頭頂的樹葉遮住了，越往樹林深處，光線
越是幽暗。
LONG
        );
        set("outdoors", "zhongnan");
        set("exits", ([
                "southdown" : __DIR__"cuipinggu",
                "northup" : __DIR__"baishulin3",
                "east" : __DIR__"baishulin2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -3140);
        set("coor/y", 30);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}