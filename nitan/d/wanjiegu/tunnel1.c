// Room: /t/wanjiegu/tunnel1.c

inherit ROOM;

void create()
{
        set("short", "地道");
        set("long", @LONG
地道里光線黑暗，空氣渾濁，一股黴味撲鼻而來。地道里石台階
異常粗糙，兩邊土牆上不時滲出水滴掉到地上。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "north" : __DIR__"tunnel2",
            "out" : __DIR__"tree_hole",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}