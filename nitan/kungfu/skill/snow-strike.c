// Last Modified by winder on Jul. 9 2001
// snow-strike.c
#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([        "action":  "$N一招"+(order[random(13)])+"「梅林小酌」"NOR"，雙手揮洒自如，輕飄飄地點向$n$l", 
        "lvl"    : 0,
        "skill_name" : "梅林小酌"
]),
([        "action":  "$N左拳平削，右拳自下劃了個半弧，一招" +(order[random(13)])+"「梅妻鶴子」"NOR",疾取$n的$l",
        "lvl"    : 10,
        "skill_name" : "梅妻鶴子"
]),
([        "action":  "$N一招" +(order[random(13)])+"「急雪落梅」"NOR"，雙掌如風中勁草，疾如流星般拍向$n$l",
        "lvl"    : 20,
        "skill_name" : "急雪落梅"
]),
([        "action":  "$N信手一招"+(order[random(13)])+"「霜雪漫天」"NOR"，散出森森寒氣，罩向$n的$l",
        "lvl"    : 30,
        "skill_name" : "霜雪漫天"
]),
([        "action":  "$N使一招"+(order[random(13)])+"「余雪殘梅」"NOR"，身隨意轉，隨手拍向$n$l",
        "lvl"    : 40,
        "skill_name" : "余雪殘梅"
]),
([        "action":  "$N長身一笑，縱身而起，一式" +(order[random(13)])+"「寒江飄梅」"NOR"，圍繞$n的$l輕飄飄接連出掌",
        "lvl"    : 50,
        "skill_name" : "寒江飄梅"
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練飛雪映梅掌必須空手。\n");
        if ((int)me->query_skill("bingxue-xinfa", 1) < 10)
                return notify_fail("你的冰雪心法修為太弱，無法練習。\n");
        if( query("max_neili", me)<10 )
                return notify_fail("你的內力修為太弱，無法練習。\n");
        return 1;
}
int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<10 )
                return notify_fail("你的內力不夠了！休息一下再練吧。\n");
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
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("snow-strike", 1);
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
        return __DIR__"snow-strike/" + action;
}

int help(object me)
{
        write(HIC"\n飛雪映梅掌："NOR"\n");
        write(@HELP

    飛雪映梅掌是雪山派掌法。

        學習要求：
                冰雪心法10級
                內力10
HELP
        );
        return 1;
}
