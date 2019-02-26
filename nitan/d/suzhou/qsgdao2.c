// Room: /d/suzhou/qsgdao2.c
// Last Modified by Winder on May. 15 2001
#include <room.h>
inherit BUNCH_ROOM;

void create()
{
        set("short", "青石官道");
        set("long",@long
你走在一條青石大道上，人來人往非常繁忙，不時地有人騎着馬匆
匆而過。大道兩旁有一些小貨攤，似乎是一處集市。北邊通向蘇州城。
long);
        set("outdoors", "suzhou");                        
        set("objects",([
                __DIR__"npc/yetu" : 2,
        ]));
        set("exits",([
                "north" : __DIR__"nanmen",
                "south" : __DIR__"qsgdao1",
        ]));
	set("coor/x", 1110);
	set("coor/y", -1100);
	set("coor/z", 0);
	setup();
}
