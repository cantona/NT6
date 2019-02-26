#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N單手一揚，一招「天蠍爪」，手中$w抖得筆直，直點$n的雙眼",
        "force" : 100,
        "dodge" : 12,
        "parry" : 10,
        "damage": 5,
        "lvl"   : 0,
        "damage_type": "刺傷"
]),
([      "action": "$N力貫鞭梢，一招「蠍尾鈎」，手中$w舞出滿天鞭影，橫掃$n腰間",
        "force" : 130,
        "dodge" : 17,
        "parry" : 15,
        "damage": 10,
        "lvl"   : 20,
        "damage_type": "劈傷"
]),
([      "action": "$N運氣於腕，一招「毒蠍蝕月」，手中$w向一根銅棍般直擊$n胸部",
        "force" : 150,
        "dodge" : 21,
        "parry" : 19,
        "damage": 13,
        "lvl"   : 40,
        "damage_type": "內傷"
]),
([      "action": "$N單臂一揮，一招「蛇遊蠍行」，手中$w直擊向$n腰肋",
        "force" : 175,
        "dodge" : 32,
        "parry" : 27,
        "damage": 18,
        "lvl"   : 60,
        "damage_type": "劈傷"
]),
([      "action": "$N高高躍起，一招「天蠍藏針」，手中$w筆直向$n當頭刺下",
        "force" : 225,
        "dodge" : 42,
        "parry" : 37,
        "damage": 35,
        "lvl"   : 80,
        "damage_type": "刺傷"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練習蠍尾鞭。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不足，沒有辦法練習蠍尾鞭。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < 20)
                return notify_fail("你的基本鞭法火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("xiewei-bian", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的蠍尾鞭。\n");

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
        level   = (int) me->query_skill("xiewei-bian", 1);
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
                return notify_fail("你的體力不夠練蠍尾鞭。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練蠍尾鞭。\n");

        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xiewei-bian/" + action;
}
