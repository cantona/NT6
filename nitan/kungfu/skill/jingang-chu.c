// jingang-chu.c 金剛降魔杵

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N高舉手中$w，使出一招"HIY"「金剛再世」"NOR"，直劈$n的$l",
        "skill_name" : "金剛再世",
        "lvl" : 0
]),
([        "action" : "$N使出"HIY"「金剛伏魔」"NOR"，單手舞動$w，一伏身，$w橫掃$n的下盤",
        "skill_name" : "金剛伏魔",
        "lvl" : 8
]),
([        "action" : "$N反身仰面，使出一式"HIY"「金剛宣法」"NOR"，雙手握$w，一棍直刺$n的$l",
        "skill_name" : "金剛宣法",
        "lvl" : 16
]),
([        "action" : "$N使出一招"HIY"「引趣眾生」"NOR"，雙手舉棍撩向$n的襠部",
        "skill_name" : "引趣眾生",
        "lvl" : 24
]),
([        "action" : "$N舞動手中$w，使出"HIY"「歌舞閻羅」"NOR"，頓時罩住$n的全身",
        "skill_name" : "歌舞閻羅",
        "lvl" : 32
]),
([        "action" : "$N使出一招"HIY"「浮游血海」"NOR"，全身貼地而飛，一棍直搗$n的$l",
        "skill_name" : "浮游血海",
        "lvl" : 40
]),
([        "action" : "$N使出一式"HIY"「驅鬼御魔」"NOR"，以棍支地，雙足飛揣$n的面門",
        "skill_name" : "驅鬼御魔",
        "lvl" : 48
]),
([        "action" : "$N運力於掌，使出"HIY"「蕩魔除妖」"NOR"，飛身疾進，手中$w橫掃$n的$l",
        "skill_name" : "蕩魔除妖",
        "lvl" : 56
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，難以修煉金剛降魔杵。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺，難以修煉金剛降魔杵。\n");

        if ((int)me->query_skill("staff", 1) < 50)
                return notify_fail("你的基本錘法不夠，難以修煉金剛降魔杵。\n");

        if ((int)me->query_skill("staff", 1) < (int)me->query_skill("jingang-chu", 1))
                return notify_fail("你的基本錘法水平有限，無法領會更高深的金剛降魔杵。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠，練不了金剛降魔杵。\n");
        me->receive_damage("qi", 40);
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
        int d_e1 = -45;
        int d_e2 = -10;
        int p_e1 = 15;
        int p_e2 = 45;
        int f_e1 = 250;
        int f_e2 = 300;
        int m_e1 = 190;
        int m_e2 = 290;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jingang-chu", 1);
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
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
       return __DIR__"jingang-chu/" + action;
}

int help(object me)
{
        write(HIC"\n金剛降魔杵："NOR"\n");
        write(@HELP

    金剛降魔杵為雪山寺器械武功。

        學習要求：
                龍象般若功或小無相功20級
                內力100
HELP
        );
        return 1;
}
