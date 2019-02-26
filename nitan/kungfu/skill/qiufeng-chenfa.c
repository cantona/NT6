// qiufeng-chenfa.c 秋風拂塵
// Last Modified by sir 10.20.01

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N端坐不動，一招"HIC"「秋風拂葉」"NOR"，手中$w帶着一股勁風，擊向$n的臉頰",
        "lvl"    : 0,
        "skill_name" : "秋風拂葉",
]),
([        "action" : "$N單臂一揮，一招"HIW"「玉帶圍腰」"NOR"，手中$w直繞向$n的身後",
        "lvl"    : 20,
        "skill_name" : "玉帶圍腰",
]),
([        "action" : "$N身形一轉，一招"HIB"「流雲斷川」"NOR"，手中$w如矯龍般騰空一卷，猛地向$n劈頭打下",
        "lvl"    : 40,
        "skill_name" : "流雲斷川",
]),
([        "action" : "$N力貫塵梢，一招"HIG"「春風化雨」"NOR"，手中$w舞出滿天幻影，排山倒海般掃向$n全身",
        "lvl"    : 50,
        "skill_name" : "春風化雨",
]),
([        "action" : "$N忽的向前一躍，一招"HIY"「野馬分鬃」"NOR"，手中$w分擊$n左右",
        "lvl"    : 60,
        "skill_name" : "野馬分鬃",
]),
([        "action" : "$N慢步上前，一招"GRN"「竹影掃階」"NOR"，手中$w緩緩罩向$n前胸",
        "lvl"    : 70,
        "skill_name" : "竹影掃階",
])
});

int valid_enable(string usage) { return usage == "whip" || usage == "parry"; }
int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
        || ( string)query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條拂塵才能練塵法。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力不足，沒有辦法練秋風塵法, 多練些內力再來吧。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("qiufeng-chenfa", 1))
                return notify_fail("你的基本鞭法火候不足，難以領會更高深的秋風塵法。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練秋風塵法。\n");
        me->receive_damage("qi", 30);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}
mapping query_action(object me, object weapon)
{
        int d_e1 = -45;
        int d_e2 = -35;
        int p_e1 = 5;
        int p_e2 = 15;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 150;
        int m_e2 = 250;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qiufeng-chenfa", 1);
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
                "damage_type" : random(2) ? "瘀傷" : "刺傷",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        if ( this_player()->query_skill("qiufeng-chenfa", 1) >= 40 )
                return __DIR__"qiufeng-chenfa/" + action;
}

int help(object me)
{
        write(HIC"\n秋風拂塵："NOR"\n");
        write(@HELP

    秋風拂塵為古墓派李莫愁揚名天下的武功。

        學習要求：
                基本內功50級
                玉女心經10級
                內力300
HELP
        );
        return 1;
}
