// changyinge.c
#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "暢音閣");
        set("long", @LONG
這是宮內最大的戲台, 每逢年節和皇上生日, 帝皇后妃都來這裏看
戲. 平日裏偶爾太后也會來這點上幾摺子看看.
LONG
        );
        set("exits", ([
                "west"  : __DIR__"yangxin2",
                "south" : __DIR__"ningshougong",
        ]));
        set("no_clean_up", 0);
	set("coor/x", -2800);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}