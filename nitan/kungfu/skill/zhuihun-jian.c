// Last Modified by winder on Sep. 12 2001
// zhuhun-jian.c 追魂奪命劍

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N使一式"HIB"「無常抖索」"NOR"，手中$w嗡嗡微振，幻成一條白光刺向$n的$l",
        "lvl"    : 0,
        "skill_name" : "無常抖索"
]),
([        "action" : "$N錯步上前，使出"BLU"「煞神當道」"NOR"，劍意如虹，$w兇猛無匹地向$n的$l揮去",
        "lvl"    : 20,
        "skill_name" : "煞神當道"
]),
([        "action" : "$N一個斜身，一式"MAG"「望鄉回顧」"NOR"，更不回頭，倒轉劍尖，手中$w向後刺向$n的$l",
        "lvl"    : 40,
        "skill_name" : "望鄉回顧"
]),
([        "action" : "$N手中$w一沉，一式"HIB"「孟婆灌湯」"NOR"，無聲無息地紮向$n的喉頭",
        "lvl"    : 60,
        "skill_name" : "孟婆灌湯"
]),
([        "action" :"$N隨風輕輕飄落，一式"BLU"「怨魂纏足」"NOR"，和身下撲，手中$w下指，疾刺$n的下三路",
        "lvl"    : 80,
        "skill_name" : "怨魂纏足"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
                return notify_fail("你只覺追魂奪命劍毒辣無比，並無精奇之舉，不學也罷。\n");

        if( query("dex", me)<24 )
                return notify_fail("你的先天身法太差，無法學習追魂奪命劍。\n");

        if( query("max_neili", me)<2500 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force", 1) < 120)
                return notify_fail("你的基本內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < 120)
                return notify_fail("你的基本劍法火候不夠，無法學習追魂奪命劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("zhuihun-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的追魂奪命劍。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<40 || query("neili", me)<30 )
                return notify_fail("你的內力或氣不夠練追魂奪命劍法。\n");
        me->receive_damage("qi", 35);
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
        int d_e1 = 15;
        int d_e2 = 35;
        int p_e1 = -15;
        int p_e2 = -5;
        int f_e1 = 100;
        int f_e2 = 150;
        int m_e1 = 90;
        int m_e2 = 190;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("zhuihun-jian", 1);
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
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"zhuihun-jian/" + action;
}
int help(object me)
{
        write(HIM"\n追魂奪命劍："NOR"\n");
        write(@HELP

    七十二路追魂奪命劍天下無雙，是紅花會二當家無塵道長的得意武功。

        學習要求：
                紅花神功50級
                基本劍法50級
                內力修為300
HELP
        );
        return 1;
}
