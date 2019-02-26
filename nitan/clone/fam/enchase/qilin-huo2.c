inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIR "麒麟火" NOR, ({"qilin huo", "qilin", "huo" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("value", 500000);
                set("long", HIR "據説麒麟火麒麟神獸骸骨所化，拿在手中有種熾熱的感覺。\n" NOR);
                set("enchase/name", "麒麟火");
                set("enchase/point", 5);
                set("enchase/type", "medal2");
                set("enchase/cur_firm", 100);
                set("enchase/spe_data", ([]) );  
        }
        setup();
}

int query_autoload()
{
        return 1;
}

