inherit ROOM;

void create()
{
        set("short", "大雄寶殿");
        set("long", @LONG
經過九級石頭台階，正面就是佛祖神像，兩邊普賢和文殊。高大
的佛像幾乎挨到了屋頂，令人凌然生威。正對著門的地方擺著幾張供
桌，上面是時鮮的瓜果。供桌兩邊的大蠟燭比人還高。兩邊是十八羅
漢。
LONG );
        set("objects", ([
                  __DIR__"npc/obj/rulaixiang" : 1,
        ]));

        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"zhongyuan",
                  "north" : __DIR__"houyuan",
        ]));

	set("coor/x", -5040);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}