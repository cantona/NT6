#include "herb.h"

void create()
{
        set_name(HIR "熊膽" NOR, ({ "xiong dan", "xiong", "dan", "herb_xiongdan" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR "這是一副新鮮的熊膽，頗具藥力。\n" NOR);
                set("base_unit", "副");
                set("base_value", 15000);
                set("base_weight", 200);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        message_vision(HIG "$N" HIG "一仰脖，將" + name() +
                       HIG "整個吞下，咂了咂嘴。\n" NOR, me);

        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}