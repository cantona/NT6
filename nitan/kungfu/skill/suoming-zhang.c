inherit SKILL;

mapping *action = ({
([      "action": "$N微一躬身，使出「修羅索命」，$w攜帶着刺耳風聲，擦地掃向$n的腳踝",
        "force" : 100,
        "attack": 10,
        "dodge" : -5,
        "parry" : 9,
        "damage": 15,
        "damage_type":"挫傷"
]),
([      "action": "$N右手托住杖端，一招「招魂悼魄」居中一擊，令其憑慣性倒向$n的肩頭",
        "force" : 110,
        "attack": 15,
        "dodge" : -10,
        "parry" : 15,
        "damage": 15,
        "damage_type":"挫傷"
]),
([      "action": "$N一聲狂喝，施一招「判官翻簿」，舉起$w地滿地亂敲，鋪天蓋地襲向$n",
        "force" : 120,
        "attack": 20,
        "dodge" : -5,
        "parry" : 19,
        "damage": 20,
        "damage_type":"挫傷"
]),
([      "action": "$N飛身躍起，一招「弔客臨門」，身下$w往橫裏直打而出，揮向$n的襠部",
        "force" : 280,
        "attack": 50,
        "dodge" : -5,
        "parry" : 55,
        "damage": 50,
        "lvl"   : 130,
        "damage_type":"挫傷"
]),
([      "action": "$N高舉$w施展「無常抖索」，身形如鬼魅般飄出，對準$n的天靈蓋一杖打下",
        "force" : 330,
        "attack": 61,
        "dodge" : -5,
        "parry" : 62,
        "damage": 60,
        "damage_type":"挫傷"
]),
([      "action": "$N雙眼發紅，一招「百鬼慟哭」，將手中$w舞成千百根相似，擊向$n全身各處要害",
        "force" : 350,
        "attack": 65,
        "dodge" : -5,
        "parry" : 67,
        "damage": 60,
        "damage_type":"挫傷"
]),
});

int valid_enable(string usage) { return usage == "staff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("staff", 1) < (int)(int)me->query_skill("suoming-zhang", 1))
                return notify_fail("你的基本杖法水平有限，無法領會更高深的索命杖法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action)-1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("suoming-zhang",1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "staff" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<80 )
                return notify_fail("你的體力不夠練索命杖法。\n");

        if( query("neili", me)<75 )
                return notify_fail("你的內力不夠練索命杖法。\n");

        me->receive_damage("qi", 70);
        addn("neili", -69, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"suoming-zhang/" + action;
}