#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + CYN "\n\n                畜        生        道" NOR);
        set("long", CYN "\n"
"飛禽走獸，弱肉強食。因學習邪見、邪法而生慢心的眾生，喜\n"
"歡以邪見與人爭論，因為懷着怨憎心，就會投生喜歡互相殘害\n"
"的畜生道。性情怯弱，常懷驚恐的動物，也是因過去生驚嚇他\n"
"人在先，而得出這樣的果報。\n\n" NOR);

        set("objects", ([
                __DIR__"npc/chushengdaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
