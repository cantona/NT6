// Room: /d/quanzhou/anhaigang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "安海港");
        set("long", @LONG
安海港是泉州三大港口之一。這裡港闊水深，風平浪靜。極目遠眺，
海天一色，蔚藍無暇。岸邊停靠著密密麻麻的各種船只。東邊有座姑嫂
塔。
LONG );
        set("outdoors", "quanzhou");
        set("exits", ([
                "east"  : __DIR__"gushaota",
                "north" : __DIR__"portroad4",
        ]));
        set("objects", ([
                __DIR__"npc/kuli" : 1,
                "/d/taishan/npc/tiao-fu" : 1,
        ]));
	set("coor/x", -890);
	set("coor/y", -7770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}