// fumo-jian.c 伏魔劍

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIC"「穿雲勢」"NOR"，劍鋒平指，劍勢如風，一氣呵成橫掃$n的腰間",
        "lvl" : 0,
        "skill_name" : "穿雲勢"
]),
([        "action" : "$N向前躍上一步，左手劍訣，右手$w使出一式"HIW"「破霧勢」"NOR"直刺$n的$l
",
        "lvl" : 10,
        "skill_name" : "破霧勢"
]),
([        "action" : "$N拔步挺腰，一式"HIY"「推山勢」"NOR"，手中$w沉滯無比，緩緩揮劍撞向$n的
$l",
        "lvl" : 20,
        "skill_name" : "推山勢"
]),
([        "action" : "$N一式"HIG"「攪海勢」"NOR"，$w自左而右劃出一個大弧，平平地向$n的$l揮去
",
        "lvl" : 30,
        "skill_name" : "攪海勢"
]),
([        "action" : "$N回身擰腰，右手虛抱成圓，一式"HIW"「開天勢」"NOR"，$w中宮直進，刺向$n的胸口",
        "lvl" : 40,
        "skill_name" : "開天勢"
]),
([        "action" : "$N一式"BLU"「劈地勢」"NOR"，$w從上至下猛劈，劍鋒直出，挾爆裂之聲驟然斬向$n的$l",
        "lvl" : 49,
        "skill_name" : "劈地勢"
]),
([        "action" : "$N運氣施出"MAG"「雷針勢」"NOR"，$w劍尖逼出一道青芒，閃電般破空射向$n的$l",
        "lvl" : 57,
        "skill_name" : "雷針勢"
]),
([        "action" : "$N雙腿半屈半蹲，一式"GRN"「龍吞勢」"NOR"，劍尖劃出無數圓圈，狂風驟起，籠罩天地",
        "lvl" : 64,
        "skill_name" : "龍吞勢"
]),
});

int valid_enable(string usage) { return (usage=="sword") || (usage=="parry") ; }
int valid_combine(string combo) { return combo=="cibei-dao"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<250 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("fumo-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的伏摩劍法。\n");

        return 1;
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練伏魔劍。\n");
        me->receive_damage("qi", 40);
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
        int d_e1 = 0;
        int d_e2 = 20;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 150;
        int f_e2 = 200;
        int m_e1 = 130;
        int m_e2 = 230;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("fumo-jian", 1);
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

string perform_action_file(string action)
{
        return __DIR__"fumo-jian/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n伏魔劍："NOR"\n");
        write(@HELP

    伏魔劍為少林七十二絕技之一。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
