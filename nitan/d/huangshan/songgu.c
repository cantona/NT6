// Room: /d/huangshan/songgu.c
// Last Modified by winder on Sep. 27 2001
inherit ROOM;
void create()
{
        set("short", "鬆谷庵");
        set("long", @LONG
長長的石階，沿途盡是茂林修竹，樹枝上掛著雲霧草，越發增加了
清涼幽靜的感覺，和前面的險峻截然不同。走完石階便是鬆谷庵，這是
一座明代的道觀，庵前翠竹如海，諸潭環布，景色清幽至極。後面便是
五龍潭和翡翠池。
LONG
        );
        set("exits", ([ 
                "north"  : __DIR__"feicui",
                "south"  : __DIR__"diezhang",
                "eastup" : __DIR__"caishi",
        ]));
        set("outdoors", "huangshan");
        set("no_clean_up", 0);
        set("coor/x", -605);
        set("coor/y", -970);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}