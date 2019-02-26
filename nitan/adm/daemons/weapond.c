// weapond.c

#pragma optimize
#pragma save_binary

#include <ansi.h>
#include <combat.h>

varargs mapping query_action();

mapping weapon_actions = ([
"slash" : ([ "damage_type" : "割傷",
             "action"      : "$N揮動$w，斬向$n的$l",
             "parry"       : 20,  ]),

"slice" : ([ "damage_type" : "劈傷",
             "action"      : "$N用$w往$n的$l砍去",
             "dodge"       : 20,  ]),

"chop"  : ([ "damage_type" : "劈傷",
             "action"      : "$N的$w朝著$n的$l劈將過去",
             "parry"       : -20, ]),

"hack"  : ([ "action"      : "$N揮舞$w，對準$n的$l一陣亂砍",
             "damage_type" : "劈傷",
             "damage"      : 30,
             "dodge"       : 30,  ]),

"thrust": ([ "damage_type" : "刺傷",
             "action"      : "$N用$w往$n的$l刺去",
             "dodge"       : 15,
             "parry"       : -15, ]),

"pierce": ([ "action"      : "$N的$w往$n的$l狠狠地一捅",
             "damage_type" : "刺傷",
             "dodge"       : -30,
             "parry"       : -30, ]),

"whip" :  ([ "action"      : "$N將$w一揚，往$n的$l抽去",
             "damage_type" : "鞭傷",
             "dodge"       : -20,
             "parry"       : 30,  ]),

"impale": ([ "action"      : "$N用$w往$n的$l直戳過去",
             "damage_type" : "刺傷",
             "dodge"       : -10,
             "parry"       : -10, ]),

"strike": ([ "action"      : "$N一個大舒臂掄起$w，對着$n的$l往下一砸",
             "damage_type" : "築傷",
             "dodge"       : -10,
             "parry"       : -10, ]),

"bash" :  ([ "action"      : "$N揮舞$w，往$n的$l用力一砸",
             "damage_type" : "挫傷",
             "post_action" : (: call_other, __FILE__, "bash_weapon" :), ]),

"crush" : ([ "action"      : "$N高高舉起$w，往$n的$l當頭砸下",
             "damage_type" : "挫傷",
             "post_action" : (: call_other, __FILE__, "bash_weapon" :), ]),

"slam"  : ([ "action"      : "$N手握$w，眼露兇光，猛地對準$n的$l揮了過去",
             "damage_type" : "挫傷",
             "post_action" : (: call_other, __FILE__, "bash_weapon" :), ]),

"throw" : ([ "action"      : "$N將$w對準$n的$l射了過去",
             "damage_type" : "刺傷",
             "post_action" : (: call_other, __FILE__, "throw_weapon" :), ]),
]);

varargs mapping query_action()
{
        string verb, *verbs;

        verbs=query("verbs", previous_object());

        if (! pointerp(verbs))
                return weapon_actions["hit"];
        else
        {
                verb = verbs[random(sizeof(verbs))];

                if (! undefinedp(weapon_actions[verb]))
                        return weapon_actions[verb];
                else
                        return weapon_actions["hit"];
        }       
}

void throw_weapon(object me, object victim, object weapon, int damage)
{
        if (objectp(weapon))
        {
                if ((int) weapon->query_amount() == 1)
                {
                        weapon->unequip();
                        tell_object(me,"\n你的"+query("name", weapon)+
                                        "用完了！\n\n");
                }
                weapon->add_amount(-1);
        }
}

void bash_weapon(object me, object victim, object weapon, int damage)
{
        object ob;
        int wap, wdp;

        if (objectp(weapon) &&
            damage == RESULT_PARRY &&
            ob=query_temp("weapon", victim) )
        {
                wap = (int)weapon->weight() / 500
                        +query("rigidity", weapon )
                        +query("str", me);
                wdp = (int)ob->weight() / 500
                        +query("rigidity", ob )
                        +query("str", victim);
                wap = random(wap);
                if( wap > 2 * wdp )
                {
                        message_vision(HIW "$N" HIW "只覺得手中" + ob->name() +
                                       HIW "把持不定，脱手飛出！\n" NOR, victim);
                        ob->unequip();
                        ob->move(environment(victim));
                        victim->reset_action();
                } else
                if (wap > wdp)
                {
                        message_vision(HIY "$N" HIY "只覺得手中" + ob->name() +
                                       HIY "一震，險些脱手！\n" NOR, victim);
                } else
                if (wap > wdp / 2 && !ob->is_item_make() && query("material", ob) == "no name" && query("material", ob) == "tian jing" ) 
                {
                        message_vision(HIW "只聽見「啪」地一聲，$N" HIW "手中的"
                                       + ob->name() + HIW "已經斷為兩截！\n" NOR,
                                       victim );
                        ob->unequip();
                        ob->move(environment(victim));
                        set("name", "斷掉的"+query("name", ob), ob);
                        set("value", 0, ob);
                        set("weapon_prop", 0, ob);
                        victim->reset_action();
                } else
                {
                        message_vision(HIY "$N" HIY "的" + weapon->name() + HIY
                                       "和$n" HIY "的" + ob->name() + HIY "相擊"
                                       "，冒出點點的火星。\n" NOR, me, victim);
                }
        }
}
