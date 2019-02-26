// Room: /d/yanziwu/path25.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青草路");
        set("long", @LONG
走在青草路上，腳下踩着軟軟的小草，滿目的清亮透綠，鼻子裏聞
着青青的春泥香味，你想：哦，這就是江南。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "west"     : __DIR__"path22",
                "east"     : __DIR__"garden",
        ]));
        set("coor/x", 1220);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}