// Room: /d/guanwai/chufang.c

inherit ROOM;

void create()
{
        set("short", "廚房");
        set("long", @LONG
炊煙繚繞，蒸汽騰騰，香味撲鼻而來。靠牆有一個灶台，支着一
口大鍋，裏面煮着香噴噴的米粥，旁邊的一個火上蒸着白麪饅頭。一
個老僕人聚精會神的整理着廚房裏面物什。
LONG );
        set("exits", ([
                "east" : __DIR__"shizilu",
        ]));

        set("objects",([
                __DIR__"obj/wan" : 2,
                __DIR__"obj/mantou" : 5,
        ]));

        set("resource/water", 1);
        setup();
        replace_program(ROOM);
}