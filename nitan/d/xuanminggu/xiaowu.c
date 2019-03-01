// Room: xiuxishi.c 休息室
// By rcwiz

inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這裡是玄冥谷中的一間茅草屋，供平時休息之用。此處雖
然簡陋了點，但也還算景色宜人，比之豪華的臥房更有一分清
新脫俗的感覺。
LONG );
        set("no_clean_up", 0);
        set("sleep_room", 1);
        set("no_fight", 1);

        set("exits", ([
                "out" : __DIR__"xuanminggu",
        ]));
        setup();
        replace_program(ROOM);
}


