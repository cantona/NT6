inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","鰲府後院");
        set("long", @LONG
這裏是鰲府的後院，中心是一個大花園。西邊一條長廊走道直通
往鰲狠的書房。北邊是鰲狠私設的牢房，牢門由幾個鰲府的侍衞把守
着。
LONG );
        set("exits", ([
                "north" :  "/d/beijing/aofu_naofang",
                "west" :  "/d/beijing/aofu_zoulang3",
                "south" :  "/d/beijing/aofu_zoulang2",
        ]));
        set("objects", ([
                "/d/beijing/npc/shi_a" : 2,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7790);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "north")
                return notify_fail("鰲府侍衞攔住你道：沒有王爺的吩咐，誰也不能進去。\n\n");
        return ::valid_leave(me, dir);
}