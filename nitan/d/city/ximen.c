// Room: /city/ximen.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
	set("short", "西門");
        set("long", @LONG
這是西城門，幾年前曾經遭到土匪的攻打，因此顯得有些破敗。
城門正上方勉勉強強可以認出『西門』兩個大字，城牆上貼着幾張通
緝告示(gaoshi)。    這裏是罪犯逃往西域的必經之地，官兵們戒備
森嚴，動不動就截住行人盤問。一條筆直的青石板大道向東西兩邊延
伸。西邊是郊外，騎馬的、坐轎的、走路的，行人匆匆。東邊是城裏。
LONG );
        set("outdoors", "city");
//	set("no_clean_up", 0);
	set("item_desc", ([
		"gaoshi" : (: look_gaoshi :),
	]));

	set("exits", ([
		"east"  : "/d/city/xidajie3",
		"west"  : "/d/city/ximenroad",
                "south" : "/d/city/xiaofang",
	]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
                "/d/mingjiao/npc/fenggongying" : 1,
        ]));
	set("coor/x", -40);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
	return FINGER_D->get_killer() + "\n揚州知府\n程藥發\n";
}