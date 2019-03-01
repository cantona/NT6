// Room: /d/huanggong/ciningmen.c
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "慈寧門");
        set("long", @LONG
這是皇宮中太後起居宮院慈寧宮的院門. 門內是個小院, 院裡小花
園裡有個荷花塘, 後面連著慈寧宮. 
LONG
        );
        set("outdoors", "huanggong");
        set("exits", ([
                "east"     : __DIR__"longzongmen",
                "west"     : __DIR__"dao8",
                "north"    : __DIR__"cininggong",
                "south"    : __DIR__"bukufang",
        ]));
        set("objects", ([
                __DIR__"npc/dongjinkui" :1,
        ]));
	set("coor/x", -2830);
	set("coor/y", 7731);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}