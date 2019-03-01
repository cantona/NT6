// Room: southgate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "南門");
        set("long", @LONG
這是成都南城門，城門正上方刻著『南門』兩個楷書大字，城牆
上貼著幾張官府告示(gaoshi)。一條筆直的青石板大道向南延伸。南
邊是郊外，遍地麥浪金黃迷人。北邊是城裡。
LONG );
        set("outdoors", "chengdu");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("no_fight",0);
        set("exits", ([
                "south"  : __DIR__"nanheqiaos",
                "north"  : __DIR__"southroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15220);
	set("coor/y", -1860);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n成都提督\n吳天德\n";
}