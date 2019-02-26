#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action" : "$N單手一揚，一招「無孔不入」，手中$w抖得筆直，對準$n"
                   "當頭罩下",
        "force"  : 90,
        "attack" : 13,
        "dodge"  : 10,
        "parry"  : 10,
        "damage" : 20,
        "lvl" : 0,
        "skill_name" : "無孔不入",
        "damage_type":  "劈傷"
]),
([      "action" : "$N身形一轉，一招「無所不至」，手中$w如矯龍般騰空一卷"
                   "，猛地擊向$n",
        "force"  : 130,
        "attack" : 24,
        "dodge"  : 28,
        "parry"  : 15,
        "damage" : 36,
        "lvl" : 30,
        "skill_name" : "無所不至",
        "damage_type":  "劈傷"
]),
([      "action" : "$N唰的一抖長鞭，一招「無所不為」，手中$w抖得筆直，刺向"
                   "$n$l",
        "force"  : 170,
        "attack" : 35,
        "dodge"  : 36,
        "parry"  : 21,
        "damage" : 55,
        "lvl" : 60,
        "skill_name" : "無所不為",
        "damage_type":  "刺傷"
]),
([      "action" : "$N力貫鞭梢，一招「風起雲湧」，手中$w舞出滿天鞭影，排山倒"
                   "海般掃向$n全身",
        "force"  : 200,
        "attack" : 40,
        "dodge"  : 50,
        "parry"  : 30,
        "damage" : 64,
        "lvl" : 90,
        "skill_name" : "風起雲湧",
        "damage_type":  "刺傷"
]),
([      "action" : "$N運氣於腕，一招「風捲殘雲」，手中$w向一根銅棍般直擊向$n",
        "force"  : 220,
        "attack" : 50,
        "dodge"  : 66,
        "parry"  : 38,
        "damage" : 80,
        "lvl" : 120,
        "skill_name" : "風捲殘雲",
        "damage_type":  "內傷"
]),
([      "action" : "$N單臂一揮，一招「欲擒故縱」，手中$w直擊向$n腰肋",
        "force"  : 260,
        "attack" : 56,
        "dodge"  : 80,
        "parry"  : 32,
        "damage" : 98,
        "lvl" : 150,
        "skill_name" : "欲擒故縱",
        "damage_type":  "內傷"
]),
([      "action" : "$N高高躍起，一招「無影無蹤」，手中$w筆直向$n當頭罩下",
        "force"  : 300,
        "attack" : 70,
        "dodge"  : 110,
        "parry"  : 40,
        "damage" : 130,
        "lvl" : 200,
        "skill_name" : "無影無蹤",
        "damage_type":  "內傷"
])
});

int valid_enable(string usage)
{
        return usage == "whip" || usage == "parry";
}

int valid_learn(object me)
{
        object weapon;

        if( query("character", me) != "心狠手辣" && query("character", me) != "國士無雙" )
                return notify_fail("練三無三不手必須要心狠手辣，我看你這點做得還不夠。\n"); 

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練三無三不手。\n");

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力不足，沒有辦法練三無三不手。\n");

        if ((int)me->query_skill("force") < 120)
                return notify_fail("你的內功火候太淺，沒有辦法練三無三不手。\n");

        if ((int)me->query_skill("whip", 1) < 100)
                return notify_fail("你的基本鞭法火候太淺，沒有辦法練三無三不手。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("sanwu-shou", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的沒有辦法練三無三不手。\n");

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
        level   = (int) me->query_skill("sanwu-shou",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練三無三不手。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練三無三不手。\n");

        me->receive_damage("qi", 55);
        addn("neili", -60, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"sanwu-shou/" + action;
}
