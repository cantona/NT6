#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N右掌一拂而起，一招"CYN"「推窗望月」"NOR"，自側面連消帶打，登時將$n的力道帶斜。",
        "lvl"    : 0,
        "skill_name" : "推窗望月"
]),
([        "action" : "$N使一招"YEL"「分水擒龍」"NOR"，左掌陡然沿着伸長的右臂，飛快的一削而出，斬向$n的$l",
        "lvl"    : 10,
        "skill_name" : "分水擒龍"
]),
([        "action" : "$N突然使一式"HIW"「白雲幻舞」"NOR"，雙臂如旋風一般一陣狂舞，颳起一陣旋轉的氣浪。 ",
        "lvl"    : 20,
        "skill_name" : "白雲幻舞"
]),
([        "action" : "$N一招"HIY"「掌中乾坤」"NOR"，猛地側過身來，右臂自左肋下疾翻而出，拇，中兩指扣圈猛彈$n的$l",
        "lvl"    : 30,
        "skill_name" : "掌中乾坤"
]),
([        "action" : "$N一招"RED"「落日趕月」"NOR"，伸掌一拍一收，一拍無絲毫力道，一收之間，一股陰柔無比的力道才陡然發出。",
        "lvl"    : 40,
        "skill_name" : "落日趕月"
]),
([        "action" : "$N身行暴起，一式"BLU"「蟄雷為動」"NOR"，雙掌橫橫切出，掌緣才遞出，嗚嗚呼嘯之聲狂作。",
        "lvl"    : 50,
        "skill_name" : "蟄雷為動"
]),
([        "action" : "$N一招"MAG"「天羅地網」"NOR"，左掌大圈而出，右掌小圈而出，兩股奇異的力道一會之下，擊向$n的$l",
        "lvl"    : 60,
        "skill_name" : "天羅地網"
]),
([        "action" : "$N一招"HIG"「五指幻山」"NOR"，猛一吐氣，單掌有如推門，另一掌卻是迅疾無比的一推即收。",
        "lvl"    : 80,
        "skill_name" : "五指幻山"
]),
([        "action" : "$N突然大吼一聲，一招"HIR"「猛虎下山」"NOR"身行疾飛而起，猛向$n直撲而下，空氣中暴出“嗚”的一聲刺耳尖嘯。",
        "lvl"    : 100,
        "skill_name" : "猛虎下山"
]),
});

/*
mapping *action = ({
([      "action": "$N右掌一拂而起，施出「推窗望月」自側面連消帶打，登時將$n力道帶斜",
        "force"  : 187,
        "attack" : 45,
        "dodge"  : 33,
        "parry"  : 32,
        "damage" : 38,
        "lvl"    : 0,
        "skill_name" : "推窗望月",
        "damage_type": "瘀傷"
]),
([      "action": "$N施出「分水擒龍」，左掌陡然沿着伸長的右臂一削而出，斬向$n的$l",
        "force"  : 212,
        "attack" : 53,
        "dodge"  : 34,
        "parry"  : 45,
        "damage" : 43,
        "lvl"    : 20,
        "skill_name" : "推窗望月",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「白雲幻舞」，雙臂如旋風一般一陣狂舞，颳起一陣旋轉的氣浪",
        "force"  : 224,
        "attack" : 67,
        "dodge"  : 45,
        "parry"  : 53,
        "damage" : 51,
        "lvl"    : 40,
        "skill_name" : "推窗望月",
        "damage_type": "瘀傷"
]),
([      "action": "$N陡然一招「掌內乾坤」，側過身來，右臂自左肋下翻出，直拍向$n而去",
        "force"  : 251,
        "attack" : 91,
        "dodge"  : 61,
        "parry"  : 63,
        "damage" : 68,
        "lvl"    : 80,
        "skill_name" : "掌內乾坤",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「落日趕月」，伸掌一拍一收，頓時一股陰柔無比的力道向$n迸去",
        "force"  : 297,
        "attack" : 93,
        "dodge"  : 81,
        "parry"  : 87,
        "damage" : 76,
        "lvl"    : 120,
        "skill_name" : "落日趕月",
        "damage_type": "瘀傷"
]),
([      "action": "$N身行暴起，一式「蟄雷為動」，雙掌橫橫向$n切出，嗚嗚呼嘯之聲狂作",
        "force"  : 310,
        "attack" : 91,
        "dodge"  : 67,
        "parry"  : 71,
        "damage" : 73,
        "lvl"    : 160,
        "skill_name" : "蟄雷為動",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「天羅地網」，左掌大圈而出，右掌小圈而發，兩股力道同時擊向$n",
        "force"  : 324,
        "attack" : 102,
        "dodge"  : 71,
        "parry"  : 68,
        "damage" : 85,
        "lvl"    : 200,
        "skill_name" : "天羅地網",
        "damage_type": "瘀傷"
]),
([      "action": "$N施一招「五指幻山」，單掌有如推門，另一掌卻是迅疾無比的一推即收",
        "force"  : 330,
        "attack" : 112,
        "dodge"  : 55,
        "parry"  : 73,
        "damage" : 92,
        "lvl"    : 220,
        "skill_name" : "五指幻山",
        "damage_type": "瘀傷"
]),
([      "action": "$N突然大吼一聲，一招「鐵掌神威」，身行疾飛而起，再猛向$n直撲而下",
        "force"  : 321,
        "attack" : 123,
        "dodge"  : 73,
        "parry"  : 72,
        "damage" : 95,
        "lvl"    : 240,
        "skill_name" : "鐵掌神威",
        "damage_type": "瘀傷"
]),
});
*/

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鐵掌掌法必須空手。\n");

        if( query("str", me)<32 )
                return notify_fail("你的先天臂力孱弱，難以修煉鐵掌掌法。\n");

        if( query("con", me)<32 )
                return notify_fail("你的先天根骨孱弱，難以修煉鐵掌掌法。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力修為太弱，難以修煉鐵掌掌法。\n");

        if ((int)me->query_skill("force") < 230)
                return notify_fail("你的內功火候不足，難以修煉鐵掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < 150)
                return notify_fail("你的基本掌法火候不夠，難以修煉鐵掌掌法。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tie-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的鐵掌掌法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
            if (level >= action[i]["lvl"])
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -55;
        int d_e2 = -30;
        int p_e1 = -60;
        int p_e2 = -50;
        int f_e1 = 300;
        int f_e2 = 450;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("tie-zhang", 1);
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
        ]);
}

int practice_skill(object me)
{
        int cost;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鐵掌掌法必須空手。\n");

        if( query("qi", me)<150 )
                return notify_fail("你的體力太低了。\n");

        cost = me->query_skill("tie-zhang", 1) / 5 + 80;

        if( query("neili", me)<cost )
                return notify_fail("你的內力不夠練鐵掌掌法。\n");

        me->receive_damage("qi", 120);
        addn("neili", -cost, me);
        return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("tie-zhang", 1);

        if (damage_bonus < 150 || lvl < 150)
                return 0;

        if (damage_bonus / 6 > victim->query_con()/10
            /*&& random(2) == 1*/)
        {
                victim->receive_wound("qi", (damage_bonus - 90) / 2, me);

                return random(2) ? HIR "只聽$n" HIR "前胸「咔嚓」一聲脆響，竟像是"
                                   "肋骨斷折的聲音。\n" NOR:

                                   HIR "$n" HIR "一聲慘叫，胸前「咔嚓咔嚓」幾聲脆"
                                   "響，口中鮮血狂噴。\n" NOR;
        }
}

/*
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lev,damage, i;
        string msg;
        object weap;
        object piece;
        weap=query_temp("weapon", victim);
        lev=query("tiezhang-zhangfa", me);

        if( (query("neili", me)>1000) &&
                (query_temp("weapon", victim)) &&
                (query_temp("tzzf", me)) &&
                (random(me->query_str()) > victim->query_str()/2) )
        {
                if( random(query("rigidity", weap))<3 )
                {
                        message_combatd(HIW"$N運掌如刀，連擊三十六下，只聽見「啪」地一聲，$n手中的" + weap->name() + "已經斷為兩截！\n" NOR, me, victim );
                        seteuid(getuid());
                        piece = new("/clone/misc/piece");
                        piece->set_name("斷掉的"+query("name", weap),({query("id", weap),"piece"}));
                        piece->move(environment(me));
                        destruct(weap);
                }
                else
                {
                        message_combatd(HIW"$N運掌如刀，連擊三十六下，只聽見「當」地一聲，$n手中的" + weap->name() + "被刀氣震落到地上！\n" NOR, me,victim );
                        weap->move(environment(me));
                }
                victim->reset_action();
                addn("neili", -100, me);
                return 1;
        }
}
*/
string perform_action_file(string action)
{
        return __DIR__"tie-zhang/" + action;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n鐵掌掌法："NOR"\n");
        write(@HELP

    鐵掌掌法是鐵掌幫鎮幫掌法。
    鐵掌掌力渾厚惡毒，與降龍十八掌、黯然銷魂掌並稱天下。


        學習要求：
                歸元吐納法100級
                內力修為1000
HELP
        );
        return 1;
}
