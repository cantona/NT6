// Room: /city/nanmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "南門");
        set("long", @LONG
這是南城門，城牆被當成了廣告牌，貼滿了花花綠綠各行各業的
廣告，官府的告示(gaoshi)因此不太顯目。官兵們被近處的歡聲笑語
所吸引，似乎不是很認真在執勤。南邊就是渡江橋了。
LONG );
        set("outdoors", "city");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
           "south" : "/d/city/dujiangqiao",
		"north" : "/d/city/nandajie2",
		"west"  : "/d/city/jiaowai8",
		"east"  : "/d/city/jiaowai7",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
                "/d/city/npc/shisong" : 1,
        ]));
	set("coor/x", 0);
	set("coor/y", -30);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n揚州知府\n程藥發\n";
}