inherit ROOM;

void create()
{
        set("short", "東城根");
        set("long", @LONG
這裡是洛陽內城東牆腳。很是冷清，幾乎沒有人會來這裡，你的面前
除了高大的城牆，滿地的塵土和雜草就什麼也沒有了。但是，突然你看見
兩個穿著黑馬褂的中年人正在牆腳處交頭接耳，竊竊私語，他們到底在幹
什麼？
LONG);
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
        set("exits", ([
                  "southwest" : __DIR__"nantou",
                  "north" : __DIR__"suishi3",
        ]));
        set("objects", ([
                "/d/beijing/npc/dipi" : 1,
        ]));
	set("coor/x", -6940);
	set("coor/y", 2110);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}