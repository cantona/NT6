// Room: /d/jiaxing/yangjia.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "楊家民房");
        set("long", @LONG
這是一座廢棄已久的民房，傢俱擺設一應俱全，只是都附着一層灰
土。屋子中間是一張小桌，桌上的杯碗還都沒有撤去，看來主人去的很
匆忙。牆上掛着一杆鐵槍。
LONG
        );
        set("item_desc", ([
                "qiang" :  "一杆用舊了的鐵槍，看起來原來應該有一對的，不知為何只剩了一杆。",
                "tieqiang" : "一杆用舊了的鐵槍，看起來原來應該有一對的，不知為何只剩了一杆。",
        ]) );
        set("exits", ([
                "south" : __DIR__"njroad3",
        ]));
        set("no_clean_up", 0);
	set("coor/x", 1270);
	set("coor/y", -1810);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}