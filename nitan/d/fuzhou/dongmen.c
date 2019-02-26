// Room: /d/fuzhou/dongmen.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "東門");
        set("long", @LONG
東門外是福州平原。從這裏看去，可以見到密密的叢林。出東門十
裏地就是鼓山了。
LONG );
        set("exits", ([
                "east" : __DIR__"shulin",
                "west" : __DIR__"dongxiaojie",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -50);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}