inherit ROOM;

void create()
{
        set("short", "亂墳崗");
        set("long", @LONG
這裏是一處亂墳崗，到處長滿了過人高的長草，聽説經常鬧鬼，
所以沒人敢來。一陣冷風颳來，嚇的你根根體毛豎起。
LONG );

        set("exits", ([
                "westup" : __DIR__"xiaoshan",
                "east" : __DIR__"luan2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "jingzhou");

        set("coor/x", -7110);
	set("coor/y", -2010);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}