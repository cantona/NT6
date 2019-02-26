// Code of ShenZhou
//wzfeng 99 11/29
#include <ansi.h>
inherit ITEM;

void setup()
{}
void init()
{
        add_action("do_eat", "eat");
}
void create()
{
        set_name(HIW"補陰丸"NOR, ({"buyin wan","wan"}));
        set_weight(5);
        if (clonep())
                set_default_object(__FILE__);
        else 
        {
                set("unit", "粒");
                set("long","這是一粒補陰丸，滋補陰柔之氣有奇效，不過常人服食恐有異常 。\n");
                set("value", 0);
                set("no_sell", 1);
                set("no_drop","這樣東西不能離開你。\n");
                set("value", 2000);
                set("medicine", 1);

        }
        setup();
}
 
int do_eat(string arg)
{

        object me;
        int skill;
        me=this_player();
        skill=me->query_skill("pixie-jian", 1);

        if (!id(arg))
        return notify_fail("你要吃什麼？\n");
        if(skill<200)
        {
        message_vision(HIR"$N吃下一粒補陰丸，只覺得渾身一陣冰涼，一股陰寒之氣之丹田串向全身，剎那間心神失首，經脈受損!\n"NOR, this_player());
        if( query("max_jingli", me)>50 )
        {
        addn("eff_jingli", -20, me);
        addn("max_jingli", -20, me);
        }
        me->unconcious();
        }
        else
        {
                if( query("drug_list/1", me) == query("drug_list/1" )
                         && query("drug_list/2", me) == query("drug_list/2" )
                         && query("drug_list/3", me) == query("drug_list/3" )
                         && query("drug_list/4", me) == query("drug_list/4" )
                         && query("drug_list/5", me) == query("drug_list/5" )
                        )
                
                
                {

                        if( query("pixie/buyin-wan/lvl", me) >= skill && query("pixie/buyin-wan/lvl", me)>0 )

                        {
                                message_vision(HIG"$N吃下一粒補陰丸，只覺得渾身一陣冰涼，一股陰寒之氣之丹田串向全身，剎那間陽氣鋭減，陰氣陡增。\n"NOR, this_player());
                                message_vision(HIR"不料以前的藥力似乎並未消失，連續服用效果適的其反。$N剎那間心神失首，經脈受損。\n"NOR, this_player());
        if( query("max_jingli", me)>50 )
        {
        addn("eff_jingli", -20, me);
        addn("max_jingli", -20, me);
        }

                        }
                        else
                        {
                        
                                message_vision(HIG"$N吃下一粒補陰丸，只覺得渾身一陣冰涼，一股陰寒之氣之丹田串向全身，剎那間陽氣鋭減，陰氣陡增。\n"NOR, this_player());
                                addn("eff_jingli", 5+random(2), me);
                                addn("max_jingli", 5+random(2), me);
                                set("pixie/buyin-wan/lvl", skill, me);
                        }
                
                }
                else
                {
                message_vision(HIG"$N吃下一粒補陰丸，只覺得渾身一陣冰涼，一股陰寒之氣之丹田串向全身，剎那間陽氣鋭減，陰氣陡增。\n"NOR, this_player());
                message_vision(HIR"不料此藥劑量與你身體不符，剎那間$N心神失首，經脈受損。\n"NOR, this_player());
                addn("max_jingli", -20, me);
                me->unconcious();
        
                }

        }
        
        
        destruct(this_object());
        return 1;
}
