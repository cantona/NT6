// Room: /d/huanggong/youmen.c

inherit ROOM;

void create()
{
        set("short", "右闕門");
        set("long", @LONG
這是通往各部官員朝房的右門. 東廡房設的是吏、戶、禮三部.
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "west"  : __DIR__"dianwai",
                "east"  : __DIR__"hubu",
                "north" : __DIR__"libu",
                "south" : __DIR__"libu2",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2790);
	set("coor/y", 7691);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}