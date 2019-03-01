// Room: /t/wanjiegu/tunnel2.c

inherit ROOM;

void create()
{
        set("short", "地道");
        set("long", @LONG
地道裡光線黑暗，空氣渾濁，一股霉味撲鼻而來。地道裡石台階
異常粗糙，兩邊土牆上不時滲出水滴掉到地上。
LONG );
        set("exits", ([ /* sizeof() == 2 */
            "south" : __DIR__"tunnel1",
            "out" : __DIR__"grassland",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}