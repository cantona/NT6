// Room: /d/kunlun/shanlu1.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "西域山路");
        set("long",@long
漸行漸西，天氣一天冷似一天，西域昆侖派勢力雄強，沿途倒並無
什麼強盜，只是黃沙撲面，寒風透骨，卻也著實難熬。
long);
        set("exits",([
                "westup" : __DIR__"shanlu2",
                "east"   : __DIR__"shanlu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "kunlun");
        set("coor/x", -80000);
        set("coor/y", 5000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}