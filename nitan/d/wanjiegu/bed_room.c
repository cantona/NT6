// Room: /t/wanjiegu/bed_room.c

inherit ROOM;

void create()
{
        set("short", "臥室");
        set("long", @LONG
這是鐘谷主的臥室，室內大紅的幃帳掛在大紅的木床之上。牆上
貼滿了各種花花綠綠的東西。床邊有個小櫃，櫃上放著一盞豆油燈。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "south" : __DIR__"left_room",
        ]));
        set("objects", ([
            __DIR__"npc/zhongling" : 1,
        ]));
//        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}