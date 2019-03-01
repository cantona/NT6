// Room: /d/suzhou/ximen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "閶門");
        set("long", @LONG
這是號稱天堂的蘇州西城門，城門正上方刻著“閶門”兩個楷書大
字，城牆上貼著幾張官府告示(gaoshi)。西門外通向寒山寺一條筆直的
青石板大道向東西兩邊延伸，東邊是城裡。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west" : __DIR__"road2",
                "east" : __DIR__"xidajie2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 1080);
	set("coor/y", -1060);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n蘇州知府\n馮旭東\n";
}