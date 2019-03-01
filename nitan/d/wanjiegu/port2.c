// Room: /t/wanjiegu/port2.c

inherit ROOM;

void create()
{
        set("short", "瀾滄江畔");
        set("long", @LONG
這裡是一個小山坡，西面是上山的路，東面一條鐵索橋橫跨江面，
只見江水奔騰，呼嘯而過，江風吹得鐵索橋晃來晃去。
LONG );
        set("outdoors", "wanjiegu");
        set("exits", ([ /* sizeof() == 2 */
            "westup" : __DIR__"slide3",
            "east" : __DIR__"bridge",
        ]));

        setup();
        replace_program(ROOM);
}