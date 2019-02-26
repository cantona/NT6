// weapond.c

#include <ansi.h>
#include <combat.h>

mapping weapon_actions = ([
        "slash": ([
                "damage_type":  "割傷",
                "action":       "$N揮動$w，斬向$n的$l",
                "parry":        20,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "slice": ([
                "damage_type":  "劈傷",
                "action":       "$N用$w往$n的$l砍去",
                "dodge":        20,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "chop": ([
                "damage_type":  "劈傷",
                "action":       "$N的$w朝著$n的$l劈將過去",
                "parry":        -20,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "hack": ([
                "action":       "$N揮舞$w，對準$n的$l一陣亂砍",
                "damage_type":  "劈傷",
                "damage":       30,
                "dodge":               30,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "thrust": ([
                "damage_type":  "刺傷",
                "action":       "$N用$w往$n的$l刺去",
                "dodge":        15,
                "parry":        -15,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "pierce": ([
                "action":       "$N的$w往$n的$l狠狠地一捅",
                "damage_type":  "刺傷",
                "dodge":        -30,
                "parry":        -30,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "whip": ([
                "action":       "$N將$w一揚，往$n的$l抽去",
                "damage_type":  "鞭傷",
                "dodge":        -20,
                "parry":        30,
        ]),
        "impale": ([
                "action":       "$N用$w往$n的$l直戳過去",
                "damage_type":  "刺傷",
                "dodge":        -10,
                "parry":        -10,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "strike": ([
                "action":       "$N一個大舒臂掄起$w，對着$n的$l往下一砸",
                "damage_type":  "築傷",
                "dodge":        -10,
                "parry":        -10,
                "post_action":  (: call_other, __FILE__, "slash_weapon" :),
        ]),
        "bash": ([
                "action":       "$N揮舞$w，往$n的$l用力一砸",
                "damage_type":  "挫傷",
                "post_action":  (: call_other, __FILE__, "bash_weapon" :),
        ]),
        "crush": ([
                "action":       "$N高高舉起$w，往$n的$l當頭砸下",
                "damage_type":  "挫傷",
                "post_action":  (: call_other, __FILE__, "bash_weapon" :),
        ]),
        "slam": ([
                "action":       "$N手握$w，眼露兇光，猛地對準$n的$l揮了過去",
                "damage_type":  "挫傷",
                "post_action":  (: call_other, __FILE__, "bash_weapon" :),
        ]),
        "throw": ([
                "action":       "$N將$w對準$n的$l射了過去",
                "damage_type":  "刺傷",
                "post_action":  (: call_other, __FILE__, "throw_weapon" :),
        ]),
]);

varargs mapping query_action()
{
        string verb, *verbs;

        verbs=query("verbs", previous_object());

        if( !pointerp(verbs) ) return weapon_actions["hit"];
        else {
                verb = verbs[random(sizeof(verbs))];
                if( !undefinedp(weapon_actions[verb]) )
                        return weapon_actions[verb];
                else return weapon_actions["hit"];
        }        
}

void throw_weapon(object me, object victim, object weapon, int damage)
{
        if( objectp(weapon) )
        {
                if( (int)weapon->query_amount()==1 )
                {
                        weapon->unequip();
                        tell_object(me,"\n你的"+query("name", weapon)+"用完了！\n\n");
                }
                weapon->add_amount(-1);
        }
}

void bash_weapon(object me, object victim, object weapon, int damage)
{
        object ob;
        int wap, wdp;

        if( objectp(weapon) && damage==RESULT_PARRY &&
                ob=query_temp("weapon", victim) )
        {
                wap = (int)weapon->weight() / 500
                        +query("rigidity", weapon )
                        +query("str", me);
                wdp = (int)ob->weight() / 500
                        +query("rigidity", ob )
                        +query("str", victim);
                wap = random(wap);

                if( wap > 5 * wdp)
                {
                        message_vision(HIM"只聽見「啪」地一聲，$N手中的"+ob->name()+HIM"已經斷為兩截！\n"NOR,victim);
                        ob->unequip();
                        ob->move(environment(victim));
                        set("name", "斷掉的"+query("name", ob), ob);
                        set("value", 49, ob);
                        set("weapon_prop", 0, ob);
                        victim->reset_action();
                } 
                else if( wap > 3 * wdp )
                        {
                                message_vision(HIY"$N只覺得手中"+ob->name()+HIY"把持不定，脱手飛出！\n"NOR,victim);
                                ob->unequip();
                                ob->move(environment(victim));
                                victim->reset_action();
                        } 
                        else if( wap > wdp )
                                {
                                        message_vision(HIW "$N只覺得手中" + ob->name() + HIW"一震，險些脱手！\n"NOR, victim);
                                }
                                else
                                {
                                        message_vision(HIR"$N的"+weapon->name()+HIR"和$n的"+ob->name()+HIR"相擊，冒出點點的火星。\n"NOR,me,victim);
                                }
        }
}

void slash_weapon(object me, object victim, object weapon, int damage)
{
        object weapon1;        
        string poison;
        int poison1, wp, wp1, wp2;  
        weapon1=query_temp("weapon", victim);

        if(objectp(weapon) && objectp(weapon1))
        {
                wp=query("weapon_prop/damage", weapon);
                wp1=query("weapon_prop/damage", weapon1);
                wp2=query("rigidity", weapon1);
                if(wp > 1000) wp = 1000;
                if(wp1 > 1000) wp1 = 1000;
                if(wp2 > 100) wp2 = 100;
                if( wp > 0 && wp > (wp1 + wp2) * 5 &&
                        random(query("str", me))>query("str", victim)/2 )
                {
                        message_vision(WHT "只聽見「哐」地一聲輕響，$N手中的"+weapon1->name()+WHT"已經被"+weapon->name()+WHT"削為兩截！\n"NOR, victim );
                        weapon1->unequip();
                        weapon1->move(environment(victim));
                        set("name", "斷掉的"+query("name", weapon1), weapon1);
                        set("value", 49, weapon1);
                        set("weapon_prop", 0, weapon1);
                        victim->reset_action();
                } 
        }

   if( objectp(weapon) && stringp(poison=query("poisoned", weapon)) && 
                (query("eff_qi", victim)<query("max_qi", victim)) )
                if( intp(poison1=query("poison_number", weapon)) && random(10)>5
                        && poison1 > 1 && victim->query_condition(poison) < 50)
                {
                        if (poison1 == 2)                   
                                set_temp("apply/long", ({query("long", weapon)+"好像是被餵過劇毒，不過效果已經不明顯了。\n"}), weapon);
                                addn("poison_number", -1, weapon);
                                victim->apply_condition(poison, victim->query_condition(poison) + random(10));
                                message_vision(HIR"$n只覺得傷口上一麻，大叫一聲：不好！\n"NOR,me,victim);
                                if( !victim->is_killing(query("id", me)))victim->kill_ob(me);
                }
}
