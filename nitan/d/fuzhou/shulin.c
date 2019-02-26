// Room: /d/fuzhou/shulin.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "樹林");
        set("long", @LONG
你走在福州東門外密林中。林中時時傳來蟲鳥的啼鳴。北邊林深處
似乎有一小廟。東邊一山，其形如鼓。卧在平坦平原上。
LONG );
        set("exits", ([
                "north"  : __DIR__"wuxiang",
                "eastup" : __DIR__"gushan",
                "west"   : __DIR__"dongmen",
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -40);
	set("coor/y", -6180);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}