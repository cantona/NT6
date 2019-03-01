// Room: /d/yanziwu/path18.c
// Date: Jan.28 2000 by Winder
#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "水邊小路");
        set("long", @LONG
你走在湖邊的小路上。西面幾尺外的灌木叢外，就是太湖水了。湖
水常常淹沒灌木叢，遊魚、水鳥爭嬉獵食，濺起水花陣陣。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"ouxiang1",
                "southeast" : __DIR__"qingfeng",
        ]));
        set("coor/x", 1190);
        set("coor/y", -1240);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}