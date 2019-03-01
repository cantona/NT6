inherit SKILL;

mapping *action = ({
([      "action":"$N一招「驚空式」，手中$w疾點向$n的期門穴",
        "force" : 90,
        "attack": 15,
        "dodge" : -10,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "驚空式",
        "damage_type" : "刺傷"
]),
([      "action":"$N吐氣開聲一招「皓月式」，$w如靈蛇吞吐，向$n白海穴戳去",
        "force" : 110,
        "attack": 30,
        "dodge" : 10,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 40,
        "skill_name" : "皓月式",
        "damage_type" : "刺傷"
]),
([      "action":"$N向前跨上一步，手中$w使出「穿雲式」，疾點$n的地倉穴",
        "force" : 130,
        "attack": 40,
        "dodge" : 5,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 60,
        "skill_name" : "穿雲式",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中的$w自左而右地一晃，使出「飛雪式」帶著呼呼風聲橫打$n的章門穴",
        "force" : 150,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 40,
        "lvl"   : 80,
        "skill_name" : "飛雪式",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「金光式」，卷起漫天筆影，$w向$n電射而去",
        "force" : 170,
        "attack": 60,
        "dodge" : 10,
        "parry" : 45,
        "damage": 50,
        "lvl"   : 100,
        "skill_name" : "金光式",
        "damage_type" : "刺傷"
]),
([      "action":"$N凝氣守中，$w逼出尺許雪亮筆鋒，揮出「天靈式」，一筆快似一筆地攻向$n",
        "force" : 180,
        "attack": 65,
        "dodge" : 5,
        "parry" : 50,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "天靈式",
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage) { return (usage == "dagger") || (usage == "parry"); }

int valid_learn(object me)
{
        object ob;

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為不夠。\n");

        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "dagger" )
                return notify_fail("你必須先找一把相應的武器才能學習驚月筆法。\n");

        if ((int)me->query_skill("dagger", 1) < (int)me->query_skill("jingyue-bifa", 1))
                return notify_fail("你的基本短兵水平有限，無法領會更高深的驚月筆法。\n");

    return 1;
}

string query_skill_name(int level)
{
        int i;

        for(i = sizeof(action) - 1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int) me->query_skill("jingyue-bifa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習驚月筆法。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠練驚月筆法。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練驚月筆法。\n");

        me->receive_damage("qi", 45);
        addn("neili", -42, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jingyue-bifa/" + action;
}