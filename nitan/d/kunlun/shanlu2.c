// Room: /d/kunlun/shanlu2.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西域山路");
        set("long",@long
漸行漸西，天氣一天冷似一天，西域崑崙派勢力雄強，沿途倒並無
什麼強盜，只是黃沙撲面，寒風透骨，卻也着實難熬。
long);
        set("exits",([
                "eastdown" : __DIR__"shanlu1",
                "northup"  : __DIR__"bayankala",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -90000);
        set("coor/y", 5000);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}