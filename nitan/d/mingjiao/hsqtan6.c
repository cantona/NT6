//HSQTAN6.C

inherit ROOM;

void create()
{
        set("short", "深潭");
        set("long", @LONG
這裡的水只有齊腰深，但站在水中，仍感覺寒意從腳下漫起，經
久不散。
LONG );
        set("exits", ([
                "up"   : __DIR__"hsqmen",
                "west" : __DIR__"hsqtan5",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
