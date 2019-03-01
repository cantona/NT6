// Room: /t/wanjiegu/slide3.c

inherit ROOM;

void create()
{
        set("short", "山坡");
        set("long", @LONG
山坡之上張著一些不知名的雜草，以及三三兩兩分布其間的灌木
叢，這裡很少有大樹，幾朵野花在路邊悄悄開放，偶爾有幾只蝴蝶飛
來飛去。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "southup" : __DIR__"shan_road1",
            "eastdown" : __DIR__"port2",
        ]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}