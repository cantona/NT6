// Room: /d/jiaxing/njroad1.c
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "村中小路");
        set("long", @LONG
一條村中的小路。路邊是一家破舊的小酒店，好象已經很久沒人來
過了的樣子。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","jiaxing");

        set("exits", ([
                "west" : __DIR__"njwest",
                "east" : __DIR__"njroad2",
                "south": __DIR__"xiaodian",
        ]) );

	set("coor/x", 1250);
	set("coor/y", -1820);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}