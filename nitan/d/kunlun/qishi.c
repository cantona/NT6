// Room: /d/kunlun/qishi.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short", "棋室");
        set("long", @LONG
昆侖三聖以“琴”、“棋”、“劍”著稱，奕棋是每個昆侖弟子入
門必修的功課。此處是昆侖派的棋室，供昆侖弟子磨練棋藝使用。
LONG );
        set("exits",([
                "west" : __DIR__"jiashan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -119970);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}