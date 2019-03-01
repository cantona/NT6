// Room: /d/huanggong/zuomen.c

inherit ROOM;

void create()
{
        set("short", "左闕門");
        set("long", @LONG
這是通往各部官員朝房的左門. 西廡房設的是兵、刑、工三部.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "east"  : __DIR__"dianwai",
                "west"  : __DIR__"xingbu",
                "north" : __DIR__"bingbu",
                "south" : __DIR__"gongbu",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2810);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}