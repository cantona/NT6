#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action": "$N使一招「雲裏乾坤」，右拳至左拳之底穿出，對準$n$l猛然攻去",
        "force" : 50,
        "dodge" : 20,
        "parry" : 20,
        "attack": 15,
        "damage": 20,
        "lvl"   : 0,
        "skill_name" : "雲裏乾坤",
        "damage_type": "瘀傷"
]),
([      "action": "$N左拳突然張開，拳開變掌，一招「霧裏看花」便往$n的$l招呼過去",
        "force" : 65,
        "dodge" : 25,
        "parry" : 25,
        "attack": 17,
        "damage": 23,
        "lvl"   : 20,
        "skill_name" : "霧裏看花",
        "damage_type":  "瘀傷"
]),
([      "action": "$N兩手虎口相對，往內一圈，一招「金鼓齊鳴」往$n的$l擊出",
        "force" : 85,
        "dodge" : 31,
        "parry" : 33,
        "attack": 21,
        "damage": 28,
        "lvl"   : 40,
        "skill_name" : "金鼓齊鳴",
        "damage_type":  "瘀傷"
]),
([      "action": "$N步履一沉，左拳虛晃一招，右拳使出「梅花弄影」擊向$n$l",
        "force" : 110,
        "dodge" : 42,
        "parry" : 45,
        "attack": 35,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "梅花弄影",
        "damage_type":  "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_combine(string combo)
{
        return combo == "huashan-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練華山拳法必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學華山拳法。\n");

        if ((int)me->query_skill("cuff", 1) < 20)
                return notify_fail("你的基本拳法火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("huashan-quan", 1))
                return notify_fail("你的基本拳法水平有限，無法領會更高深的華山拳法。\n");

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
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = -20;
        int p_e2 = 0;
        int f_e1 = 100;
        int f_e2 = 200;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("huashan-quan", 1);
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
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練華山拳法。\n");

        me->receive_damage("qi", 55);
        addn("neili", -45, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"huashan-quan/" + action;
}

int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n華山拳法："NOR"\n");
        write(@HELP

    華山拳法為華山氣宗拳法。

        學習要求：
           紫霞10級
HELP
        );
        return 1;
}
