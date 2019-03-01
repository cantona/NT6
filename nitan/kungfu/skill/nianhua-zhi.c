// nianhua-zhi.c -拈花指

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N側身抬臂，右指劃了個半圈，一式"HIG"「瓶花落硯」"NOR"擊向$n的$l",
        "lvl" : 0,
        "skill_name" : "瓶花落硯"
]),
([        "action" : "$N左掌虛托，一式"MAG"「寒梅吐蕊」"NOR"，右指穿腋疾出，指向$n的胸前",
        "lvl" : 10,
        "skill_name" : "寒梅吐蕊"
]),
([        "action" : "$N俯身斜倚，左手半推，右手一式"BLU"「初杏問酒」"NOR"，向$n的$l劃過",
        "lvl" : 20,
        "skill_name" : "初杏問酒"
]),
([        "action" : "$N雙目微睜，一式"RED"「露草斜陽」"NOR"，雙手幻化出千百個指影，拂向$n的$l",
        "lvl" : 30,
        "skill_name" : "露草斜陽"
]),
([        "action" : "$N一式"HIB"「仰月承霖」"NOR"，左掌護住丹田，右手斜指蒼天，蓄勢點向$n的$l",
        "lvl" : 40,
        "skill_name" : "仰月承霖"
]),
([        "action" : "$N雙掌平托胸前，十指叉開，一式"CYN"「葉底留蓮」"NOR"，指向$n的周身大穴",
        "lvl" : 50,
        "skill_name" : "葉底留蓮"
]),
([        "action" : "$N雙掌翻飛，一式"HIW"「清風拂桂」"NOR"，指端迸出無數道勁氣，射向$n的全身",
        "lvl" : 60,
        "skill_name" : "清風拂桂"
]),
([        "action" : "$N一式"YEL"「菊圃秋霜」"NOR"，並指如刃，一束束銳利無儔的刀氣，凌虛向$n的$l砍去",
        "lvl" : 70,
        "skill_name" : "菊圃秋霜"
]),
([        "action" : "$N一式"HIG"「伽葉微笑」"NOR"，雙手食指交叉，指端射出一縷罡氣，穿過$n的$l",
        "lvl" : 80,
        "skill_name" : "伽葉微笑"
]),
([        "action" : "$N左掌豎立胸前，一式"HIY"「佛祖拈花」"NOR"，右手食指扣住拇指，輕輕對著$n一彈",
        "lvl" : 90,
        "skill_name" : "佛祖拈花"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) { return combo=="sanhua-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練拈花指必須空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不夠，無法學拈花指。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練拈花指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("nianhua-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的拈花指。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練拈花指。\n");
        me->receive_damage("qi", 35);
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
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 220;
        int f_e2 = 320;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("nianhua-zhi", 1);
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
        return __DIR__"nianhua-zhi/" + action;
}
int help(object me)
{
        write(HIC"\n拈花指："NOR"\n");
        write(@HELP

    拈花指為少林七十二絕技之一。
    當年迦葉尊者在靈山妙悟佛法，拈花微笑。此拈花指即取尊者
遺意而創。
    可與散花掌互備。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
