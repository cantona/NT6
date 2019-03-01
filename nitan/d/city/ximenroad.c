// Room: /city/ximenroad.c
// YZC 1995/12/04 

inherit ROOM;

string look_gaoshi();

void create()
{
    	set("short", "西門大道");
        set("long", @LONG
這裡是揚州西城門外大道。西通洛陽城，向東就是西門了。南邊，
新開了個武道大會場，每到比武之期，人聲鼎沸，你不禁想去見識一
下當今的成名人物。北邊就是大名鼎鼎的俠義盟揚州分部了。
LONG );
        set("outdoors", "city");
	set("exits", ([
		"east"  : "/d/city/ximen",
                "west"  : "/d/luoyang/road8",
		"south" : "/d/city/wudao4",
                "north" : "/d/city/xym_yzdamen",
	]));
        set("objects", ([
            "/d/village/npc/boy" : 3,
        ]));
	set("coor/x", -50);
	set("coor/y", 0);
	set("coor/z", 0);
	setup();
}

int valid_leave(object me, string dir)
{
	object obj;
	if( dir == "south")set_temp("view_leitai", 1, me);
        return ::valid_leave(me, dir);
}