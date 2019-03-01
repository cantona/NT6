// Room: /city/zuixianlou2.c
// YZC 1995/12/04 

inherit ROOM;

void create()
{
	set("short", "醉仙樓二樓");
        set("long", @LONG
這裡是醉仙樓正對著街面的二樓，文人學士在這裡吟詩作畫，富
商土豪在這裡大快朵頤，江湖豪客則自然是貂裘換酒，縱情豪飲了。
東邊的幾間廂房內則有人在舉辦喜宴，大宴賓客。
LONG );
	set("item_desc", ([
		"paizi" : "本店出售烤鴨及上等花雕酒。\n",
	]));
	set("objects", ([
		"/d/city/npc/xian" : 1,
		"/d/city/npc/guidao" : 1,
                /*CLASS_D("gaibang") + "/kongkong" : 1,*/
	]));
	set("exits", ([
		"down" : "/d/city/zuixianlou",
                "up"   : "/d/city/zuixianlou3",
                "east": "/d/city/zxlpath",
	]));
//	set("no_clean_up", 0);
	set("coor/x", 10);
	set("coor/y", 20);
	set("coor/z", 10);
	setup();
	replace_program(ROOM);
}
