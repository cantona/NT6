// Room: /d/kunlun/houting.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "後廳");
        set("long", @LONG
這裡是後客廳，裡面簡單，只有幾張軟榻，供疲憊的客人歇息，屋
子裡烤著火，暖烘烘的。
LONG );
        set("exits",([
                "north" : __DIR__"huayuan",
                "south" : __DIR__"jiuqulang5",
                "west"  : __DIR__"liangting",
                "east"  : __DIR__"jiashan",
        ]));
        set("no_fight",1);
        set("outdoors", "kunlun");
        set("no_clean_up", 0);
        set("coor/x", -119990);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}