// chunyang-quan.c 純陽拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

int chunyangwuji(object me, object victim, object weapon, int damage);
mapping *action = ({
([        "action":
"只見$N身形一矮，大喝聲中以拳化勾一個"HIW"「玄鶴捕食」"NOR"對準$n的$l戳了過去",
        "lvl" : 0,
        "skill_name" : "玄鶴捕食"
]),
([        "action":
"$N左手一分，身形扭轉右拳運氣，蜿蜒前伸，一招"HIY"「金蛇尋龜」"NOR"便往$n的$l
招呼過去",
        "lvl" : 20,
        "skill_name" : "金蛇尋龜"
]),
([        "action":
"$N右拳在$n面門一晃，和身向前一撲左拳使了個"HIB"「野馬上槽」"NOR"往$n的$l狠命一掄",
        "lvl" : 40,
        "skill_name" : "野馬上槽"
]),
([        "action":
"$N步履一沉，左拳拉開，右拳帶風，一招"HIR"「黑虎掏心」"NOR"勢不可擋地擊向$n$l",
        "lvl" : 60,
        "skill_name" : "黑虎掏心"
]),
([        "action":
"只見$N拉開架式，一招"HIM"「二龍戲珠」"NOR"雙拳齊出擊向$n$l，虎虎有風",
        "lvl" : 80,
        "skill_name" : "二龍戲珠"
]),
([        "action":
"$N虛晃一拳，回身欲走，只霎那間身子一側，反腳踢起，正是"RED"「麒麟反掛」"NOR"！",
        "lvl" : 100,
        "skill_name" : "麒麟反掛"
]),
([        "action":
"$N拉開後弓步，左拳一晃，右拳隨出，左右拳掌交替變幻迭出，一招"GRN"「青龍
奪食」"NOR"往$n的$l攻去",
        "lvl" : 120,
        "skill_name" : "青龍奪食"
]),
([        "action":
"只見$N運足氣力，一個縱身，右拳從左拳後側身穿出，身隨拳至，力勢千鈞！
這一招的名字叫作"HIR"「赤龍穿雲」"NOR"",
        "lvl" : 140,
        "skill_name" : "赤龍穿雲"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanhua-juding"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練純陽拳必須空手。\n");
        if ((int)me->query_skill("force", 1) < 15)
                return notify_fail("你的內功火候不夠，無法學純陽拳。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練純陽拳。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練純陽拳。\n");
        me->receive_damage("qi", 35);
        addn("neili", -20, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -40;
        int p_e2 = -20;
        int f_e1 = 200;
        int f_e2 = 400;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("chunyang-quan", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
                "post_action": (: chunyangwuji :),
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

void finish_chunyangwuji(object me, int skill_lvl)
{
        //set_temp("apply/attack",query_temp("cyq-wuji/old_attack",  me), me);
        //set_temp("apply/unarmed_damage",query_temp("cyq-wuji/old_damage",  me), me);
        delete_temp("perform/chunyangwuji", me);
        delete_temp("cyq-wuji", me);
        me->start_busy(2+random(2));
}
int chunyangwuji(object me, object victim, object weapon, int damage)
{
        string msg;
        int cyq_wuji=query_temp("perform/chunyangwuji", me);
        int skill_lvl = me->query_skill("chunyang-quan", 1)/4;
        int exp_m=query("combat_exp", me);
        int exp_t=query("combat_exp", victim);

        if( damage > 0 ) {
                if( query("qi", victim) <= 0){
                        msg = HIR"\n\t只見$N拳風威猛，當第"+chinese_number(cyq_wuji)+"招發出時，$n已經受不住$N的拳風！\n"NOR;
                        //if( me->is_killing(query("id", victim)) )
                                victim->receive_wound("qi",query("max_qi", victim),me);
                        message_combatd(msg , me, victim);
                        finish_chunyangwuji(me, skill_lvl);
                        return 1;
                }else msg = HIY"\n\t$N一招命中，不待$n反應第"+chinese_number(cyq_wuji+1)+"招已經以排山倒海之勢向$n攻來！\n"NOR;
        }else{
                if( random(exp_m) < random(exp_t / 2) ){
                        msg = HIW"\n\t$N一招不中，頓時亂了自己的招數，純陽無極的威猛招式再也使不出來！\n"NOR;
                        message_combatd(msg , me, victim);
                        finish_chunyangwuji(me, skill_lvl);
                        return 1;
                }else{
                        msg = HIY"\n\t$N一招不中，急轉身形將第"+chinese_number(cyq_wuji+1)+"招迅速遞出，速度較前快且發力更深！\n"NOR;
                        //addn_temp("apply/unarmed_damage", skill_lvl/3, me);
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
                }
        }
        if( cyq_wuji >= query_temp("cyq-wuji/max_times", me)){
                msg = HIY"\n\t$N一口氣向$n連續攻出"+chinese_number(cyq_wuji)+"招，純陽拳的威力著實不可被輕視！\n"NOR;
                message_combatd(msg , me, victim);
                finish_chunyangwuji(me, skill_lvl);
                return 1;
        }

        addn_temp("perform/chunyangwuji", 1, me);
        //addn_temp("apply/attack", skill_lvl/2, me);
        //addn_temp("apply/unarmed_damage", -skill_lvl/2, me);
        message_combatd(msg , me, victim);
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        COMBAT_D->do_attack(me,victim,query_temp("weapon", me));
        return 1;
}


string perform_action_file(string action)
{
        return __DIR__"chunyang-quan/" + action;
}
int help(object me)
{
        write(HIC"\n純陽拳："NOR"\n");
        write(@HELP

    純陽拳為王重陽所創的全真派拳法。
    可與昊天掌互備。

        學習要求：
                先天氣元功20級
                內力100
HELP
        );
        return 1;
}
