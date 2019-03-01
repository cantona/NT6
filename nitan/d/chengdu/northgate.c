// Room: northgate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "北門");
        set("long", @LONG
這是成都北城門，城門正上方刻着『北門』兩個楷書大字，城牆
上貼着幾張官府告示(gaoshi)。一條筆直的青石板大道向北延伸。北
邊望去，一片綠油油的田野夾着隨風搖曳的高樹，長竹。城門邊兩行
官兵仔細盤查進出人等。
LONG );
        set("outdoors", "chengdu");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("no_fight",0);
        set("exits", ([
                "south"  : __DIR__"northroad2",
                "north"  : __DIR__"fuheqiaon",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1800);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n成都提督\n吳天德\n";
}