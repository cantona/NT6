// Room: /t/wanjiegu/shan_road3.c

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這是一條山間小路，兩邊山坡上張了許多樹木，北風吹過，發出
沙沙的響聲。路上張著許多雜草，看起來這裡很少有人走動。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "eastup" : __DIR__"shan_road2",
            "northdown" : __DIR__"shan_road4",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}