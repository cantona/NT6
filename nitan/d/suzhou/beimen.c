// Room: /d/suzhou/beimen.c
// Date: May 31, 98  Java

inherit ROOM;

string look_gaoshi();
void create()
{
        set("short", "齊門");
        set("long", @LONG
這是蘇州府的北城門。出門遠遠可見西面的虎丘山。放眼望去盡是
綠的田，翠的草和清清的小河。門邊官兵身後貼著一份告示(gaoshi)。
南北一條筆直的官道。
LONG );
        set("outdoors", "suzhou");
//        set("no_clean_up", 0);
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north" : __DIR__"road1",
                "south" : __DIR__"beidajie2",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", 1110);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return FINGER_D->get_killer() + "\n蘇州知府\n馮旭東\n";
}