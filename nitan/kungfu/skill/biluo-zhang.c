// biluo-zhang.c 碧羅掌
// Last Modified by sir 10.23.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N一式「起手式」，左手帶風，右手拍向$n的$l",
        "force"  : 30,
        "attack" : 5,
        "dodge"  : 15,
        "parry"  : 20,
        "damage" : 10,
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "起手式"
]),
([      "action" : "$N右手微台，直出向前，一式「截手式」，疾向$n的$l擊去",
        "force"  : 45,
        "attack" : 8,
        "dodge"  : 20,
        "parry"  : 35,
        "damage" : 13,
        "lvl"    : 10,
        "damage_type" : "瘀傷",
        "skill_name"  : "截手式"
]),
([      "action" : "$N使一式「逆風式」，左掌微拂，右掌順勢而進，猛地插往$n的$l",
        "force"  : 60,
        "attack" : 12,
        "dodge"  : 25,
        "parry"  : 20,
        "damage" : 15,
        "lvl"    : 25,
        "damage_type" : "瘀傷",
        "skill_name"  : "逆風式"
]),
([      "action" : "$N雙掌隱隱泛出青氣，一式「御氣式」，掌風激勁，雨點般向$n擊去",
        "force"  : 76,
        "attack" : 15,
        "dodge"  : 30,
        "parry"  : 25,
        "damage" : 18,
        "lvl"    : 38,
        "damage_type" : "瘀傷",
        "skill_name"  : "御氣式"
]),
([      "action" : "$N雙掌不斷反轉，使出一式「潛手式」，雙掌併攏，筆直地向$n的$l襲去",
        "force"  : 52,
        "attack" : 18,
        "dodge"  : 33,
        "parry"  : 30,
        "damage" : 25,
        "lvl"    : 55,
        "damage_type" : "瘀傷",
        "skill_name"  : "潛手式"
]),
([      "action" : "$N身形一變，使一式「齊掌式」，雙掌帶着蕭剎的勁氣，猛地擊往$n的$l",
        "force"  : 90,
        "attack" : 20,
        "dodge"  : 38,
        "parry"  : 35,
        "damage" : 30,
        "lvl"    : 65,
        "damage_type" : "瘀傷",
        "skill_name"  : "齊掌式"
]),
([      "action" : "$N使一式「青煙式」，雙掌如夢似幻，同時向$n的$l擊去",
        "force"  : 120,
        "attack" : 22,
        "dodge"  : 42,
        "parry"  : 38,
        "damage" : 33,
        "lvl"    : 72,
        "damage_type" : "瘀傷",
        "skill_name"  : "青煙式"
]),
([      "action" : "$N一式「流雲式」，身法忽變，似流雲飄忽，不覺已擊到$n的$l上",
        "force"  : 140,
        "attack" : 24,
        "dodge"  : 45,
        "parry"  : 45,
        "damage" : 38,
        "lvl"    : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "流雲式"
]),
([      "action" : "$N突地一招「風雷式」，雙掌挾着一陣風雷之勢，猛地劈往$n的$l",
        "force"  : 160,
        "attack" : 26,
        "dodge"  : 50,
        "parry"  : 50,
        "damage" : 50,
        "lvl"    : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "風雷式"
]),
});

int valid_enable(string usage) { return usage=="parry" || usage=="strike"; }
//int valid_combine(string combo) { return combo=="luoyan-hand"; }
int valid_combine(string combo)
{
        return combo == "henshan-quan";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練碧羅掌法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學碧羅掌法。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法碧羅掌法。\n");

        if ((int)me->query_skill("strike", 1) < 20)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("biluo-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的碧羅掌法。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練碧羅掌。\n");
        me->receive_damage("qi", 40);
        addn("neili", -30, me);
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
        int d_e1 = 15;
        int d_e2 = 50;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 30;
        int f_e2 = 160;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("biluo-zhang", 1);
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
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"biluo-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n碧羅掌："NOR"\n");
        write(@HELP

    碧羅掌是衡山派的掌法。
    可與大落雁手互備。

        學習要求：
                回雁心法15級
                內力50
HELP
        );
        return 1;
}
