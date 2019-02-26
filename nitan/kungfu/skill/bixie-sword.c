// bixie-sword.c
// Last Modified by sir 10.21.2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使一招"HIM"「羣邪辟易」"NOR"，手中$w圈起，倏地刺出，銀星點點，劍尖直向$n的$l刺去",
        "lvl"    : 0,
        "skill_name" : "羣邪辟易"
]),
([        "action" : "$N一招"HIB"「鍾馗抉目」"NOR"，劍隨身轉，圍着$n身圍疾刺，劍光霍霍罩向$n的$l",
        "lvl"    : 10,
        "skill_name" : "鍾馗抉目"
]),
([        "action" : "$N舞動$w，一招"MAG"「花開見佛」"NOR"挾著無數劍光刺向$n的$l",
        "lvl"    : 20,
        "skill_name": "花開見佛"
]),
([        "action" : "$N手中$w一聲清嘯，祭出"HIW"「流星趕月」"NOR"劍鋒閃爍不定，銀光飛舞，猛地裏一劍挺出，直刺$n$l",
        "lvl"    : 30,
        "skill_name": "流星趕月"
]),
([        "action" : "$N手中$w劍光暴長，一招"GRN"「飛燕穿柳」"NOR"往$n$l刺去",
        "lvl"    : 40,
        "skill_name": "飛燕穿柳"
]),
([        "action" : "$N手中$w化成一道光弧，直指$n$l，一招"HIG"「江上弄笛」"NOR"發出虎哮龍吟刺去",
        "lvl"    : 50,
        "skill_name": "江上弄笛"
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

int valid_learn(object me)
{
        object ob;

        if( query("gender", me) == "女性" )
                return notify_fail("女子不能學辟邪劍法。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力不夠，沒有辦法練辟邪劍法。\n");
        if( !(ob=query_temp("weapon", me) )
                 || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<30 || query("neili", me)<10 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習辟邪劍法！\n");
        me->receive_damage("qi", 30);
        addn("neili", -10, me);
//        write("你按著所學練了一遍辟邪劍法。\n");
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
        int d_e1 = 40;
        int d_e2 = 60;
        int p_e1 = 10;
        int p_e2 = 30;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 10;
        int m_e2 = 100;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("bixie-sword", 1);
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
int valid_effect(object me, object weapon, string name, int skill)
{
}

int help(object me)
{
        write(HIC"\n辟邪劍法："NOR"\n");
        write(@HELP

    辟邪劍法原自《葵花寶典》。請help bixie-jian。
    這套辟邪劍法是林震南傳下的，由於祖訓，且缺少練功的真正
法門，沒有自宮，威力就大不如了。

        學習要求：
                女性不宜學
                內力100
HELP
        );
        return 1;
}
