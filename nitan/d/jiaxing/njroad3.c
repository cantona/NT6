// Room: /d/jiaxing/njroad3.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一條村中的小路。路邊是一家民房，好像很久沒有人住的樣子。南
邊有條小路通向江邊。
LONG
        );
        set("outdoors","jiaxing");
        set("exits", ([
                "west" : __DIR__"njroad2",
                "east" : __DIR__"njeast",
                "north": __DIR__"yangjia",
                "south": __DIR__"njroad4",
        ]) );

        set("no_clean_up", 0);
	set("coor/x", 1270);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}