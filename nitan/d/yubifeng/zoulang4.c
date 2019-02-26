// /yubifeng/zoulang4.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short","走廊");
        set("long",@LONG
這是一條長長的走廊，通向各個客人的寢室。兩側木壁上或刻有花
鳥魚蟲，或掛了些許時人的字畫，每隔七八步，就有一處香台，縷縷青
煙從銅鶴嘴裏游出，聞之精神一振。
LONG);
        set("exits", ([
                "east"  : __DIR__"eastroom1",
                "north" : __DIR__"zoulang6",
                "south" : __DIR__"zoulang2",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6130);
        set("coor/y", 5190);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}
