// Room: /d/suzhou/dongmen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "相門");
        set("long", @LONG
這是號稱天堂的蘇州東城門，城門正上方刻着“相門”兩個楷書大
字，城牆上貼着幾張官府告示(gaoshi)。守門官兵們警惕地注視着過往
行人，你最好小心為妙。一條筆直的青石板大道向東西兩邊延伸，西邊
是城裏。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west" : __DIR__"dongdajie2",
                "east" : "/d/jiaxing/jnroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 1140);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n蘇州知府\n馮旭東\n";
}