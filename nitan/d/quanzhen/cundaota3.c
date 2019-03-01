// cundaota3.c 存道塔三層
// Winder Oct.10 1998

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "存道塔三層");
        set("long", @LONG
這裏是存道塔的三層，塔梯繞着塔內向塔頂延伸。這裏空空如
也，經書也許全被全真弟子們借去閲讀了。
LONG
        );
        set("exits", ([
                "westup" : __DIR__"cundaota4",
                "westdown" : __DIR__"cundaota2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -2780);
        set("coor/y", 130);
        set("coor/z", 190);
        setup();
        replace_program(ROOM);
}