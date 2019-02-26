// Room: /d/kunlun/bayankala.c
// Last Modified by winder on Nov. 14 2000

#include <ansi.h>
#include <room.h>

inherit ROOM;

void create()
{
        set("short", "巴顏喀拉山");
        set("long",@long
這巴顏喀拉山山勢低平，西接崑崙山埡口，又與通天河支流德曲相
隔，沼澤遍佈。在山腳放眼望去，隨處可見一處處沼澤草甸，乃是放牧
各類牲畜的好地方。遠處散佈着一頂頂牧民的蒙古包。
long);
        set("exits",([
                "west"      : __DIR__"kekexili",
                "southdown" : __DIR__"shanlu2",
                "northwest" : __DIR__"hmszroad1",
        ]));

        set("objects",([
                __DIR__"obj/da-shitou.c" :  1,
        ]));

        set("outdoors", "kunlun");
        set("coor/x", -90000);
        set("coor/y", 10000);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}