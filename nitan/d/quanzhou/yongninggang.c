// Room: /d/quanzhou/yongninggang.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "永寧港");
        set("long", @LONG
永寧港是泉州三大港口之一。這裡港闊水深，風平浪靜。極目遠眺，
海天一色，蔚藍無暇。岸邊停靠著密密麻麻的各種船只。南邊的姑嫂塔
流傳著一個感人的故事。
LONG );
        set("outdoors", "quanzhou");
        set("no_clean_up", 0);
        set("exits", ([
                "south"       : __DIR__"gushaota",
                "northwest"   : __DIR__"portroad4",
        ]));
        set("objects", ([
                __DIR__"npc/kuli" : 1,
                "/d/taishan/npc/tiao-fu" : 1,
                "/maze/binghuodao/npc/xiexiao-shi" : 1,
        ]));
        set("no_fight", 1);
	set("coor/x", -880);
	set("coor/y", -7770);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
