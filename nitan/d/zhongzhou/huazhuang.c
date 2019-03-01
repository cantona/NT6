inherit ROOM;

void create()
{
        set("short", "化妝間");
        set("long", @LONG
這是演員的化妝間，幾個演員正對著鏡子化妝，也沒注意
你進來。牆邊一溜掛著很多衣服。邊上的櫃子上放了好幾個面
具，那個面具看上去很精巧，帶在臉上足可以以假亂真。
LONG);

        set("exits", ([
                "east" : __DIR__"xiyuan1",

        ]));
        set("objects", ([
                __DIR__"npc/xizi1" : 2,
                __DIR__"npc/xizi3" : 1,
        ]));

        set("coor/x", -9070);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}