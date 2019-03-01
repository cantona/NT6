// Room: /d/wuxi/yamen.c
// Winder 2000/02/22 

inherit ROOM;

void create()
{
        set("short", "衙門大門");
        set("long", @LONG
這裡是衙門大門，兩扇朱木大門緊緊關閉著。“肅靜”“回避”的
牌子分放兩頭石獅子的旁邊。前面有一個紅漆大鼓，顯然是供小民鳴冤
用的。幾名衙役站在門前，不怒自威。
LONG );
        set("exits", ([
                "south" : __DIR__"eastroad1",
                "north" : __DIR__"ymzhengting",
        ]));
        set("objects", ([
                "/d/city/npc/yayi" : 4,
        ]));
        set("coor/x", 1050);
	set("coor/y", -720);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if( !wizardp(me) && !query("officerlvl", me) && objectp(present("yayi",environment(me))) && dir == "north" )
                return notify_fail("衙役喝道：“威……武……。”\n");
        return ::valid_leave(me, dir);
}