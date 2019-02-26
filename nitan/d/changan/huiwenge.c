//Room: huiwenge.c

#include <ansi.h>

inherit ROOM;

void create ()
{
        set ("short", "匯文閣");
        set("long", @LONG
這是一家書局。大堂裏擺了一排排的書櫃，書架上整整齊齊地放
着一些卷軸，堂內還懸掛着幾盆花花草草，紅綠相間，疏密有致，令
人賞心悦目。進來就可以看到一額橫匾：[1；34m         書山有徑勤為路 
        學海無涯苦做舟[2；37；0m
LONG );

        set("exits", 
        ([ //sizeof() == 1
                "west" : "/d/changan/yongtai-dadao3",
        ]));
        set("objects", 
        ([ //sizeof() == 1
                "/d/changan/npc/shuchi" : 1,
        ]));

        set("no_clean_up", 0);
        set("coor/x", -10750);
	set("coor/y", 1930);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}