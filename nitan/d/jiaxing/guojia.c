// Room: /d/jiaxing/guojia.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "郭家民房");
        set("long", @LONG
這是一座廢棄已久的民房，家具擺設一應俱全，只是都附著一層灰
土。屋子中間是一張小桌，桌上的杯碗還都沒有撤去，看來主人去的很
匆忙。
LONG
        );
        set("exits", ([
                "south" : __DIR__"njroad2",
        ]));
        set("no_clean_up", 0);

	set("coor/x", 1260);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}