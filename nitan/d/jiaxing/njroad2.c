// Room: /d/jiaxing/njroad2.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一條村中的小路。路邊是一家民房，不過好象已經很久很久沒有人
住了。
LONG
        );
        set("outdoors","jiaxing");

        set("exits", ([
                "west" : __DIR__"njroad1",
                "east" : __DIR__"njroad3",
                "north": __DIR__"guojia",
        ]) );
        set("objects", ([
                "/d/village/npc/girl" : 1,
        ]) );

	set("coor/x", 1260);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}