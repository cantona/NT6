#include <ansi.h>

inherit ITEM;
inherit F_FOOD;

void create()
{
        set_name(YEL "花種" NOR, ({"hua zhong", "zhong"}));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "一枚無法確定品種的花種。\n");
                set("unit", "只");
                set("value", 20);
                set("food_remaining", 1);
                set("food_supply", 10);
        }
}

void init()
{
        add_action("do_zhonghua", "zhonghua");
}

int do_zhonghua()
{
        object me,ob;
 
        me = this_player();
        ob = this_object();

        if( query_temp("zhonghua", me) == 1 )
        {
                tell_object(me,HIR "種子已經撥下了，現在該培育(peiyu)花種。\n" NOR);
                return 1;
        }

        message_vision("$N用手在地上挖了一個坑，把花種放了進去。\n", me);
        tell_object(me, HIR "種子已經撥下了，現在該培育(peiyu)花種。\n" NOR);
        addn_temp("zhonghua", 1, me);
        destruct(ob);
        addn("jing", -50, me);
        return 1;
}