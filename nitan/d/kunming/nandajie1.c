#include <ansi.h>
inherit ROOM;

void create()
{
        set("short",  "南大街" );
        set("long", @LONG
你走在昆明最繁華的街道上，人來人往，好不熱鬧，街的
兩旁有許多販賣商品的人，正在販賣一些土特產，沿街有一些
店鋪，西邊是一家當鋪，東邊一個高高的晃字立了出來。
LONG);
        set("outdoors", "kunming");

        set("exits", ([
                "south" : __DIR__"nandajie2", 
                "north" : __DIR__"jinrilou",
                "west"  : __DIR__"dangpu",
                "east" : __DIR__"jiulou",
        ]));
        set("objects", ([
                "/d/beijing/npc/hunhun" : 1,
        ]));
	set("coor/x", -16840);
	set("coor/y", -7220);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}