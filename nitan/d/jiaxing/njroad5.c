// Room: /d/jiaxing/njroad5.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一條村中的小路。南邊就是錢塘江了，那邊的樹下聚集著一些閒散
的村民。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "north": __DIR__"njroad4",
                "south": __DIR__"jiangpan1",
        ]) );

	set("coor/x", 1270);
	set("coor/y", -1840);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}