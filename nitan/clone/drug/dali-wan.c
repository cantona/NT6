// Code of ShenZhou
#include <ansi.h>;
inherit PILL;

void setup()
{}

int cure_ob(string);

void create()
{
        set_name(HIR"金剛大力丸"NOR, ({"dali wan", "wan"}));
        set_weight(100);
        if (clonep())
        set_default_object(__FILE__);
        else 
        {
                set("unit", "顆");
                set("long","這是江湖上常見的藥丸，紅色，龍眼大小，服後會力氣大增。\n");
                set("value", 5000);
                set("no_sell", 1);
        }
set("wposition", "/clone/drug/dali-wan.c");
        setup();
}

int cure_ob(object me)
{
        int app_str;
        if( query_temp("daliwan", me) )
                return notify_fail("你已服過大力丸了。\n");
        app_str = random(5)+1;
        message_vision(HIR"$N服下一顆金剛大力丸，掄了掄胳膊，直想找人打一架。\n"NOR,me);
        addn_temp("apply/str", app_str, me);
        set_temp("daliwan", 1, me);
    destruct(this_object());
    return 1;
}

//void remove_eff(int app_str, object me)
//{
//        message_vision(HIM"$N胳膊一陣發軟，看來金剛大力丸藥性已去。\n"NOR,me);
//        me->add_temp("apply/str",-app_str);
//        me->delete_temp("daliwan");
//}

