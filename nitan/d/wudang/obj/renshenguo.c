#include <ansi.h>
inherit ITEM;

void init(object ob)
{
        if (find_call_out("destguo") != -1)
                return;

        remove_call_out("destguo");
        call_out("destguo", 10, ob);
}

void destguo(object ob)
{
        ob = this_object();

        message_vision(HIM "\n只見$N" HIM "慢慢滲出水來，一會就腐爛掉了。\n\n"
                       NOR, ob);
        destruct(ob);
}

void create()
{
        set_name(HIM "人蔘果" NOR, ({"renshen guo", "renshen", "guo"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("long", HIM "這是一隻已經成型的人蔘果，真的象極了三"
                            "周不滿的小孩。\n" NOR);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        addn("max_neili", 10, me);

        if( query("max_neili", me)>me->query_neili_limit() )
                set("max_neili", me->query_neili_limit(), me);

        set("neili",query("max_neili",  me), me);
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("eff_qi",  me), me);

        message_vision(HIM "\n$N" HIM "吃下一枚人蔘果，只覺得精神健旺，內"
                       "力充沛，真氣源源而\n生，甚至不再感到飢餓乾渴。\n\n", me);

        destruct(this_object());
        return 1;
}