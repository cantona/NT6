inherit ROOM;

void create()
{
        set("short", "南城根");
        set("long", @LONG
這裏是洛陽內城南牆腳。很是冷清，幾乎沒有人會來這裏，你的面前
除了高大的城牆，滿地的塵土和雜草就什麼也沒有了。
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"suishi4",
                  "northeast" : __DIR__"dongtou",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));
	set("coor/x", -6950);
	set("coor/y", 2100);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}