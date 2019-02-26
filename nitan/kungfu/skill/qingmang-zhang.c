inherit SKILL;

mapping *action = ({
([      "action": "$N前腿踢出，後腿腳尖點地，一式「橫空出世」，二掌直出，攻向$n"
                  "的上中下三路",
        "force" : 120,
        "attack": 17,
        "dodge" : 5,
        "parry" : 12,
        "damage": 5,
        "lvl"   : 0,
        "damage_type" : "瘀傷",
]),
([      "action": "$N左掌劃一半圓，一式「長虹貫日」，右掌斜穿而出，疾拍$n的胸前"
                  "大穴",
        "force" : 150,
        "attack": 25,
        "dodge" : 5,
        "parry" : 18,
        "damage": 10,
        "lvl"   : 10,
        "damage_type" : "瘀傷",
]),
([      "action": "$N使一式「雲斷秦嶺」，右掌上引，左掌由後而上一個甩劈，斬向$n"
                  "的$l",
        "force" : 170,
        "attack": 32,
        "dodge" : 6,
        "parry" : 22,
        "damage": 10,
        "lvl"   : 20,
        "damage_type" : "劈傷",
]),
([      "action": "$N左掌護胸，右拳凝勁後發，一式「鐵索攔江」，緩緩推向$n的$l",
        "force" : 190,
        "attack": 38,
        "dodge" : -5,
        "parry" : 32,
        "damage": 10,
        "lvl"   : 40,
        "damage_type" : "瘀傷",
]),
([      "action": "$N使一式「狂風捲地」，全身飛速旋轉，雙掌一前一後，猛地拍向$n"
                  "的胸口",
        "force" : 210,
        "attack": 51,
        "dodge" : 10,
        "parry" : 27,
        "damage": 15,
        "lvl"   : 70,
        "damage_type" : "瘀傷",
]),
([      "action": "$N合掌抱球，猛吸一口氣，一式「懷中抱月」，雙掌疾推向$n的肩頭",
        "force" : 250,
        "attack": 52,
        "dodge" : 5,
        "parry" : 38,
        "damage": 15,
        "lvl"   : 90,
        "damage_type" : "瘀傷",
]),
([      "action": "$N向上高高躍起，一式「高山流水」，居高臨下，掌力籠罩$n的全身",
        "force" : 280,
        "attack": 62,
        "dodge" : 20,
        "parry" : 56,
        "damage": 15,
        "lvl"   : 110,
        "damage_type" : "瘀傷",
]),
});

int valid_enable(string usage) { return usage=="strike" ||  usage=="parry"; }  

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練青莽掌必須空手。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功心法火候不夠，無法修煉青莽掌。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練青莽掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("qingmang-zhang", 1))
                return notify_fail("你的基本掌法火候有限，無法領會更高深的青莽掌。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i - 1]["lvl"])
                        return action[i - 1]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int)me->query_skill("qingmang-zhang", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練青莽掌。\n");

        me->receive_damage("qi", 30);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingmang-zhang/" + action;
}