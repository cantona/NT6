// tianxiang.c 天香玉露

#include <ansi.h>

inherit ITEM;

void setup()
{
}

void create()
{
        set_name(HIG "天香玉露" NOR, ({"magic water", "yvlu", "lu"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "滴");
                set("long", HIG "這是附著在靈芝上的一滴晶瑩剔透的玉露，傳說採自\n"
                                "靈山，千年來以靈芝為母，不斷的吸取著日精月華，\n"
                                "具有著無比神奇的功效。\n");
                set("value", 1000000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        string force;
        int neili_limit;

        neili_limit = me->query_neili_limit();
        message_vision(HIG "$N" HIG "小心翼翼的將玉露含在嘴中，登時覺得"
                       "靈台一陣空明，渾身上\n下飄飄欲仙，一時間竟有不在"
                       "塵世的感覺。\n" NOR,
                       me);

        if( query("max_neili", me)<neili_limit )
        {
                addn("max_neili", 120+random(150), me);
                if( query("max_neili", me)>neili_limit )
                        set("max_neili", neili_limit, me);
                set("neili",query("max_neili",  me), me);

        }

        if( query("gift/tianxiang", me) <= 200 )
        {
        force = me->query_skill_mapped("force");
        if (me->can_improve_skill("force"))
                me->improve_skill("force", 40000);
        if (stringp(force) && me->can_improve_skill(force))
                me->improve_skill(force, 40000);
        }

        addn("gift/tianxiang", 1, me);
        me->start_busy(random(5) + 5);
        destruct(this_object());
        return 1;
}