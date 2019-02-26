// Room: /d/wuxi/road17.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "山道");
        set("long", @LONG
山路翻上了山坡，反面覺得平坦些。從這裏向西北去，還要走不
少這裏的山路，真有些留戀江南的繁華。山道旁樹木葱葱，景緻還算
怡人，只是略顯荒涼而已。
LONG );
        set("outdoors", "yixing");
        set("no_clean_up", 0);
        set("exits", ([
                "southdown" : __DIR__"road16",
                "northwest" : "/d/yixing/shanlu2",
        ]));
        set("coor/x", 980);
	set("coor/y", -720);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}