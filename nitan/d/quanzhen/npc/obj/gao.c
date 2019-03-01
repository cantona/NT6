#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + HIC "龜苓膏" NOR, ({ "guiling gao", "guiling", "gao" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", HIC "這是一塊用烏龜甲和茯苓配置成的龜苓"
                            "膏，功能延年益壽。\n" NOR);
                set("value", 3000);
                set("only_do_effect", 1);
        }
        setup();
}

int do_effect(object me)
{
        int na, un;
        mapping my = me->query_entire_dbase();

        na = this_object()->name();
        un=query("unit", this_object());

        if ((int)me->query_condition("pill_drug") > 0)
        {
                write("你覺得現在內息未定，經脈隱隱還能感到真氣沖盪，不"
                      "敢貿然服食。\n");
                return 1;
        }

        me->apply_condition("pill_drug", 2000);

        message_vision(HIC "$N" HIC "服下一" + un + na + HIC "，急忙開始運功吸"
                       "收藥力。\n" NOR, me);

        if( query("max_jingli", me)<1000 )
        {
                tell_object(me, HIC "你只覺得精神健旺之極，精力直欲奔騰而出。\n" NOR);
                me->improve_jingli(5 + random(5));
        } else
                tell_object(me, HIC "你只覺精神飽滿之極，全身的疲憊一掃而空。\n" NOR);

        if( query("jingli", me)<query("max_jingli", me) )
                my["jingli"]  = my["max_jingli"];

        me->start_busy(random(5) + 5);
        destruct(this_object());
        return 1;
}