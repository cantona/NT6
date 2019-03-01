// didao4.c

inherit ROOM;

void create()
{
        set("short", "甬道");
        set("long", @LONG
你一到這裡，迎面就聞到一股腐爛的泥土的味道，不過從前面的
亮光中，你又看到了希望，你不禁開始加快腳步，想看看那裡到底有
些什麼東西。 
LONG );
        set("exits", ([ /* sizeof() == 2 */
                "north" : __DIR__"didao5",
                "up" : __DIR__"didao3",
        ]));

        setup();
        replace_program(ROOM);
}
