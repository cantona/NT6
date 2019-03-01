// wudang-quan.c 武當長拳
// Last Modified by Winder on Feb. 18 2001
#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N力灌右臂，一招"RED"「七星手」"NOR"，一拳直出打向$n的$l",
        "lvl" : 0,
        "skill_name" : "七星手"
]),
([        "action" : "$N身行前探，閃身跨奔$n身側，一招"HIB"「推手」"NOR"，向$n的$l推去",
        "lvl" : 10,
        "skill_name" : "推手"
]),
([        "action" : "$N雙臂微曲，身行晃動，一招"HIM"「一條鞭」"NOR"守中帶攻打向$n的$l",
        "lvl" : 20,
        "skill_name" : "一條鞭"
]),
([        "action" : "$N馬步紮穩，左手虛晃，右手握拳一式"GRN"「直擊」"NOR"迅猛打向$n的胸口",
        "lvl" : 40,
        "skill_name" : "直擊"
]),
([        "action" : "$N施出"HIC"「雁回頭」"NOR"，縱身躍向空中，雙手同時擊向$n的$l",
        "lvl" : 50,
        "skill_name" : "雁回頭"
]),
([        "action" : "$N雙臂回環，身行微微後仰，一招"HIW"「井欄」"NOR"，纏向$n的雙手",
        "lvl" : 60,
        "skill_name" : "井欄"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="juehu-shou"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練武當長拳必須空手。\n");

        if ((int)me->query_skill("yinyun-ziqi", 1) < 10)
                return notify_fail("你的氤氳紫氣火候不夠，無法學武當長拳。\n");

        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練武當長拳。\n");

        return 1;
}
int practice_skill(object me)
{
        int lvl = me->query_skill("wudang-quan", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        me->receive_damage("qi", 20);
        return 1;
}
string query_skill_name(int level)
{
        int i = sizeof(action);

        while (i--)
                if(level > action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 35;
        int d_e2 = 55;
        int p_e1 = -25;
        int p_e2 = -5;
        int f_e1 = 120;
        int f_e2 = 220;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wudang-quan", 1);
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

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("wudang-quan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

int help(object me)
{
        write(HIC"\n武當長拳："NOR"\n");
        write(@HELP

    武當長拳為武當派入門拳法。

        學習要求：
                太極神功1級
HELP
        );
        return 1;
}
