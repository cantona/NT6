#include <ansi.h>
#include <armor.h>

inherit HEAD;

void create()
{
        set_name(HIR "鳳凰羽毛" NOR, ({ "fenghuang feather", "feather", "fenghuang" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {               
                        set("long", HIR "一根鳳凰身上的羽毛，呈火紅色。\n" NOR);

                set("unit", "根");
                set("value", 10000);
        }
        setup();
}

int query_autoload()
{
        return 1;
}
