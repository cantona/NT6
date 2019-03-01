// Room: /d/yanziwu/path14.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "紅泥小路");
        set("long", @LONG
這是條紅泥小路，在山青水綠的江南，到處都能看到這種紅色的泥
土。走在紅泥路上，襯托著路邊的青草越發綠得可愛。路西緊靠著藕韻
塘岸，一溜的楊柳枝條點擊著水面，帶來無限旖旎情愫。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"path13",
                "southwest" : __DIR__"path15",
        ]));
        set("coor/x", 1260);
        set("coor/y", -1230);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}