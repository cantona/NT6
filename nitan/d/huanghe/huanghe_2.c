// Room: /huanghe/huanghe_2.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河");
        set("long", @LONG
黃河出了青海，經甘肅之後，向東受到黃土高原的阻擋，轉而向東
北流去。在流經黃土高原的過程中泥沙含量猛增，水色澄黃，就被稱為
黃河。
LONG );
        set("exits", ([
                "west"      : __DIR__"huanghe_3",
                "northeast" : __DIR__"huangtu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -4000);
        set("coor/y", 400);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}