#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", NOR + HIB "\n\n                餓        鬼        道" NOR);
        set("long", HIB "\n"
"哀嚎四起，環顧周圍，遍是咽細如針，口大如炬，腹鼓如山的\n"
"餓鬼。前世造作的善惡業不同，在餓鬼道所受的果報也會不同。\n"
"餓鬼多是汲汲於飲食，但卻四處奔走求食不能，所見池水卻都\n"
"變成膿血而不能飲用，不是遇水成火就是喉細無法咽食。\n\n" NOR);

        set("objects", ([
                __DIR__"npc/eguidaofo" : 1,
        ]));
        set("no_magic", 1);
        setup();
}
