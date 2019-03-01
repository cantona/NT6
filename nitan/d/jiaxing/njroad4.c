// Room: /d/jiaxing/njroad4.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一條村中的小路。往南邊看已經可以看到大江了，江水的咆哮聲不
時地敲擊着你的耳鼓。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "north": __DIR__"njroad3",
                "south": __DIR__"njroad5",
        ]) );
        set("objects", ([
                "/d/village/npc/boy" : 1,
        ]) );

	set("coor/x", 1270);
	set("coor/y", -1830);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}