// Room: /d/yanziwu/path22.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青草路");
        set("long", @LONG
走在青草路上，腳下踩著軟軟的小草，滿目的清亮透綠，鼻子裡聞
著青青的春泥香味，你想：哦，這就是江南。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"  : __DIR__"path23",
                "west"     : __DIR__"path21",
                "east"     : __DIR__"path25",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1270);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}