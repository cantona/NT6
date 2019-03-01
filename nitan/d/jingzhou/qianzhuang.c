inherit ROOM;
void create()
{
        set("short", "錢莊");
        set("long", @LONG
這是一家老字號的錢莊，已有幾百年的歷史，在全國各地都有分
店。它發行的銀票信譽非常好，通行全國。
LONG );
        set("no_fight", 1);
        set("exits", ([
                "east" : __DIR__"beidajie1",
        ]));
        set("objects", ([
                __DIR__"npc/qian" : 1
        ]));

        set("coor/x", -7110);
	set("coor/y", -2040);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}