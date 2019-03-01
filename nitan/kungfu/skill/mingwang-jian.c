// mingwang-jian.c 不動明王劍

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N怒目圓睜，使出一招"HIB"「不動」"NOR"，手中$w一抖，直刺$n的$l",
        "skill_name" : "不動",
        "lvl" : 0
]),
([        "action" : "$N使出一式"HIW"「起手出劍」"NOR"，足下一滑，劍芒閃向$n的$l",
        "skill_name" : "起手出劍",
        "lvl" : 10
]),
([        "action" : "$N使出一招"HIY"「山崩」"NOR"，縱身躍入半空，$w如山崩般劈向$n的$l",
        "skill_name" : "山崩",
        "lvl" : 20
]),
([        "action" : "$N使出"HIC"「千旋轉」"NOR"，將$w舞得如紡車一般，忽然一劍刺向$n的$l",
        "skill_name" : "千旋轉",
        "lvl" : 30
]),
([        "action" : "$N使出一招"HIM"「降魔舞」"NOR"，全身勁氣貫于$w中，劍氣直指$n的$l",
        "skill_name" : "降魔舞",
        "lvl" : 40
]),
([        "action" : "$N單足獨立，使出一式"MAG"「鶴舞」"NOR"，一道劍光如白影般向$n的$l掃去",
        "skill_name" : "鶴舞",
        "lvl" : 50
]),
([        "action" : "$N使出一招"GRN"「龍騰」"NOR"，手中$w如遊龍般撲向$n的$l",
        "skill_name" : "龍騰",
        "lvl" : 60
]),
([        "action" : "$N飛身一躍，居高臨下使出"BLU"「花雨滿天」"NOR"，頓時劍尖如雨刺向$n的$l",
        "skill_name" : "花雨漫天",
        "lvl" : 80
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
//int valid_combine(string combo) { return combo=="xuedao-daofa"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 70)
                return notify_fail("你的內功火候太淺。\n");

        if (me->query_skill("sword", 1) < me->query_skill("mingwang-jian", 1))
                return notify_fail("你的基本劍法火候有限，無法領會更高深的不動明王劍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30
         || query("neili", me)<15 )
                return notify_fail("你的內力或氣不夠，練不了不動明王劍。\n");
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
        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = 0;
        int p_e2 = 20;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 40;
        int m_e2 = 120;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("mingwang-jian", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : random(2) ? "割傷" : "刺傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"mingwang-jian/" + action;
}

int help(object me)
{
        write(HIC"\n不動明王劍："NOR"\n");
        write(@HELP

    雪域雪山寺劍法。

        學習要求：
                龍象功或小無相功20級
                內力100
HELP
        );
        return 1;
}
