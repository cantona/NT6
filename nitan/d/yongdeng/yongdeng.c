// Room: /huanghe/yongdeng.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "永登");
        set("long", @LONG
這裏就是西北的軍事重鎮永登。一座孤城聳立在茫茫荒野之上。此
城建於漢光武年間，據聞大將軍霍去病曾在此練兵三年，後一舉平定大
西北。歷代而來，這裏都有軍隊長駐。
LONG );
        set("exits", ([
                "southup" : "/d/xingxiu/xxroad3",
                "north"   : __DIR__"gulang",
                "southeast"    : "/d/huanghe/huanghe_3",
                "west"    : __DIR__"kedian",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 4,
        ]));
        set("outdoors", "yongdeng");
        set("coor/x", -16110);
	set("coor/y", 4200);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}