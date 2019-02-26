// Room: /d/yanziwu/path12.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "紅泥小路");
        set("long", @LONG
這是條紅泥小路，在山青水綠的江南，到處都能看到這種紅色的泥
土。走在紅泥路上，襯托着路邊的青草越發綠得可愛。路南緊靠着藕韻
塘岸，一溜的楊柳枝條點擊着水面，帶來無限旖旎情愫。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "east"   : __DIR__"path13",
                "west"   : __DIR__"path11",
        ]));
        set("coor/x", 1250);
        set("coor/y", -1220);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}