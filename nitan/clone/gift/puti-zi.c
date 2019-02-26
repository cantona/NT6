// puti-zi.c 菩提子

#include <ansi.h>
#include "gift.h"

void create()
{
        set_name(HIG "菩提子" NOR, ({"puti zi", "zi"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIG "這是一顆晶瑩如玉的菩提子，採自靈山佛祖座"
                            "前，珍稀無比，\n乃萬年菩提樹之實，功能化百劫"
                            "，渡千災，與天地同壽。\n");
                set("base_value", 50000);
                set("base_weight", 100);
                set("base_unit", "顆");
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int neili_limit;

        neili_limit = me->query_current_neili_limit();
        if ((int)me->query_condition("putizi_drug") > 0)
        {
                write("你覺得現在內息未定，經脈隱隱還能感到真氣衝蕩，不"
                      "敢貿然服食。\n");
                return 1;
        } else
        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 100+random(30), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

                message_vision(HIY "$N" HIY "吃下一顆菩提子，頓然間只覺一股浩"
                               "蕩無比的真氣直衝頂門，連忙運功吸納。\n" NOR,
                               me);
                // me->apply_condition("putizi_drug", 50);
        } else
        {
                message_vision(HIY "$N" HIY "一仰脖，吞下了一顆菩提子。\n" NOR,
                               me);
                tell_object(me, "你覺得沒啥感覺，不如花生好吃。\n");
        }

        // me->start_busy(random(5) + 5);
        add_amount(-1);
        if (query_amount() < 1)
                destruct(this_object());
                
        return 1;
}

