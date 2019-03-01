// Room: /d/quanzhou/taocipu.c
// Last Modified by winder on May. 29 2001

inherit ROOM;

void create()
{
        set("short", "陶瓷舖");
        set("long", @LONG
這裡燒制各式各樣的陶瓷制品。櫃台上擺著花色各異的碗碟瓶罐，
白皙透明，巧奪天工。動物瓷器，細膩圓潤，栩栩如生。由于它的特殊
地位，因此生意和技術從來都是傳子不傳女。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                "north"   : __DIR__"xinmenji",
        ]));
	set("coor/x", -910);
	set("coor/y", -7730);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}