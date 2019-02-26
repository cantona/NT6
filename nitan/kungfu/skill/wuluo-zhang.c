// wuluo-zhang.c 五羅輕煙掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([      "action" : "$N屏息靜氣，手起一掌"HIB"「輕煙裊裊」"NOR"，輕輕柔柔地拍向$n",
        "lvl"    : 0,
        "skill_name" : "輕煙裊裊"
]),
([      "action" : "$N輕輕淺笑，繞到$n身後，左手做勢温柔輕擁$n腰間。$n蹙眉急躲，$N右手一招"BLU"「煙霧繚繞」"NOR"，無聲無息向$n的$l拍到",
        "lvl"    : 20,
        "skill_name" : "煙霧繚繞"
]),
([      "action" : "$N一招"MAG"「煙海雲濤」"NOR"，雙掌幻化出一片掌影，如一陣輕煙，將$n細細密密地籠罩於內",
        "lvl"    : 40,
        "skill_name" : "煙海雲濤"
]),
([      "action" : "$N返身越出圈外，回首一招"HIC"「雲煙渺渺」"NOR"，遠遠地向$n的$l輕輕拍出兩掌，掌風颳到，陡然變盛直讓$n呼不出氣來",
        "lvl"    : 60,
        "skill_name" : "雲煙渺渺"
]),
([      "action" : "$N左掌從右掌內圍翻出，輕飄飄地向$n拍去，看到$n起手招架，右掌卻自胸口疾速圈出，一招"HIW"「煙霧瀰漫」"NOR"，趕超左掌，拍向$n的$l",
        "lvl"    : 80,
        "skill_name" : "煙霧瀰漫"
]),
([      "action" : "$N雙掌齊推，振起一陣勁風，一招"HIW"「煙消雲散」"NOR"在一丈開外擊向$n",
        "lvl"    : 100,
        "skill_name" : "煙消雲散"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_combine(string combo) { return combo=="jinyu-quan"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練五羅輕煙掌必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候不夠，無法學五羅輕煙掌。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為太弱，無法練五羅輕煙掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("wuluo-zhang", 1))
                return notify_fail("你的基本掌法火候有限，無法領會更高深的五羅輕煙掌。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練五羅輕煙掌。\n");
        me->receive_damage("qi", 25);
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
        int d_e1 = -20;
        int d_e2 = 0;
        int p_e1 = 20;
        int p_e2 = 50;
        int f_e1 = 130;
        int f_e2 = 230;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("wuluo-zhang", 1);
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

string perform_action_file(string action)
{
        return __DIR__"wuluo-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n五羅輕煙掌："NOR"\n");
        write(@HELP

    五羅輕煙掌是天南大理段家的武功。
    可與金玉拳互備。

        學習要求：
                基本內功20級
                內力100
HELP
        );
        return 1;
}

