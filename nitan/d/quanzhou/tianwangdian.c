// Room: /d/quanzhou/tianwangdian.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "天王殿");
        set("long", @LONG
走入山門即是天王殿。左右塑天王坐像各一尊，怒目挺腰，狀極威
猛。殿後則是一片寬敞的大石庭，通往後面的大雄寶殿。
LONG );
        set("exits", ([
                "south" : __DIR__"kaiyuansi",
                "north" : __DIR__"dxbaodian",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/shami" : 1,
        ]));
	set("coor/x", -920);
	set("coor/y", -7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}