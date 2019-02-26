// Room: /d/huanggong/guoshiguan.c

inherit ROOM;

void create()
{
        set("short", "國史館");
        set("long", @LONG
國史館是翰林儒臣們奉敕纂修國史等書的常設機構. 這裏的藏書頗
多. 主要是方誌和史書.
LONG
        );
        set("exits", ([
                "northwest"  : __DIR__"wenhua",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2780);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}