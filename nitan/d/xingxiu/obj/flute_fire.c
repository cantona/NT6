// Code of ShenZhou
// Ryu, 12/5/96

inherit ITEM;
#include <ansi.h>;

void init();
void wear(int);

int worn;

void create()
{
        set_name(HIR"一堆火焰"NOR,({"huo yan"}));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIR"火焰高約尺，"+GRN+"色作純碧，"+BLU+"鬼氣森森，"+HIR+"和尋常火焰大異。\n"NOR);
                set("unit", "堆");
                set("value", 1);
                set("no_get", 1);
                set("no_drop", 1);
        }
        
        setup();
}

void init()
{
        worn = 0;
        call_out("wear", 100, 1); 
        add_action("do_kick","ti");
        add_action("do_kick","kick");
}


int do_kick(string arg){

        object ob, me, armor, temp_ob;
        mapping myfam;
        int exp1, exp2, damage;
        me=this_player();
        if( !arg || me != this_player(1)) return 0;
        ob = present(arg, environment(me));  
        
        damage = me->query_skill("feixing-shu",1);
        if(!ob) 
        {
               tell_object(me,"這裏沒有" + arg + "這個生物。\n");
               return 1;
        }

        exp1=atoi(count_div(query("combat_exp", me),100));
        exp2=atoi(count_div(query("combat_exp", ob),100));
        
        if(!ob->is_character() || !me->is_fighting(ob) )
        {
                tell_object(me,"只能對戰鬥中的對手使用。\n");
                return 1;
        }
        
        if (me->is_busy())
        {
               tell_object(me,"你正忙着呢。\n");
                return 1;
        }

        if ((damage<150)){
                message_vision(HIR"\n$N嘻嘻一笑，提起腳來，向火焰踢去，結果一聲慘叫，被火焰燒傷。\n"NOR,me);
                set_temp("die_reason", "給星宿毒火燒死了", me);
                me->receive_wound("qi", random(500));
                destruct(this_object());
                me->start_busy(random(2)+2);
                return 1;
        } else {
                
                addn("neili", -damage, me);
                message_vision(HIR"\n$N臉色一變，身形一晃，已經轉到$n身後。舉起右腳，微微一挑，將火焰向$n撥去。\n"NOR,me,ob);
                me->start_busy(random(2)+2);
                if (ob->query_skill_mapped("parry") == "dragon-strike" &&
                    !query_temp("weapon", ob) && 
                    ob->query_skill("dragon-strike",1) > damage/2 + random(damage/2))
                {
                        message_vision(HIW"\n$N一聲怒吼，雙掌收至胸口隨即緩緩推出，一道氣牆洶湧而起，卻是威霸江湖的「降龍十八掌」！\n"NOR,ob);
                        message_vision(HIR"\n火焰在彭湃的氣浪衝擊下，頃刻間以更快的速度向$N飛卷而去。\n"NOR,me);
                        temp_ob = ob;
                        ob = me;
                        me = temp_ob;
                        damage = me->query_skill("dragon-strike",1);
                }
                if(random(exp1)>random(exp2))
                {
                        if( query_temp("armor/cloth", ob)){
                                armor=query_temp("armor/cloth", ob);
                                if( query("id", armor) != "armor"){
                                        message_vision(HIR"\n只見$N身上的$n"+HIY+"被火焰燒得四散而飛。\n"NOR, ob, armor);
                                        armor->unequip();
                                        armor->move(environment(ob));
                                        armor->set_name("燒焦的"+query("name", armor));
                                        set("value", 0, armor);
                                        set("armor_prop/armor", 0, armor);
                                        ob->reset_action();
                                }
                        }
                        
                        message_vision(HIR"\n只聽見一聲慘叫，$n躲閃不及，被火焰燒中。\n"NOR,me,ob);
                        set_temp("die_reason", "給星宿毒火燒死了", ob);
                        ob->receive_wound("qi", damage, me);
                        ob->start_busy(random(2)+1);
                        destruct(this_object());
                        return 1;
                } else {
                        message_vision(HIY"\n$n大驚之下閃開，火光下只見$N微微冷笑。\n"NOR,me,ob);
                        destruct(this_object());
                        return 1;
                }
        }
        
}

void wear(int phase)
{
        worn = phase;
        switch(phase) {
        case 1:
                set("long", HIR"火焰熊熊燃燒着，"+GRN+"色作純碧，"+BLU+"鬼氣森森，"+HIR+"和尋常火焰大異。\n"NOR);
                call_out("wear", 100, phase+1); 
                break;
        case 2:
                set("long", RED"火勢越來越弱，幾乎快燒完了。\n"NOR);
                call_out("wear", 30, phase+1); 
                break;
        case 3:
                message("vision",RED"火焰漸漸地熄滅了。\n"NOR, environment(this_object()));
                destruct(this_object());
                break;
        }       
}

// End of File 

