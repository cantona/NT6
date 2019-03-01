#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", HIG "\n\n                修        羅        道" NOR);
        set("long", HIG "\n"
"阿修羅原是印度遠古諸神之一，被視為惡神，屬于兇猛好鬥的\n"
"鬼神，經常與帝釋天爭鬥不休。因有福報而沒有德性有的說法\n"
"只是將他納入鬼神中，或說是墮落的天人，而北傳佛教將他列\n"
"為善道，南傳佛教則歸類入惡道中。福如天人，德非天人。\n\n" NOR);

        set("objects", ([
                __DIR__"npc/xiuluodaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
