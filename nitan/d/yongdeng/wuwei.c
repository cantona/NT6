// Room: /huanghe/wuwei.c
// Java Sep. 22 1998

#include <room.h>

inherit ROOM;

void create()
{
        set("short", "武威");
        set("long", @LONG
武威是西夏國的西南重鎮，駐有重兵，城樓高達三丈，門口有兩排
官兵正在認真的盤查過往行人，城門口的告示上畫著最近通緝的江洋大
盜的圖形，城裡頭看上去還挺熱鬧。東南就是去永登的方向了，西南面
就是祁連山脈。
LONG );
        set("exits", ([
                "southeast" : __DIR__"wuqiao",
                "north"     : __DIR__"tumenzi",
        ]));
        set("objects", ([
                __DIR__"npc/xixiabing" : 3,
        ]));
        set("outdoors", "yongdeng");
        set("coor/x", -16110);
	set("coor/y", 4240);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}