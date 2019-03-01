// Room: /d/xiangyang/walls8.c
// Date: Jan. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "南城頭");
        set("long", @LONG
這裡是襄陽的南城頭。一些宋兵正在城頭巡邏，一個牙將
正在這兒負責接受各種守城材料，一些弓箭手正拈弓搭箭緊盯
著城下的動靜。
LONG );
        set("outdoors", "xiangyang");

        set("exits", ([
                "northeast" : __DIR__"walle7",
                "westdown"  : __DIR__"walls6",
        ]));
        set("objects", ([
                __DIR__"npc/ya"   : 1,
                __DIR__"npc/bing" : 2,
        ]));
        set("coor/x", -7780);
	set("coor/y", -810);
	set("coor/z", 40);
	setup();
        replace_program(ROOM);
}