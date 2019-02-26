// Room: /d/changcheng/changcheng18.c
// Last Modified by Winder on Aug. 25 2000

#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "長城");
        set("long", WHT @LONG
你已經繞過了倒塌的城牆，又回到了長城上。站在堅實的城磚上，
你高興的唱起歌來“萬里長城永不倒。。。。。。”，歌聲在空曠的山
上傳了很遠，很遠。
LONG
NOR );
        set("outdoors", "changcheng");
        set("exits", ([
                "southwest"  :__DIR__"changcheng19",
                "eastdown"   :__DIR__"changcheng17",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -14000);
        set("coor/y", 11000);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}