inherit ROOM;

void create()
{
        set("short", "小山坡");
        set("long", @LONG
這裡是一處小山，到處長滿了過人高的長草，東面是一處亂墳崗，
聽說經常鬧鬼，所以沒人敢去。一陣冷風刮來，嚇的你根根體毛豎起！
LONG );
        set("exits", ([
                "southdown" : __DIR__"houmen",
                "eastdown" :__DIR__"luan",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7120);
	set("coor/y", -2010);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}