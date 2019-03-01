#include <ansi.h>

inherit SKILL;

mapping *action = ({
([      "action": "$N單手一揚，一招「虐目」，手中$w抖得筆直，直點$n的雙眼",
        "force" : 110,
        "dodge" : 12,
        "parry" : 10,
        "damage": 35,
        "lvl"   : 0,
        "skill_name" : "虐目",
        "damage_type": "刺傷"
]),
([      "action": "$N力貫鞭梢，一招「傷肝」，手中$w舞出滿天鞭影，橫掃$n腰間",
        "force" : 140,
        "dodge" : 17,
        "parry" : 15,
        "damage": 50,
        "lvl"   : 20,
        "skill_name" : "傷肝",
        "damage_type": "劈傷"
]),
([      "action": "$N運氣于腕，一招「損心」，手中$w向一根銅棍般直擊$n胸部",
        "force" : 180,
        "dodge" : 21,
        "parry" : 19,
        "damage": 43,
        "lvl"   : 40,
        "skill_name" : "損心",
        "damage_type": "內傷"
]),
([      "action": "$N單臂一揮，一招「催膽」，手中$w直擊向$n腰肋",
        "force" : 215,
        "dodge" : 32,
        "parry" : 27,
        "damage": 58,
        "lvl"   : 60,
        "skill_name" : "催膽",
        "damage_type": "劈傷"
]),
([      "action": "$N高高躍起，一招「攝魄」，手中$w筆直向$n當頭罩下",
        "force" : 255,
        "dodge" : 42,
        "parry" : 37,
        "damage": 75,
        "lvl"   : 80,
        "skill_name" : "攝魄",
        "damage_type": "劈傷"
]),
([      "action": "$N身形一轉，一招「收魂」，手中$w如矯龍般騰空一卷，猛地向$n劈頭打下",
        "force" : 330,
        "dodge" : 87,
        "parry" : 69,
        "damage": 81,
        "lvl"   : 100,
        "skill_name" : "收魂",
        "damage_type": "劈傷"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練習纏魂索。\n");

        if( query("max_neili", me)<400 )
                return notify_fail("你的內力不足，沒有辦法練習纏魂索。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < 60)
                return notify_fail("你的基本鞭法火候太淺。\n");

        if ((int)me->query_skill("whip", 1) < (int)me->query_skill("chanhun-suo", 1))
                return notify_fail("你的基本鞭法水平有限，無法領會更高深的纏魂索。\n");

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
        level   = (int) me->query_skill("chanhun-suo",1);
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
                return notify_fail("你的體力不夠練纏魂索。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練纏魂索。\n");

        me->receive_damage("qi", 50);
        addn("neili", -50, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"chanhun-suo/" + action;
}
