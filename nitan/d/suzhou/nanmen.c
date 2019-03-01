// Room: /d/suzhou/nanmen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "吳門");
        set("long", @LONG
這是蘇州府的南城門。進進出出的吳儂軟語，聽來特讓人舒服。門
口的官兵開口喝罵，也是這種軟綿聲氣。門上貼著一份告示(gaoshi)。
南北一條筆直的官道。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north" : __DIR__"nandajie2",
                "south" : __DIR__"qsgdao2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1090);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n蘇州知府\n馮旭東\n";
}