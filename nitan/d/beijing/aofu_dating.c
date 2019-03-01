inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","鰲府大廳");
        set("long", @LONG
這裡是鰲狠府的大廳，大廳相當的寬敞明亮，四周的牆上懸掛滿
了各朝名人的真跡，正堂坐著一個滿面虯須，身材魁梧，身著黃馬褂
的中年男子，看來那就是當朝第一大臣，被御封為『滿洲第一勇士』
的鰲狠了。大廳往北是一條走廊，那是通往鰲府的後院所在。
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_zoulang2",
                "south" :  "/d/beijing/aofu_dayuan",
        ]));
        set("objects", ([
                "/d/beijing/npc/aobai" : 1,
                "/d/beijing/npc/yahuan_a" : 1,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7770);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("ao bai", environment(me))) && dir == "north")
                return notify_fail("鰲拜大聲喝道：他奶奶的，你要幹嘛？\n\n");
        return ::valid_leave(me, dir);
}