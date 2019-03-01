// Room: /d/luoyang/road9.c
// Last modified by winder 2002.11.11

inherit ROOM;

void create()
{
        set("short", "大官道");
        set("long", @LONG
這是一條寬闊筆直的官道，足可容得下十馬並馳。路上塵土飛揚，
將道邊的綠樹染上一層黃灰。大道往東通向脂粉之都的揚州，而西面則
是通往洛陽城。
LONG);
        set("exits", ([  /*  sizeof()  ==  2  */
                "west"      : __DIR__"road10",
                "southeast" : __DIR__"road8",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6870);
	set("coor/y", 2140);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}