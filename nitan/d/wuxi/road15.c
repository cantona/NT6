// Room: /d/wuxi/road15.c
// Winder 2000/02/22 

inherit ROOM;
#include <ansi.h>;
void create()
{
        set("short", "山路");
        set("long", @LONG
山路曲曲折折，四周花草成叢，林蔭茂盛。仰身長嘯，但聽空山
鳥語。回音陣陣。山下天下第二泉早已沒入一片密密的竹林之中，再
向山上就快要到惠山的頂峰了。
LONG );
        set("outdoors", "wuxi");
        set("no_clean_up", 0);
        set("exits", ([
                "northup"    : __DIR__"huishan",
                "southdown"  : __DIR__"huishanquan",
        ]));
        set("coor/x", 990);
	set("coor/y", -710);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}