// Room: westgate.c
// Date: Feb.14 1998 by Java

inherit ROOM;
string look_gaoshi();
void create()
{
        set("short", "西門");
        set("long", @LONG
你來到了西城門外，只見高大的城牆厚實凝重，衞兵仔細地盤查
着過往行人，一切都顯得井井有條。城牆上貼着幾張告示(gaoshi)。
西面遠遠可以看到城外的清溪碧水。東邊是城裏。
LONG );
        set("outdoors", "chengdu");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "west"  : __DIR__"nanheqiaow",
                "east"  : __DIR__"westroad2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing"    : 2,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -15250);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n成都提督\n吳天德\n";
}