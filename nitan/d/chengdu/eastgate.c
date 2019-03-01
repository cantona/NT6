// Room: eastgate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "東門");
        set("long", @LONG
這是成都東城門，城門正上方刻着『東門』兩個楷書大字，城牆
上貼着幾張官府告示(gaoshi)。一條筆直的青石板大道向東西兩邊延
伸。東邊是郊外，一片平平展展的平原風光，真是不愧天府之國的美
稱。西邊是城裏。
LONG );
        set("outdoors", "chengdu");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "east"  : __DIR__"fuheqiaoe",
                "west"  : __DIR__"eastroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15190);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n成都提督\n吳天德\n";
}