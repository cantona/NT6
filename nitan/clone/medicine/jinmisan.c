// 金蜜散(jinmi san)

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIW "金蜜散" NOR, ({"jinmi san", "jinmi", "san"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一包金蜜散，據説可以解玉蜂針毒。\n");                
                set("base_unit", "包");
                set("base_value", 8000);
                set("base_weight", 80);
                set("only_do_effect", 1); 
                set("mixture", ([
                        "herb" : ([ "shanju"   : 1,
                                    "muxiang"  : 1,
                                    "chantui"  : 1,
                                    "niuhuang" : 1 ]),
                        "neili" : 300,
                        "jing"  : 50,
                        "time"  : 5,
                        "min_level" : 60,
                        "yunv-xinjing" : 60,
                ]));                
        }

    setup();
}

int do_effect(object me)
{
        if (! me->query_condition("yufengdu"))
        {
                tell_object(me,"你並沒有中蜂毒啊！\n");
                return 1;
        }

        me->clear_condition("yufengdu");
        message_vision(HIY "$N服下了一包金蜜散。苦中帶甜，甜中帶苦，一股香氣沁人心脾。\n"NOR,me);
        tell_object(me,HIY "你感覺體內的蜂毒已慢慢消去。\n" NOR, me);

        destruct(this_object());
        return 1;
}
