// Room: /d/village/alley2.c

inherit ROOM;

void create()
{
        set("short", "小巷盡頭");
        set("long", @LONG
這裏是小巷的盡頭，一隻破木箱上擺着幾樣粗製的賭具，地上亂
扔着些雞骨頭，空氣中有一股雞香、酒香和汗臭混雜在一起的味道。
看來這裏是村內地痞、流氓聚集的地方。
LONG );
        set("exits", ([ /* sizeof() == 1 */
            "southeast" : __DIR__"alley1",
        ]));

        set("outdoors", "village");
        set("objects", ([
            __DIR__"npc/punk": 1,
            __DIR__"npc/dipi": 1,
        ]) );

        setup();
        replace_program(ROOM);
}
