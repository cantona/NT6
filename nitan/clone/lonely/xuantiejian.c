#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(NOR + WHT "玄鐵重劍" NOR, ({ "xuantie jian", "xuantie", "jian" }) );
        set_weight(28000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + WHT "一柄由玄鐵鑄成的無鋒長劍，著手沉重無比，但是卻蘊藏著極大的威力。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", 1);
                set("material", "steel");
                set("wield_msg", NOR + WHT "$N" NOR + WHT "抽出$n" NOR + WHT"，仗劍而立，威風凜凜，令人肅然起敬。\n" NOR);
                set("unwield_msg", NOR + WHT "$N" NOR + WHT "仰天長嘆，潛運內力，將$n" NOR + WHT "收回。\n" NOR);
                set("stable", 100);
                set("skill", ([
                        "name"         : "xuantie-jian",
                        "exp_required" : 500000,
                        "jing_cost"    : 100,
                        "difficulty"   : 100,
                        "min_skill"    : 0,
                        "max_skill"    : 30,
                ]));
        }
        init_sword(180);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int ap, dp;
        object weapon;
        string msg;

        if (me->query_skill_mapped("sword") != "xuantie-jian" ||
            me->query_skill("xuantie-jian", 1) < 200 ||
            query("neili", me)<300 )
                return damage_bonus / 2;

        ap = me->query_skill("sword");
        dp = victim->query_skill("parry");

        me->start_busy(1 + random(4));

        if (ap / 2 + random(ap) > dp)
        {
                
                victim->receive_damage("qi", ap * 3 / 4, me);
                victim->receive_wound("qi", ap * 3 / 4, me);

                if( !objectp(weapon=query_temp("weapon", victim)) || 
                      query("skill_type", weapon) == "pin" || 
                      (objectp(weapon=query_temp("weapon", victim)) && //寰宇天晶不磨損
                       weapon->is_item_make() && query("material", weapon) == "tianjing") )
                            return HIR "$N" HIR "催動內力，手中" + this_object()->name() + HIR
                                   "猶如神助一般，重重地砍在$n" HIR "身上！\n" NOR;

                if( query("consistence", weapon)>10 || 
                    weapon->is_item_make())
                {
                      msg = HIR "$N" HIR "催動內力，手中"+ this_object()->name() + HIR "猶如神助一"
                            "般，猛然回轉，重重地砍在$n" HIR "的" + weapon->name() + HIR
                            "上，\n只聽得“□~~”的一聲，" + weapon->name() + HIR "頓時火花"
                            "四射，$n" HIR "只覺得胸口氣血翻騰不息。\n" NOR;
                      
                      weapon->is_item_make()?weapon->add("consistence",-1 )
                                             : addn("consistence", -10, weapon);


                      tell_object(victim, HIG "你的" + weapon->name() + HIG "受到了嚴重的損傷！\n");
                      
                      return msg;
                    
                }

                // 非自制武器損壞
                msg = HIR "$N" HIR "催動內力，手中"+ this_object()->name() + HIR "猶如神助一"
                "般，砍在$n" HIR "的" + weapon->name() + HIR
                "上，\n只聽得“□~~”的一聲，" + weapon->name() + HIR "頓時斷為兩截。\n" NOR;

                weapon->set_name("斷掉的" + weapon->name() + NOR);
                set("no_wield", 1, weapon);
                weapon->move(environment(me));

                return msg;
        }                 
        return damage_bonus;
}
