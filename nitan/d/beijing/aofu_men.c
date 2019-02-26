inherit ROOM;
#include <ansi.h>

void create()
{
        set("short","鰲府大門");
        set("long", @LONG
一座富麗堂皇的大宅院出現在你的眼前，兩頭高大的石獅子鎮住
了大門兩側。門額上懸掛一方橫匾，寫着‘滿洲第一勇士鰲狠府’幾
個大字，門外有官兵把守，戒備森嚴。門上掛着兩個燈籠，赫然寫着
『鰲』字。這裏就是當朝第一大臣，被御封為『滿洲第一勇士』的鰲
狠的府邸。
LONG );
        set("exits", ([
                "north" : "/d/beijing/aofu_zoulang1",
                "south" : "/d/beijing/di_4",
        ]));
        set("objects", ([
                 "/d/beijing/npc/shi_a" : 2,
        ]));
	set("coor/x", -2820);
	set("coor/y", 7740);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (objectp(present("shi wei", environment(me))) && dir == "north")
                return notify_fail("鰲府侍衞一把攔住你，朗聲喝道：王府要地，怎由閒雜人等隨便進出。\n\n");
        return ::valid_leave(me, dir);
}