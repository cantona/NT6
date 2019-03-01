//hanxing-bada.c 寒星八打
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N使一招「隕星乍現」，手中$w疾射$n的$l",
        "force": 20,
        "dodge": 20,
        "damage":90,
        "lvl" : 0,
        "skill_name" : "隕星乍現",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N使出「玉隼擊空」，雙手下沉$w陡的向上飛出直襲$n的$l",
        "force": 25,
        "dodge": 20,
        "damage": 70,
        "lvl" : 10,
        "skill_name": "玉隼擊空",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N一招「暮靄沉沉」，長袖一揮，手中$w從腋下激射$n的$l",
        "force":35,
        "dodge": 30,
        "damage":40,
        "lvl" : 120,
        "skill_name": "暮靄沉沉",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N手中$w一式「長電裂空」，$w幻作一道白光直奔$n的$l",
        "force":80,
        "dodge": 40,
        "damage":90,
        "lvl" : 30,
        "skill_name": "長電裂空",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N縱身一躍，手中$w一招「蒼龍入海」射向$n的$l",
        "force":120,
        "dodge": 45,
        "damage":170,
        "lvl" : 40,
        "skill_name":"蒼龍入海",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N手扣$w,憑空一指，一招「巴山夜雨」灑向$n的$l",
        "force":160,
        "dodge": 20,
        "damage":50,
        "lvl" : 50,
        "skill_name": "巴山夜雨",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N身形一晃，使一招「彗星橫空」$w脱手而出，襲向$n的$l",
        "force":220,
        "dodge": 50,
        "damage":60,
        "lvl" : 60,
        "skill_name": "彗星橫空",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
([        "action":"$N身形一轉手中$w使一招「後弈射日」畫出一道光弧襲向$n的$l",
        "force":135,
        "dodge": 55,
        "damage":140,
        "lvl" : 100,
        "skill_name": "后羿射日",
        "damage_type": "刺傷",
        "post_action": (: call_other, WEAPON_D, "throw_weapon" :),
]),
});

int valid_enable(string usage) { return usage=="throwing" || usage=="parry"; }
int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠，沒有辦法練寒星八打。\n");

        if ((int)me->query_skill("throwing", 1) < (int)me->query_skill("hanxing-bada", 1))
                return notify_fail("你的基本暗器水平有限，無法領悟更高深的寒星八打術。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

/*
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "throwing" )
                return notify_fail("你使用的武器不對。\n");
*/
        if( query("qi", me)<30 || query("neili", me)<3 )
                return notify_fail("你的內力或氣不夠，沒有辦法練習寒星八打。\n");
        me->receive_damage("qi", 30);
        addn("neili", -3, me);
//        write("你按着所學練了一遍寒星八打。\n");
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
        int i, level;
        level = (int) me->query_skill("hanxing-bada",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int learn_bonus() { return 10; }
int practice_bonus() { return 10; }
int success() { return 5; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"hanxing-bada/" + action;
}

int help(object me)
{
        write(HIC"\n寒星八打："NOR"\n");
        write(@HELP

    紅花會趙半山的絕技。

        學習要求：
                紅花心法50級
                內力修為100
HELP
        );
        return 1;
}
