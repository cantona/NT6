// /d/beijing/andingmen.c
// Last Modified by winder on Jan. 18 2002

inherit ROOM;
string look_gaoshi();

void create()
{
        set("short", "安定門");
        set("long", @LONG
這裡是永定門，城門正上方刻著“安定門”三個大字，城牆上貼著
幾張官府告示 (gaoshi)。幾個官兵守在兩旁。
LONG );
        set("outdoors", "beijing");
        set("item_desc", ([
                "gaoshi" : (: look_gaoshi :),
        ]));
        set("exits", ([
                "north" : "/d/changcheng/nroad1",
                "south" : __DIR__"di_anmen",
        ]));
        set("objects", ([
                "/d/city/npc/wujiang" : 1,
                "/d/city/npc/bing" : 2,
        ]));
	set("coor/x", -2800);
	set("coor/y", 7760);
	set("coor/z", 0);
	setup();
}

string look_gaoshi()
{
        return "輯拿天地會一眾反賊! \n舉報一人，賞金十兩;\n捉拿一人，賞金百兩。\n知情不報者，立斬!\n鰲拜發\n";
}