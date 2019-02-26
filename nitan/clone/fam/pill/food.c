#include <ansi.h>
inherit COMBINED_ITEM;

void create()
{
        set_name(NOR + WHT "乾糧" NOR, ({ "gan liang", "gan", "liang" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + WHT "這是一塊便於攜帶的乾糧。\n" NOR);
                set("base_unit", "塊");
                set("base_value", 50);
                set("base_weight", 10);
                set("only_do_effect", 1);
        }
        setup();
        set_amount(1);
}

int do_effect(object me)
{
        if( query("food", me) >= me->max_food_capacity() )
        {
                write("你已經吃太飽了，再也塞不下任何東西了。\n");
                return 1;
        }

        message_vision("$N摸出一塊" + name() + "啃了幾口。\n" NOR, me);
        addn("food", 3000, me);

        add_amount(-1);

        if (query_amount() < 1)
                destruct(this_object());

        return 1;
}