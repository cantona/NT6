// jinyu-quan.c 金玉拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一招"HIY"「金光燦爛」"NOR"，雙拳一上一下, 向$n揮去",
        "lvl"    : 0,
        "skill_name" : "金光燦爛"
]),
([        "action" : "$N一招"MAG"「其利斷金」"NOR"，幻出一片拳影，氣勢如虹，擊向$n的頭部",
        "lvl"    : 20,
        "skill_name" : "其利斷金"
]),
([        "action" : "$N身影向上飄起，臉浮微笑，一招"BLU"「藍田美玉」"NOR"，輕輕拍向$n的$l",
        "lvl"    : 40,
        "skill_name" : "藍田美玉"
]),
([        "action" : "$N一招"HIC"「金玉其外」"NOR"，雙拳一合，$n只覺到處是$N的拳影",
        "lvl"    : 60,
        "skill_name" : "金玉其外"
]),
([        "action" : "$N繞著$n一轉，滿場遊走，拳出如風，不絕擊向$n，正是一招"GRN"「金玉滿堂」"NOR"",
        "lvl"    : 80,
        "skill_name" : "金玉滿堂"
]),
([        "action" : "只見$N一個側身退步，左手虛晃，突然猛跨兩步，已到$n面前，
右拳陡出，事先絕無征兆，迅如崩雷，一招"HIM"「點石成金」"NOR"擊向$n的前胸",
        "lvl"    : 100,
        "skill_name" : "點石成金"
]),
([        "action" : "$N一招"CYN"「眾口鑠金」"NOR"，撲向$n，似乎$n的全身都被拳影籠罩",
        "lvl"    : 120,
        "skill_name" : "眾口鑠金"
]),
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="wuluo-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練金玉拳必須空手。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候不夠，無法練金玉拳。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練金玉拳。\n");

        if ((int)me->query_skill("cuff") < 20)
                return notify_fail("你的基本拳法等級太低，無法練金玉拳。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("jinyu-quan", 1))
                return notify_fail("你的基本拳法火候水平有限，無法領會更高深的金玉拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練金玉拳。\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 90;
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinyu-quan", 1);
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
                "damage_type" : "瘀傷",
        ]);
}

int learn_bonus() { return 30; }
int practice_bonus() { return 25; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"jinyu-quan/" + action;
}

int help(object me)
{
        write(HIC"\n金玉拳："NOR"\n");
        write(@HELP

    金玉拳為天南大理段家的武功。
    可與五羅輕煙掌互備。

        學習要求：
                枯榮禪功20級
                內力100
HELP
        );
        return 1;
}
