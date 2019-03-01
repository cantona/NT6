// sanhua-zhang.c 散花掌

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N合掌抱球，一式"HIG"「春深芳草盡」"NOR"，雙掌變幻吞吐，緩緩推向$n的$l",
        "lvl" : 0,
        "skill_name" : "春深芳草盡"
]),
([      "action" : "$N五指綻開，一式"GRN"「夏閒獨蘭馨」"NOR"，左右掌穿插翻飛，疾向$n的$l拍去",
        "lvl" : 20,
        "skill_name" : "夏閒獨蘭馨"
]),
([      "action" : "$N使一式"YEL"「秋酣菊霜清」"NOR"，左掌虛托，右掌乍伸乍合，猛地插往$n的$l",
        "lvl" : 40,
        "skill_name" : "秋酣菊霜清"
]),
([      "action" : "$N雙掌血紅，一式"MAG"「冬臥聽梅吟」"NOR"，幻成漫天梅花朵朵，雨點般向$n擊去",
        "lvl" : 60,
        "skill_name" : "冬臥聽梅吟"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="nianhua-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練散花掌必須空手。\n");

        if ((int)me->query_skill("force", 1) < 60)
                return notify_fail("你的內功火候不夠，無法學散花掌。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練散花掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("sanhua-zhang", 1))
                return notify_fail("你的基本掌法火候水平有限，無法領會更高深的散花掌。\n");

        if ((int)me->query_skill("weituo-gun", 1) < 60
        &&  (int)me->query_skill("cibei-dao", 1) < 60
        &&  (int)me->query_skill("pudu-zhang", 1) < 60
        &&  (int)me->query_skill("fengyun-shou", 1) < 60)
                return notify_fail("你必須在韋陀棍，慈悲刀，普渡杖，和風雲手中任選一門練到一定境界才能練散花掌。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練散花掌。\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
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
        int d_e1 = -25;
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 140;
        int f_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("sanhua-zhang", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"sanhua-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n散花掌："NOR"\n");
        write(@HELP

    散花掌為少林七十二絕技之一。
    可與拈花指互備。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
