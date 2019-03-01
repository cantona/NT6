// Room: /d/fuzhou/yamen.c
// Date: may 12. 1998 Java

inherit ROOM;

void create()
{
        set("short", "提督衙門");
        set("long", @LONG
這裡是衙門大門，兩扇朱木大門緊緊關閉著。“肅靜”“回避”的
牌子分放兩頭石獅子的旁邊。前面有一個大鼓，幾名戈什哈站在門前。
LONG );
        set("exits", ([
                "east" : __DIR__"nandajie",
        ]));
        set("objects", ([
                __DIR__"npc/geshiha" : 2,
        ]));
        set("no_fight", "1");
        set("no_beg", "1");
	set("coor/x", -90);
	set("coor/y", -6190);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
        if (!wizardp(me) && objectp(present("geshiha", environment(me))) && dir != "east")
                return notify_fail("戈什哈喝道：“施大人已去校場閱兵，你來何幹？”\n");
        return ::valid_leave(me, dir);
}