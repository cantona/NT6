#include <ansi.h>
inherit SKILL;
 
mapping *action = ({
([      "action": "$N身形稍退，手中$w迎風一抖，朝著$n劈頭蓋臉地砸將下",
        "dodge" : 31,
        "attack": 31,
        "force" : 289,
        "damage": 34,
        "parry" : 35,
        "lvl" : 0,
        "damage_type": "砸傷"
]),
([      "action": "$N仰天長笑，看也不看，隨手一棒向$n當頭砸下",
        "dodge" : 33,
        "attack": 37,
        "force" : 316,
        "damage": 41,
        "parry" : 42,
        "lvl" : 25,
        "damage_type": "砸傷"
]),
([      "action": "$N一個虎跳，越過$n頭頂，手中$w掄個大圓，砸向$n$l",
        "dodge" : 38,
        "attack": 38,
        "force" : 318,
        "damage": 73,
        "parry" : 35,
        "lvl" : 50,
        "damage_type": "砸傷"
]),
([      "action": "$N一聲巨喝，$n一愣之間，$N手中$w已呼嘯而至，掃向$n的$l",
        "dodge" : 31,
        "attack": 48,
        "force" : 331,
        "damage": 91,
        "parry" : 33,
        "lvl" : 75,
        "damage_type": "砸傷"
]),
([      "action": "$N身形稍退，手中$w迎風一抖，朝著$n劈頭蓋臉地砸將下",
        "dodge" : 49,
        "attack": 63,
        "force" : 391,
        "damage": 103,
        "parry" : 31,
        "lvl" : 100,
        "damage_type": "砸傷"
]),
([      "action": "$N腳步蹌踉，左一棒，右一棒，打得$n手忙腳亂，招架不迭",
        "dodge" : 51,
        "attack": 74,
        "force" : 481,
        "damage": 167,
        "parry" : 28,
        "lvl" : 130,
        "damage_type": "砸傷"
]),
([      "action": "$N連翻幾個筋鬥，手中$w轉得如風車一般，一連三棒直擊$n頂門",
        "dodge" : 31,
        "attack": 83,
        "force" : 503,
        "damage": 184,
        "parry" : 35,
        "lvl" : 160,
        "damage_type": "砸傷"
]),
([      "action": "$N手中$w化為萬道霞光，乘$n目眩之時，$w已到了$n的$l",
        "dodge" : 23,
        "attack": 98,
        "force" : 548,
        "damage": 193,
        "parry" : 51,
        "lvl" : 200,
        "damage_type": "砸傷"
]),
});


int valid_enable(string usage)
{
        return usage == "parry" || usage == "club";
}

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你必須先找一根棍子才能練金猿棍法。\n");

        if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不足，難以修煉金猿棍法。\n");

        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候太淺，難以修煉金猿棍法。\n");

        if ((int)me->query_skill("club", 1) < 100)
                return notify_fail("你的基本棍法火候太淺，難以修煉金猿棍法。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("jinyuan-gun", 1))
                return notify_fail("你的基本棍法水平不夠，無法領會更高深的金猿棍法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("jinyuan-gun",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練金猿棍法。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練金猿棍法。\n");

        me->receive_damage("qi", 75);
        addn("neili", -85, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jinyuan-gun/" + action;
}