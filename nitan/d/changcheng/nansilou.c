// Room: /d/changcheng/nansilou.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "南四樓");
        set("long", WHT@LONG
一旦爬上十分陡峭的南四樓，你終於知道了“不到長城非好漢”的
況味了。疲憊之餘，臨風怡然遠眺，東邊是三十里長的關溝，似乎近在
咫尺。南面羣山萬壑之外，就是京城了。
LONG
NOR  );
        set("outdoors", "changcheng");
        set("exits", ([
                "eastdown"  :__DIR__"changcheng22",
                "northdown" :__DIR__"beisilou",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 2000);
        set("coor/y", 5000);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}