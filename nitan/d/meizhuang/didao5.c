// didao5.c

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
你一到這裏，迎面就聞到一股腐爛的泥土的味道，不過從前面的
亮光中，你又看到了希望，你不禁開始加快腳步，想看看那裏到底有
些什麼東西。 
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"didao6",
                "south" : __DIR__"didao4",
                "east"  : __DIR__"didao4",
                "west"  : __DIR__"didao5",
        ]));

        setup();
        replace_program(ROOM);
}