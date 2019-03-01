// Room: /d/yanziwu/path23.c
// Date: Jan.28 2000 by Winder

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "青草路");
        set("long", @LONG
沿著青草路，慢慢爬上蔓陀山峰。腳下踩著軟軟的小草，滿目的清
亮透綠，鼻子裡聞著青青的春泥香味，你想：哦，這就是江南。
LONG );
        set("outdoors", "mantuo");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"   : __DIR__"path24",
                "southdown" : __DIR__"path22",
        ]));
        set("coor/x", 1210);
        set("coor/y", -1260);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}