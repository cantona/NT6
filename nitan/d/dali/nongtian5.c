//Room: /d/dali/nongtian5.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","農田");
        set("long",@LONG
這是一小塊普通的水田，附近有溪流流過，灌溉十分方便。圍繞
農田的是一片片桑林，擺夷人採桑、養蠶，紡織相當精致的絲織品。
西邊有所民居。
LONG);
        set("objects", ([
           __DIR__"npc/nongfu2": 1,
           __DIR__"npc/cow": 1,
        ]));
        set("outdoors", "dalie");
        set("exits",([ /* sizeof() == 1 */
            "south"  : __DIR__"buxiongbu",
            "east"   : __DIR__"langan3",
        ]));
	set("coor/x", -19020);
	set("coor/y", -6900);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}