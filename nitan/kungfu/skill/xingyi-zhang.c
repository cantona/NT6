// xingyi-zhang.c 星移掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N兩掌一合，然後左掌拍出，身形跟進，一式"CYN"「幻形變影」"NOR"，左掌收回，右掌變幻吞吐，猛地推向$n的$l",
        "lvl" : 0,
        "skill_name" : "幻形變影"
]),
([        "action" : "$N伸出雙手，十指箕張，一式"RED"「星星點點」"NOR"，手指左右飄忽，十只指尖疾點$n的$l",
        "lvl" : 20,
        "skill_name" : "星星點點"
]),
([        "action" : "$N使一式"HIC"「漫天星鬥」"NOR"，一個飛身躍起，左掌虛立，右掌乍伸乍合，風馳電掣般向$n的$l拍了下來",
        "lvl" : 40,
        "skill_name" : "漫天星鬥"
]),
([        "action" : "$N一聲長嘯，一式"HIW"「北鬥七星」"NOR"，雙掌幻成漫天星鬥，舖天蓋地般向$n擊去",
        "lvl" : 60,
        "skill_name" : "北鬥七星"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="canhe-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練星移掌必須空手。\n");
        if ((int)me->query_skill("shenyuan-gong", 1) < 15)
                return notify_fail("你的神元功火候不夠，無法學星移掌。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練星移掌。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練星移掌。\n");
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
        int d_e1 = -35;
        int d_e2 = -5;
        int p_e1 = 5;
        int p_e2 = 35;
        int f_e1 = 180;
        int f_e2 = 280;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xingyi-zhang", 1);
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
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"xingyi-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n星移掌："NOR"\n");
        write(@HELP

    姑蘇慕容家最拿手的絕技，乃是一門借力打力之技，叫做“鬥
轉星移”。星移掌便是依此演化的慕容家傳掌法。
    可與參合指互備。

        學習要求：
                神元功15級
                內力50
HELP
        );
        return 1;
}
