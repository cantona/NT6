// fashao.c 退燒靈

inherit ITEM;

#include <ansi.h>

void create()
{
        set_name(HIY"退燒靈"NOR, ({"tuishao ling", "tuishao ling"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "包");
                set("long", "這是一包治發燒的藥，療效顯著。\n");
                set("value", 200);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        if (! me->query_condition("ill_fashao"))
        {
                write("你現在又沒有發燒，別亂吃藥。\n");
                return 1;
        } else {
                me->clear_condition("ill_fashao");
                message_vision("$N吃下一包退燒靈，看起來精神多了。\n", me);
                me->start_busy(2);
                destruct(this_object());
                return 1;
        }
}