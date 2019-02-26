// Room: /d/fuzhou/biaojuzt.c
// Date: may.12 1998 Java

inherit ROOM;

void create()
{
        set("short", "正廳");
        set("long", @LONG
這裏是福威鏢局的正廳，幾隻太師椅一字排開，正中央坐着總鏢頭，
手持煙袋杆正在閉目沉思。牆上掛着幾幅字畫和一把寶劍。
LONG );
        set("exits", ([
                "north" : __DIR__"biaojuhy",
                "south" : __DIR__"biaojudy",
                "west"  : __DIR__"biaojunz",
                "east"  : __DIR__"biaojuzf",
        ]));
        set("objects", ([
                __DIR__"npc/linzhennan" : 1,
        ]));
	set("coor/x", -101);
	set("coor/y", -6161);
	set("coor/z", -1);
	setup();
        replace_program(ROOM);
}