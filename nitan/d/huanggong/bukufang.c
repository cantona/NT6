// Room: /d/huanggong/bukufang.c
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "布庫房");
        set("long", @LONG
屋中空空洞洞，牆壁邊倚著幾個牛皮的人形，樑上垂下來幾只大布
袋，裡面似乎裝作米麥或是沙土，此外便只有一張桌子，桌前掛著塊桌
帷。
LONG
        );
        set("exits", ([
                "north"    : __DIR__"ciningmen",
        ]));
        set("objects", ([
                __DIR__"obj/table" :1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7721);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}