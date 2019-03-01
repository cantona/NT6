// Room: /d/kunlun/qinshi.c
// Last Modified by winder on Nov. 15 2000

#include <ansi.h>
inherit ROOM;

void create ()
{
        set("short", "琴室");
        set("long", @LONG
昆侖三聖以“琴”、“棋”、“劍”著稱，奕棋是每個昆侖弟子入
門必修的功課。此處是昆侖派的琴室，供昆侖弟子磨練琴藝使用。
LONG);
        set("exits",([
                "east" : __DIR__"liangting",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -120010);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}