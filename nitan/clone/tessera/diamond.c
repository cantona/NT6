
#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIW "水晶鑽" NOR, ({ "diamond" }));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一顆寶石，上面似乎附着某種神奇的魔力。\n" NOR);
                set("value", 100000);
                set("unit", "顆");
                set("level", 2); 
                set("material", "diamond"); 
                set("no_identify", 1);
        }
        setup();
}

