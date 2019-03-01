// Room: /d/huanggong/kunningmen.c
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "坤寧門");
        set("long", @LONG
這是皇宮後廷的後門. 門外是御花園. 門內南連坤寧宮, 由此進入
所謂的三宮六院.
LONG
        );
        set("outdoors", "huanggong");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"kunninggong",
                "north"     : __DIR__"yuhuayuan",
        ]));
        set("objects", ([
                __DIR__"npc/ruidong" : 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7711);
	set("coor/z", 0);
	setup();
}
int valid_leave(object me, string dir)
{
        if (dir == "south" &&
        objectp(present("rui dong", environment(me))))
                return notify_fail("瑞棟攔住你說：此處禁地，請止步。\n");

        return ::valid_leave(me, dir);
}