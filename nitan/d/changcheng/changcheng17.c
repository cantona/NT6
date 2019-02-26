// Room: /d/changcheng/changcheng17.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
你已經繞過了倒塌的城牆，有回到了長城上。站在堅實的城磚上，
你高興的唱起歌來“萬里長城永不倒。。。。。。”，歌聲在空曠的山
上傳了很遠，很遠。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "westup"    :__DIR__"changcheng18",
                "southdown" :__DIR__"changcheng16",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -13000);
        set("coor/y", 11000);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}