inherit SKILL;

mapping *action = ({
([      "action":"$N吐氣開聲一招「泣」字訣，$w如靈蛇吞吐，向$n白海穴戳去",
        "force" : 130,
        "attack": 30,
        "dodge" : -10,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 0,
        "skill_name" : "泣字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N向前跨上一步，混身充滿戰意，使出「驚」字訣，疾點$n的地倉穴",
        "force" : 170,
        "attack": 40,
        "dodge" : 5,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 30,
        "skill_name" : "驚字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中的$w自左而右地一晃，使出「傷」字訣橫打$n的章門穴",
        "force" : 190,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 40,
        "lvl"   : 60,
        "skill_name" : "傷字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「卷」字訣，卷起漫天筆影，$w向$n電射而去",
        "force" : 240,
        "attack": 60,
        "dodge" : 10,
        "parry" : 45,
        "damage": 50,
        "lvl"   : 90,
        "skill_name" : "卷字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N凝氣守中，$w逼出尺許雪亮筆鋒，陡然揮出「離」字訣攻向$n",
        "force" : 260,
        "attack": 65,
        "dodge" : 5,
        "parry" : 50,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "離字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N使出一招「悲」字訣挺筆中宮直進，筆尖顫動，中途忽然轉而向上",
        "force" : 280,
        "attack": 70,
        "dodge" : 5,
        "parry" : 52,
        "damage": 75,
        "lvl"   : 150,
        "skill_name" : "悲字訣",
        "damage_type" : "刺傷"
]),
([      "action":"$N側身斜刺一筆，一招「蒼」字訣卷帶著呼呼筆風，將$n包圍緊裹",
        "force" : 310,
        "attack": 75,
        "dodge" : 5,
        "parry" : 64,
        "damage": 90,
        "lvl"   : 180,
        "skill_name" : "蒼字訣",
        "damage_type" : "刺傷"
]),
});


int valid_enable(string usage)
{
        return usage == "dagger" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 100)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("dagger", 1) < 30)
                return notify_fail("你的基本短兵火候太淺。\n");

        if ((int)me->query_skill("dagger", 1) < (int)me->query_skill("canghong-bifa", 1))
                return notify_fail("你的基本短兵水平有限，無法領會更高深的蒼虹筆法。\n");

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

        level = (int) me->query_skill("canghong-bifa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習蒼虹筆法。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練蒼虹筆法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練蒼虹筆法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"canghong-bifa/" + action;
}