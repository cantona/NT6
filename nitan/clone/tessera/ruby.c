
#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIR "紅寶石" NOR, ({ "ruby" }));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一顆寶石，上面似乎附着某種神奇的魔力。\n" NOR);
                set("value", 100000);
                set("unit", "顆");
                set("level", 2); 
                set("material", "ruby"); 
                set("no_identify", 1);
        }
        setup();
}

