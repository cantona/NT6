inherit SKILL;

string *dodge_msg = ({
        "$n身子輕輕一擺，一招「乳燕歸巢」，躲開了$N的攻擊。\n",
        "$n一招「蜻蜓點水」，身形微微一抖，向後跳開了數尺。\n",
        "可是$n一招「平步青雲」，雙足點地，飄然而起，使$N攻勢落空。\n",
        "$n一招「雪燕南歸」，身子向後橫移開來，躲開了攻擊。\n",
        "$n使出一招「燕落長空」，整個身體一個盤旋，繞開了$N攻擊。\n",
});

mapping *action = ({
([      "action":"$N一招「乳燕歸巢」，手中$w如蜻蜓點水般，招招向$n的$l點去",
        "force" : 120,
        "attack": 25,
        "dodge" : 75,
        "parry" : 82,
        "damage": 10,
        "lvl"   : 0,
        "skill_name" : "乳燕歸巢",
        "damage_type":"挫傷"
]),
([      "action":"$N把$w平提胸口，一擰身，一招「蜻蜓點水」，$w猛地撩向$n的$l",
        "force" : 150,
        "attack": 37,
        "dodge" : 73,
        "parry" : 81,
        "damage": 15,
        "lvl"   : 40,
        "skill_name" : "蜻蜓點水",
        "damage_type":"挫傷"
]),
([      "action":"$N一招「雪燕南歸」，全身滴溜溜地在地上打個大轉，$w向$n的$l間戳去",
        "force" : 180,
        "attack": 42,
        "dodge" : 65,
        "parry" : 87,
        "damage": 20,
        "lvl"   : 80,
        "skill_name" : "雪燕南歸",
        "damage_type":"挫傷"
]),
([      "action":"$N伏地一個滾翻，一招「平步青雲」，$w挾呼呼風聲迅猛掃向$n的足脛",
        "force" : 210,
        "attack": 43,
        "dodge" : 68,
        "parry" : 85,
        "damage": 25,
        "lvl"   : 100,
        "skill_name" : "平步青雲",
        "damage_type":"挫傷"
]),
([      "action":"$N一招「燕落長空」，身棍合一，棍端逼成一條直線，流星般向頂向$n的$l",
        "force" : 240,
        "attack": 49,
        "dodge" : 73,
        "parry" : 91,
        "damage": 30,
        "lvl"   : 120,
        "skill_name" : "燕落長空",
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry" || usage == "dodge"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<250 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("caiyan-gong", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的採燕功。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("caiyan-gong", 1))
                return notify_fail("你的基本棍法水平有限，無法領會更高深的採燕功。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("caiyan-gong", 1);
        for(i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練採燕功。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的體力不夠練採燕功。\n");

        me->receive_damage("qi", 62);
        addn("neili", -61, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"caiyan-gong/" + action;
}