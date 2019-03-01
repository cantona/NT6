// Room: /d/quanzhou/shangu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
在壑幽林美，山清氣爽的山谷中，座落著一座寺院。門前的對聯寫
著：

              神靈體正勝佛國，地寂境幽似西天

這是一座石砌廟宇，建築小巧玲瓏。周圍蒼鬆翠柏，又增幾分靜穆。此
乃是摩尼教的所在。摩尼教是波斯人摩尼創立的宗教，又稱為「明教」。
摩尼教徒主要食素，被世人傳為「食菜事魔」，稱之為「魔教」。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "enter" : __DIR__"caoan",
                "north" : __DIR__"shisun",
        ]));
	set("coor/x", -930);
	set("coor/y", -7740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}