#include <ansi.h>
inherit __DIR__"gift";

void create()
{
        set_name(NOR + HIC "福壽膏" NOR, ({ "fushou gao", "fushou", "gao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIC "這是一塊製作精緻的糕點，據説吃了可以增強身法。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 10000);
                set("base_weight", 50);
                set("only_do_effect", 1);
                set("gift_type", "dex");
                set("gift_name", "先天身法");
                set("gift_point", 40);
                set("gift_msg", HIW "突然你只覺全身輕飄飄的，有股騰雲駕霧的感覺。\n" NOR);
        }
        setup();
}
