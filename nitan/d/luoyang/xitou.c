inherit ROOM;

void create()
{
        set("short", "西城根");
        set("long", @LONG
這裏是洛陽內城南牆腳。很是冷清，幾乎沒有人會來這裏，你的面前
除了高大的城牆，滿地的塵土和雜草就什麼也沒有了。但是，忽然你眼睛
一花，有兩個黑影從你的面前一閃而過，到底是發生了什麼事情呢？
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "southeast" : __DIR__"nantou2",
                  "north" : __DIR__"suishi10",
        ]));
        set("objects", ([
                "/d/city/npc/liumang" : 1,
                "/d/beijing/npc/hunhun" : 1,
        ]));
	set("coor/x", -7040);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}