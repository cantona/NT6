// /guanwai/huandi2.c

inherit ROOM;

void create()
{
        set("short", "荒路");
        set("long", @LONG
這是城東的一條荒路，路旁雜亂的長着齊膝的荒草，遠近荒無一人。兩
旁乾枯的老樹上落滿了成羣的烏鴉，淒涼的鳴叫聲在荒野上遠遠傳去，一派
淒涼的景象。
LONG );
        set("exits", ([
                "southwest" : __DIR__"huandi1",
                "enter"     : __DIR__"shanshenmiao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "guanwai");
        set("coor/x", 4020);
	set("coor/y", 9260);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}
