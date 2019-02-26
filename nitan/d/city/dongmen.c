// Room: /city/dongmen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "東門");
        set("long", @LONG
這是東城門，城門正上方刻着『東門』兩個楷書大字，城牆上貼
着幾張官府告示(gaoshi)。官兵們警惕地注視着過往行人，你最好小
心為妙。一條筆直的青石板大道向東西兩邊延伸。東邊是郊外，隱約
可見一片一望無際的樹林，神祕莫測。西邊是城裏。北面有一片茂盛
的青竹林。
LONG );
        set("outdoors", "city");
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));
	set("exits", ([
		"east" : "/d/taishan/yidao",
		"north" : "/d/city/ml1",
		"south" : "/d/city/jiaowai1",
		"west" : "/d/city/dongdajie3",
	]));
	set("objects", ([
		"/d/city/npc/wujiang" : 1,
		"/d/city/npc/bing" : 2,
                "/d/city/npc/jpl2": 1,
	]));

	set("coor/x", 40);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n揚州知府\n程藥發\n";
}