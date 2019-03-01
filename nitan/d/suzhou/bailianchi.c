// Room: /d/suzhou/bailianchi.c
// Date: May 31, 98  Java

inherit ROOM;

void create()
{
        set("short", "白蓮池");
        set("long", @LONG
白蓮池位于二仙亭的北面，池中種有千葉蓮花，池上架彩蓮曲橋，
相傳吳王夫差與西施曾在此採蓮賞荷。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("exits", ([
                "south" : __DIR__"erxianting",
        ]));
        set("objects", ([
                __DIR__"npc/lady2" : 1,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1030);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}