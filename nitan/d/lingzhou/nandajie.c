// Room: /lingzhou/nandajie.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "南大街");
        set("long", @LONG
這裏是靈州南大街，也是商業最繁華的地段，一眼望去只見街兩旁
店鋪林立，五顏六色的店招和旗幟在陽光的照耀下分外鮮明，街上行人
很是不少，西面是一家酒館，東面是一家車馬店。
LONG );
        set("exits", ([
                "south" : __DIR__"nanmen",
                "north" : __DIR__"center",
                "east"  : __DIR__"chema",
                "west"  : __DIR__"jiuguan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");
        set("coor/x", -6275);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}