inherit SKILL;

mapping *action = ({
([        "action":"$N一式「順水推舟」，$N手中$w指向自己左胸口，劍柄斜斜向右外，緩緩劃向$n的$l",
        "force" : 85,
        "dodge" : 35,
        "parry" : 35,
        "attack": 31,
        "damage": 23,
        "lvl"   : 0,
        "skill_name" : "順水推舟",
        "damage_type":"刺傷"
]),
([        "action":"$N身形微側，左手後擺，右手$w一招「橫掃千軍」，直向$n的腰間揮去",
        "force" : 109,
        "dodge" : 41,
        "parry" : 43,
        "attack": 33,
        "damage": 24,
        "lvl"   : 20,
        "skill_name" : "橫掃千軍",
        "damage_type":"刺傷"
]),
([        "action":"$N縱身近前，$w鬥然彎彎彈出，劍光爆長，一招「峭壁斷雲」，猛地刺向$n的胸口",
        "force" : 121,
        "dodge" : 43,
        "parry" : 45,
        "attack": 35,
        "damage": 27,
        "lvl"   : 40,
        "skill_name" : "峭壁斷雲",
        "damage_type":"刺傷"
]),
([        "action":"$N左手捏個劍決，平推而出，決指上仰，右手劍朝天不動，一招「仙人指路」，刺向$n",
        "force" : 135,
        "dodge" : 48,
        "parry" : 47,
        "attack": 37,
        "damage": 31,
        "lvl"   : 60,
        "skill_name" : "仙人指路",
        "damage_type":"刺傷"
]),
([        "action":"$N劍招忽變，使出一招「雨打飛花」，全走斜勢，但七八招斜勢中偶爾又挾著一招正勢，教人極難捉摸",
        "force" : 143,
        "dodge" : 57,
        "parry" : 59,
        "attack": 41,
        "damage": 32,
        "lvl"   : 80,
        "skill_name" : "雨打飛花",
        "damage_type":"刺傷"
]),
([        "action":"$N手中$w劍刃豎起，鋒口向下，一招「大漠平沙」，劍走刀勢，劈向$n的$l",
        "force" : 153,
        "dodge" : 63,
        "parry" : 68,
        "attack": 43,
        "damage": 34,
        "lvl"   : 100,
        "skill_name" : "大漠平沙",
        "damage_type":"劈傷"
]),
([        "action":"$N一招「木葉蕭蕭」，$N橫提$w，劍尖斜指向天，由上而下，劈向$n的$l",
        "force" : 167,
        "dodge" : 69,
        "parry" : 71,
        "attack": 45,
        "damage": 36,
        "lvl"   : 120,
        "skill_name" : "木葉蕭蕭",
        "damage_type":"劈傷"
]),
([        "action":"$N搶前一步，$w微微抖動，劍光點點，一招「江河不竭」，終而復始，綿綿不絕刺向$n",
        "force" : 185,
        "dodge" : 73,
        "parry" : 78,
        "attack": 48,
        "damage": 37,
        "lvl"   : 140,
        "skill_name" : "江河不竭",
        "damage_type":"刺傷"
]),
([        "action":"$N左手劍鞘一舉，快逾電光石光，一招「高塔掛雲」，用劍鞘套住$n手中兵器，$w直指$n的嚥喉",
        "force" : 205,
        "dodge" : 78,
        "parry" : 85,
        "attack": 49,
        "damage": 38,
        "lvl"   : 160,
        "skill_name" : "高塔掛雲",
        "damage_type":"刺傷"
]),
([        "action":"$N翻身回劍，劍訣斜引，一招「百丈飛瀑」，劍鋒從半空中直瀉下來，罩住$n上方",
        "force" : 243,
        "dodge" : 82,
        "parry" : 91,
        "attack": 51,
        "damage": 39,
        "lvl"   : 180,
        "skill_name" : "百丈飛瀑",
        "damage_type":"刺傷"
]),
([        "action":"$N一式「雪擁藍橋」，$N手中劍花團團，一條白練疾風般向卷向$n",
        "force" : 271,
        "dodge" : 87,
        "parry" : 95,
        "attack": 53,
        "damage": 41,
        "lvl"   : 200,
        "skill_name" : "雪擁藍橋",
        "damage_type":"刺傷"
]),
([        "action":"$N騰空而起，突然使出一招「悄然無聲」，悄無聲息地疾向$n的背部刺去",
        "force" : 285,
        "dodge" : 95,
        "parry" : 107,
        "attack": 57,
        "damage": 43,
        "lvl"   : 220,
        "skill_name" : "悄然無聲",
        "damage_type":"刺傷"
]),
});

int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force", 1) < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword") < 50)
                return notify_fail("你的基本劍法火候太淺，無法修煉正兩儀劍法。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("zhengliangyi-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的正兩儀劍法。\n");

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
        level = (int) me->query_skill("zhengliangyi-jian", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];

}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練正兩儀劍法。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練正兩儀劍法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -75, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"zhengliangyi-jian/" + action;
}