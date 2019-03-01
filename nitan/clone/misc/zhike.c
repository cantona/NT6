// zhike.c 止咳藥

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIY"止咳藥"NOR, ({"zhike yao", "zhikeyao"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包常見的止咳藥。\n");
                set("value", 100);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (! me->query_condition("ill_kesou"))
        {
                write("你現在又沒有咳嗽，別亂吃藥。\n");
                return 1;
        } else {
                me->clear_condition("ill_kesou");
                message_vision("$N吃下一包止咳藥，咳嗽輕多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}