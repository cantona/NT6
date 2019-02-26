inherit ROOM;

void create()
{
        set("short", "南廳");
        set("long", @LONG
這是一間大大的房間，放着整排藥櫃，一股濃濃的藥味讓你
幾欲窒息，那是從藥櫃上的幾百個小抽屜裏散發出來的。
LONG );

        set("no_fight", 1);
        set("exits", ([
                "north" : __DIR__"tingyuan",
                "west" : __DIR__"neiwu",
        ]));
        set("objects", ([
                __DIR__"npc/huoji1" : 1,
        ]));
        setup();
        replace_program(ROOM);
}
