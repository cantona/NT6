// Room: /d/wuxi/northroad2.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "北大街");
        set("long", @LONG
青磚街道由於有條小河從底下穿過有點起伏。北邊可以看到通向城
外的北城門。東邊是當地武館，不少喜愛拳腳或是有大志於胸的青年往
往到這裏去學些防身技能。西邊是參和堂，一股濃濃的煎草藥味常常不
時地從藥鋪裏傳出來，南邊通向市中心，人非常地多。
LONG );
        set("outdoors", "wuxi");
        set("exits", ([
                "north" : __DIR__"northgate",
                "south" : __DIR__"jinlianqiao",
                "east"  : __DIR__"wuguan",
                "west"  : __DIR__"canhetang",
        ]));
        set("objects", ([
                        "/d/village/npc/kid" : 1,
        ]));
        set("coor/x", 1040);
	set("coor/y", -700);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}