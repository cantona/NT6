inherit SKILL;

mapping *action = ({
([      "action": "$N左手$w輕送，施出觀日劍法起手「日出東海」向前刺出，罩向$n的$l",
        "force" : 153,
        "attack": 39,
        "dodge" : 65,
        "parry" : 67,
        "damage": 41,
        "lvl"   : 0,
        "skill_name" : "日出東海",
        "damage_type": "割傷"
]),
([      "action": "$N劍尖倏地翻上，手中$w斜刺$n$l，正是觀日劍法中「寰陽萬鈞」一招",
        "force" : 167,
        "attack": 43,
        "dodge" : 68,
        "parry" : 69,
        "damage": 43,
        "lvl"   : 20,
        "skill_name" : "寰陽萬鈞",
        "damage_type": "刺傷"
]),
([      "action": "$N一招「丹陽破虛」，劍尖一抖，$w中宮直進，劍到中途卻變轉劍鋒斜削$n",
        "force" : 173,
        "attack": 48,
        "dodge" : 71,
        "parry" : 79,
        "damage": 45,
        "lvl"   : 40,
        "skill_name" : "丹陽破虛",
        "damage_type": "割傷"
]),
([      "action": "$N手中$w微微顫動，一招「赤日炎炎」，忽然刺出，頓時一道劍光射向$n而去",
        "force" : 195,
        "attack": 51,
        "dodge" : 75,
        "parry" : 82,
        "damage": 49,
        "lvl"   : 60,
        "skill_name" : "赤日炎炎",
        "damage_type": "刺傷"
]),
([      "action": "$N左手緊握劍指，右手$w紫光暴漲，一式「烽火絕塵」，劍指劍鋒同時刺向$n",
        "force" : 218,
        "attack": 57,
        "dodge" : 79,
        "parry" : 83,
        "damage": 53,
        "lvl"   : 80,
        "skill_name" : "烽火絕塵",
        "damage_type": "刺傷"
]),
([      "action": "$N一式「洪峯萬里」，$w劃了一個半月弧形，灑出點點火光，直飛$n而去",
        "force" : 224,
        "attack": 62,
        "dodge" : 85,
        "parry" : 89,
        "damage": 57,
        "lvl"   : 100,
        "skill_name" : "洪峯萬里",
        "damage_type": "刺傷"
]),
([      "action": "$N身形一轉，一招「煉獄洪爐」，手中$w對着$n猛攻數劍，招式精奇之極",
        "force" : 238,
        "attack": 69,
        "dodge" : 87,
        "parry" : 91,
        "damage": 61,
        "lvl"   : 130,
        "skill_name" : "煉獄洪爐",
        "damage_type": "割傷"
]),
([      "action": "$N手中的$w連削帶刺，一招「日照九天」，夾帶着一陣熾熱掠過$n全身",
        "force" : 257,
        "attack": 75,
        "dodge" : 95,
        "parry" : 99,
        "damage": 68,
        "lvl"   : 160,
        "skill_name" : "日照九天",
        "damage_type": "刺傷"
]),
([      "action": "$N一招「殘陽血照」，使得若有若無，朦朦朧朧，$w斜斜劃出，直取$n$l",
        "force" : 270,
        "attack": 81,
        "dodge" : 107,
        "parry" : 109,
        "damage": 73,
        "lvl"   : 190,
        "skill_name" : "殘陽血照",
        "damage_type": "刺傷"
]),
([      "action": "$N長嘯一聲，一招「天火燎原」$w豪光綻放，劍尖頓時迸出數道劍氣射向$n",
        "force" : 285,
        "attack": 85,
        "dodge" : 115,
        "parry" : 115,
        "damage": 77,
        "lvl"   : 220,
        "skill_name" : "天火燎原",
        "damage_type": "刺傷"
])
});

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me)
{
        if ((int)me->query_skill("force") < 150)
                return notify_fail("你的內功火候不夠，無法學習觀日劍法。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力修為不足，無法學習觀日劍法。\n");

        if ((int)me->query_skill("sword", 1) < 100)
                return notify_fail("你的基本劍法太淺，無法學習觀日劍法。\n");

        if (me->query_skill("sword", 1) < me->query_skill("guanri-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的觀日劍法。\n");

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
        level = (int) me->query_skill("guanri-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
            || query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練觀日劍法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練觀日劍法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -70, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"guanri-jian/" + action;
}