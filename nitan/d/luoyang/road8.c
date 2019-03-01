// Room: /d/luoyang/road8.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。由于常年車馬奔
馳，路面陷下深深的車轍。雨雪天氣，泥濘不堪。晴天日頭，又粉塵飛
揚。大道往東通向脂粉之都的揚州，而西面則是通往洛陽城。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "east"      : "/d/city/ximenroad",
                "northwest" : __DIR__"road9",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6860);
	set("coor/y", 2130);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}