inherit SKILL;

#include <ansi.h>

string *parry_msg = ({
        HIY "$N" HIY "招式雖猛，$n" HIY "毫無閃避之意，反手一刀橫空而出，竟將這招化解。\n" NOR,
        HIY "$n" HIY "連劈數刀，刀氣如虹，$N" HIY "趕緊收招，不敢再進。\n" NOR,
});

mapping *action = ({
([      "action" : "$N手中$w橫空掃過，一招「斷波無流」，夾雜著呼天搶地般的氣勢向$n$l砍去",
        "skill_name" : "斷波無流",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「神刀無情」，心中一陣凄苦，雙眼微閉，$w無情般的劃過，揮向$n的$l",
        "skill_name" : "神刀無情",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割傷",
]),
([      "action" : "$N使出一招「碧波神刀」，$w猶如海嘯般，舖天蓋地卷向$n",
        "skill_name" : "碧波神刀",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「滄海橫流」，手中$w輕轉，化作一道刀芒，橫空而出，劈向$n",
        "skill_name" : "滄海橫流",
        "force"  : 500,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割傷",
]),
([      "action" : "$N手拖$w，轉身躍起，一招「天刀八式」，$w一聲長鳴，八道白光射向$n的$l",
        "skill_name" : "天刀八式",
        "force"  : 600,
        "attack" : 360,
        "parry"  : 100,
        "damage" : 600,
        "damage_type" : "割傷",
]),
([      "action" : "$N一聲長嘆，回首舊事，心中一陣凄涼，一招「驚天刀煞」使出，$w發出震天般響聲，猶如鬼怪般湧向$n",
        "skill_name" : "驚天刀煞",
        "force"  : 600,
        "attack" : 360,
        "parry"  : 200,
        "damage" : 600,
        "damage_type" : "割傷",
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("str", me)<38 )
                return notify_fail("你先天臂力不足，無法修煉霸刀。\n");

        if( query("con", me)<38 )
                return notify_fail("你先天臂力不足，無法修煉霸刀。\n");

        if( query("reborn/times", me) < 3 )
                return notify_fail("你轉世次數不夠，無法領悟霸刀的精髓。\n");

        if( me->query_skill("sword",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");

        if( me->query_skill("club",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");
                
        if( me->query_skill("staff",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");
                
        if( me->query_skill("whip",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");
                
        if( me->query_skill("dagger",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");
                
        if( me->query_skill("hammer",1) && query("reborn/times", me) < 3 )
                return notify_fail("你所學的雜學太多了，無法專心研習霸刀。\n");
                                                          
        if( query("max_neili", me)<20000 )
                return notify_fail("你的內力修為不足。\n");

        if ((int)me->query_skill("force", 1) < 500)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 500)
                return notify_fail("你的武學修養不足。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本刀法火候不夠，無法領會更高深的霸刀。\n");  
                
        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的霸刀。\n");  
                              
        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本招架水平有限，無法領會更高深的霸刀。\n"); 
                
        if ((int)me->query_skill("force", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的霸刀。\n"); 
                
        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("badao", 1))
                return notify_fail("你的武學修養有限，無法領會更高深的霸刀。\n"); 
/*
        // 學會了第三刀必須要求易筋經
        if( query("can_perform/badao/san", me) )
        {
                if ((int)me->query_skill("yijinjing", 1) * 3 < (int)me->query_skill("badao", 1))
                {
                        return notify_fail("你易筋經修為不足，強行提升恐怕會走火入魔。\n");
                }
        }
  */      
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int double_attack()
{
        return 1;
}

int practice_skill(object me)
{
        return notify_fail("霸刀博大精深，無法簡單的通過練習進步。\n");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        string *desc;
        object weapon;
        
        weapon=query_temp("weapon", me);
        
        if (! objectp(weapon))return damage_bonus;
        
        desc = ({
                HIY "$N" HIY "縱身而起，舉起手中" + weapon->name() + HIY "從天劈下，猶如一道閃電劃向$n" HIY "。\n" NOR,
                HIC "$N" HIC "輕旋" + weapon->name() + HIC "，單刀直劈，招式簡單之極，卻剛猛無比。\n" NOR,
                HIR "$N" HIR "揮動手中" + weapon->name() + HIR "，頓時飛沙走石，夾雜著凌厲的刀勢，將$n" HIR "籠罩。\n" NOR,
        });

        if (me->is_busy() 
           || random(4) >= 1
           || ! living(victim) 
           || damage_bonus < 150 
            || query("neili", me)<500
           || me->query_skill("badao", 1) < 500) 
                return 0; 

        // 追加特效
        victim->receive_wound("qi", damage_bonus / 4, me);

        if (random(6) == 1)victim->start_busy(3 + random(5));
        
        return desc[random(sizeof(desc))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, cost;

        if ((int)me->query_skill("badao", 1) < 350
           || me->query_skill_mapped("parry") != "badao"
            || query("neili", me)<200
           || ! living(me) || random(5) > 2)
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force", 1) * 4 + ob->query_skill("martial-cognize", 1);
        dp = me->query_skill("badao", 1) * 5 + me->query_skill("martial-cognize", 1) + 100;

        if (dp / 2 + random(dp / 2) >= ap)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIG "毫無留戀，順勢一刀，硬將$N" HIG "逼退。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIG "$n" HIG "不退不閃，連劈數刀，$N" HIG "驚駭之下，連忙收招。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIG "$n" HIG "橫刀向前，勢與$N" HIG "共存亡，舉手反劈，竟將$N" HIG "招式化解 。\n" NOR]);
                        break;
                }
                return result;
        }
}

string perform_action_file(string action)
{
        return __DIR__"badao/" + action;
}

int difficult_level()
{
        return 30000;
}
