// Room: /d/suzhou/yamengate.c
// Last Modified by winder on May. 15 2001
inherit ROOM;

void create()
{
        set("short", "衙門大門");
        set("long", @LONG
這裏是衙門大門，兩扇朱木大門緊緊關閉着。“肅靜”“迴避”的
牌子分放兩頭石獅子的旁邊。前面有一個大鼓，顯然是供小民鳴冤用的。
幾名衙役在門前巡邏。
LONG
        );

        set("exits", ([
                "south" : __DIR__"xidajie1",
                "north" : __DIR__"yamen",
        ]));

        set("objects", ([
                __DIR__"npc/yayi" : 2,
        ]));
	set("coor/x", 1100);
	set("coor/y", -1050);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("ya yi", environment(me))) &&
                dir == "north")
                return notify_fail("衙役喝道：“威……武……。”\n");
        return ::valid_leave(me, dir);
}