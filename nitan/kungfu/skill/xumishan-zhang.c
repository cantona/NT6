// xumishan-zhang.c 須彌山掌

inherit SHAOLIN_SKILL;

mapping *action = ({
([        "action": "$N前腿踢出，後腿腳尖點地，一式「五丁開山」，雙掌直擊$n的面門",
          "force" : 150,
          "attack": 15,
          "dodge" : 5,
          "parry" : 20,
          "lvl"   : 0,
          "damage_type" : "瘀傷",
          "skill_name" : "五丁開山"
]),
([        "action": "$N左掌劃一半圓，一式「壁立千刃」，右掌斜穿而出，疾拍$n的胸前大穴",
          "force" : 180,
          "attack": 20,
          "dodge" : 5,
          "parry" : 20,
          "damage": 10,
          "lvl"   : 30,
          "damage_type" : "瘀傷",
          "skill_name" : "壁立千刃"
]),
([        "action": "$N使一式「雲斷秦嶺」，右掌上引，左掌由後而上一個甩劈，斬向$n的$l",
          "force" : 200,
          "attack": 30,
          "dodge" : 5,
          "parry" : 10,
          "damage": 20,
          "lvl"   : 50,
          "damage_type" : "劈傷",
          "skill_name" : "雲斷秦嶺"
]),
([        "action": "$N左掌護胸，右掌凝勁後發，一式「日墜蒼山」，緩緩推向$n的$l",
          "force" : 240,
          "attack": 80,
          "dodge" : -5,
          "parry" : 10,
          "damage": 30,
          "lvl"   : 80,
          "damage_type" : "瘀傷",
          "skill_name" : "日墜蒼山"
]),
([        "action": "$N使一式「山高雲淡」，身行一縱，雙掌一前一後，猛地擊向$n的頭頂百匯大穴",
          "force" : 250,
          "attack": 50,
          "dodge" : 20,
          "parry" : 60,
          "damage": 35,
          "lvl"   : 100,
          "damage_type" : "瘀傷",
          "skill_name" : "山高雲淡"
]),
([        "action": "$N雙掌合十，深吸一口氣，一式「濛濛羣山」，雙掌驟然化出一片掌影，擊向$n的前胸",
          "force" : 280,
          "attack": 50,
          "dodge" : 25,
          "parry" : 30,
          "damage": 40,
          "lvl"   : 125,
          "damage_type" : "瘀傷",
          "skill_name" : "濛濛羣山"
]),
([        "action": "$N向上高高躍起，一式「高山流水」，居高臨下，掌力籠罩$n的全身",
          "force" : 300,
          "attack": 60,
          "dodge" : 30,
          "parry" : 35,
          "damage": 45,
          "lvl"   : 150,
          "damage_type" : "瘀傷",
          "skill_name" : "高山流水"
]),
([        "action": "$N使一式「峯迴路轉」，勁氣瀰漫，雙掌如輪，一掌強過一掌的向$n劈去",
          "force" : 350,
          "attack": 70,
          "dodge" : 30,
          "parry" : 55,
          "damage": 50,
          "lvl"   : 175,
          "damage_type" : "劈傷",
          "skill_name" : "峯迴路轉"
]),
([        "action": "$N兩掌上下護胸，一式「山窮水盡」，驟然化為滿天掌雨，攻向$n",
          "force" : 400,
          "attack": 80,
          "dodge" : 30,
          "parry" : 60,
          "damage": 55,
          "lvl"   : 200,
          "damage_type" : "瘀傷",
          "skill_name" : "山窮水盡"
]),
([        "action": "$N一式「排山倒海」，雙掌一圈，全身內力如巨浪般洶湧而出，$n頓覺避無可避",
          "force" : 450,
          "attack": 100,
          "dodge" : 50,
          "parry" : 80,
          "damage": 60,
          "lvl"   : 250,
          "damage_type" : "內傷",
          "skill_name" : "排山倒海"
])
});

int valid_enable(string usage) { return usage == "strike" ||  usage == "parry"; }

int valid_combine(string combo) { return combo == "jingang-zhi"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練須彌山掌必須空手。\n");

        if ((int)me->query_skill("force", 1) < 300)
                return notify_fail("你的基本內功火候不夠，無法學須彌山掌。\n");

        if( query("max_neili", me)<2000 )
                return notify_fail("你的內力太弱，無法練須彌山掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xumishan-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的須彌山掌。\n");

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

        level = (int)me->query_skill("xumishan-zhang", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<90 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<90 )
                return notify_fail("你的內力不夠練須彌山掌。\n");

        me->receive_damage("qi", 80);
        addn("neili", -75, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"xumishan-zhang/" + action;
}
