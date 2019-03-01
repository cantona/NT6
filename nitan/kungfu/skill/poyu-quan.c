// poyu-quan.c 劈石破玉拳

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N右腳立定、左腳虛點，一式「起手式」，左右手一高一低，擊向$n的$l",
        "lvl" : 0,
        "skill_name" : "起手式"
]),
([        "action" : "$N左腳虛踏，全身右轉，一招「石破天驚」，右拳猛地擊向$n的$l",
        "lvl" : 10,
        "skill_name" : "石破天驚"
]),
([        "action" : "$N雙手大開大闔，寬打高舉，使一招「鐵閂橫門」，雙拳向$n的$l打去",
        "lvl" : 20,
        "skill_name" : "鐵閂橫門"
]),
([        "action" : "$N左掌圈花揚起，屈肘當胸，右手虎口朝上，一招「千斤墜地」打向$n的$l",
        "lvl" : 30,
        "skill_name" : "千斤墜地"
]),
([        "action" : "$N使一招「傍花拂柳」，上身前探，雙拳劃了個半圈，擊向$n的$l",
        "lvl" : 40,
        "skill_name" : "傍花拂柳"
]),
([        "action" : "$N雙拳劃弧，一記「金剛摯尾」，掌出如電，一下子切到$n的手上",
        "lvl" : 50,
        "skill_name" : "金剛摯尾"
]),
([        "action" : "$N施出「封閉手」，雙拳拳出如風，同時打向$n頭，胸，腹三處要害",
        "lvl" : 60,
        "skill_name" : "封閉手"
]),
([        "action" : "$N左腳內扣，右腿曲坐，一式「粉石碎玉」，雙拳齊齊捶向$n的胸口",
        "lvl" : 80,
        "skill_name" : "粉石碎玉"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }
int valid_combine(string combo) { return combo=="hunyuan-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練劈石破玉拳必須空手。\n");

        if ((int)me->query_skill("force") < 90)
                return notify_fail("你的內功火候不夠，無法學劈石破玉拳。\n");

        if( query("max_neili", me)<450 )
                return notify_fail("你的內力太弱，無法練劈石破玉拳。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練「劈石破玉拳」。\n");
        me->receive_damage("qi", 35);
        addn("neili", -25, me);
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
        int d_e2 = 45;
        int p_e1 = -35;
        int p_e2 = -20;
        int f_e1 = 160;
        int f_e2 = 310;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("poyu-quan", 1);
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
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"poyu-quan/" + action;
}
int help(object me)
{
        write(HIC"\n劈石破玉拳："NOR"\n");
        write(@HELP

    劈石破玉拳原為劈石及破玉兩路拳法絕學，為華山武功。
    可與混元掌互備。

        學習要求：
                紫霞神功10級
                內力50
HELP
        );
        return 1;
}
