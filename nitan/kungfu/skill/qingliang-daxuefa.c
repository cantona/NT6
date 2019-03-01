inherit SKILL;

mapping *action = ({
([      "action":"$N左手施展出一招「清心普善」，手中的$w疾點向$n的期門穴",
        "force" : 90,
        "attack": 15,
        "dodge" : -10,
        "parry" : 20,
        "damage": 25,
        "lvl"   : 0,
        "skill_name" : "清心普善",
        "damage_type" : "刺傷"
]),
([      "action":"$N吐氣開聲一招「寒梅映雪」，$w如靈蛇吞吐，向$n白海穴戳去",
        "force" : 130,
        "attack": 30,
        "dodge" : -10,
        "parry" : 30,
        "damage": 30,
        "lvl"   : 40,
        "skill_name" : "寒梅映雪",
        "damage_type" : "刺傷"
]),
([      "action":"$N向前跨上一步，混身充滿戰意，手中$w使出「追風逐電」，疾點$n的地倉穴",
        "force" : 170,
        "attack": 40,
        "dodge" : 5,
        "parry" : 32,
        "damage": 35,
        "lvl"   : 60,
        "skill_name" : "追風逐電",
        "damage_type" : "刺傷"
]),
([      "action":"$N手中的$w自左而右地一晃，使出「飛黃騰達」帶著呼呼風聲橫打$n的章門穴",
        "force" : 190,
        "attack": 50,
        "dodge" : 5,
        "parry" : 35,
        "damage": 40,
        "lvl"   : 80,
        "skill_name" : "飛黃騰達",
        "damage_type" : "刺傷"
]),
([      "action":"$N飛身躍起，一式「快馬加鞭」，卷起漫天筆影，$w向$n電射而去",
        "force" : 240,
        "attack": 60,
        "dodge" : 10,
        "parry" : 45,
        "damage": 50,
        "lvl"   : 100,
        "skill_name" : "快馬加鞭",
        "damage_type" : "刺傷"
]),
([      "action":"$N凝氣守中，$w逼出尺許雪亮筆鋒，揮出「靈台觀景」，一筆快似一筆地攻向$n",
        "force" : 260,
        "attack": 65,
        "dodge" : 5,
        "parry" : 50,
        "damage": 60,
        "lvl"   : 120,
        "skill_name" : "靈台觀景",
        "damage_type" : "刺傷"
]),
([      "action":"$N使出一招「群山疊影」挺筆中宮直進，筆尖顫動，中途忽然轉而向上變幻無方",
        "force" : 280,
        "attack": 70,
        "dodge" : 5,
        "parry" : 52,
        "damage": 75,
        "lvl"   : 140,
        "skill_name" : "群山疊影",
        "damage_type" : "刺傷"
]),
([      "action":"$N側身斜刺一筆，一招「風雷卷破」卷帶著呼呼筆風，將$n包圍緊裹",
        "force" : 310,
        "attack": 75,
        "dodge" : 5,
        "parry" : 64,
        "damage": 90,
        "lvl"   : 150,
        "skill_name" : "風雷卷破",
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

        if ((int)me->query_skill("dagger", 1) < 10)
                return notify_fail("你的基本短兵火候太淺。\n");

        if ((int)me->query_skill("dagger", 1) < (int)me->query_skill("qingliang-daxuefa", 1))
                return notify_fail("你的基本短兵水平有限，無法領會更高深的清涼打穴法。\n");

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

        level = (int) me->query_skill("qingliang-daxuefa", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "dagger" )
                return notify_fail("你所持的武器無法練習清涼打穴法。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練清涼打穴法。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練清涼打穴法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -62, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"qingliang-daxuefa/" + action;
}