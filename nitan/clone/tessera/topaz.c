
#include <ansi.h>

inherit TESSERA;

void create()
{
        set_name(HIY "黃寶石" NOR, ({ "topaz" }));
        set_weight(20);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", WHT "這是一顆寶石，上面似乎附着某種神奇的魔力。\n" NOR);
                set("value", 100000);
                set("unit", "顆");
                set("level", 2); 
                set("material", "topaz"); 
                set("no_identify", 1);
        }
        setup();
}

