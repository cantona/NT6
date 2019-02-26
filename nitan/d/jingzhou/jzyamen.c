#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "荊州衙門");
        set("long", @LONG
一座大廈，硃紅的大門，門上釘着碗口大的銅釘，門外兩盞大燈籠，
一盞寫着“荊州府正堂”，另一盞寫着“凌府”。這裏是荊州衙門大門
所在，衙門的兩扇朱木大門緊緊關閉着。『肅靜』『迴避』的牌子分放
兩頭石獅子的旁邊。前面有一個大鼓，顯然是供小民鳴冤用的。幾名衙
役在門前巡邏。
LONG );
        set("region", "jingzhou");
        set("exits", ([
                "south" : __DIR__"ymzhengting",
                "north" : __DIR__"xidajie1",
        ]));
        set("objects", ([
                __DIR__"obj/lion" : 2,
                __DIR__"npc/yayi" : 4,
        ]));

        set("coor/x", -7110);
	set("coor/y", -2060);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (dir == "south" &&
           objectp(present("ya yi", environment(me))))
                return notify_fail(CYN "衙役齊聲喝道：威……武……\n" NOR);
        return ::valid_leave(me, dir);
}