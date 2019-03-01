// Room: /yangzhou/zizaiting.c
// Last Modified by Winder on Jul. 20 2000

inherit ROOM;

void create()
{
        set("short","觀自在亭");
        set("long",@LONG
琴室東南湖岸邊，舊有御碑亭一座，現故址重修為“觀自在亭”，
內置石桌、石凳，以觀水景。
LONG );
        set("outdoors", "shouxihu");
        set("exits", ([
                "northwest"  : __DIR__"qinshi1",
        ]));
        set("objects", ([
                "/d/city/npc/lady2" : 1,
        ]));
        set("coor/x", 30);
        set("coor/y", 90);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}