inherit SKILL;

mapping *action = ({
([      "action" : "$N一招「飛燕入林」，手中$w輕輕顫動，一劍自上而下紮向$n的$l",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 25,
        "lvl"    : 0,
        "skill_name" : "飛燕入林",
        "damage_type": "刺傷"
]),
([      "action" : "$N身形不動，一招「虛式分金」，手中$w向前下反刺，一劍指向$n的$l",
        "force"  : 120,
        "dodge"  : 20,
        "damage" : 20,
        "lvl"    : 10,
        "skill_name" : "虛式分金",
        "damage_type": "刺傷"
]),
([      "action" : "$N右手$w先向前刺，使出一式「鳳凰摯窩」，劍光如匹練般泄向$n的$l",
        "force"  : 140,
        "dodge"  : 15,
        "damage" : 25,
        "lvl"    : 20,
        "skill_name" : "鳳凰摯窩",
        "damage_type": "刺傷"
]),
([      "action" : "$N碎步急進，提劍沿劍身方向疾速上刺，一招「輕羅小扇」直取$n的$l",
        "force"  : 150,
        "dodge"  : 15,
        "damage" : 35,
        "lvl"    : 30,
        "skill_name" : "輕羅小扇",
        "damage_type": "刺傷"
]),
([      "action" : "$N平劍斜洗，臂圓劍直，一式「玉女穿梭」，$w連綿不絕刺向$n的$l",
        "force"  : 130,
        "dodge"  : 25,
        "damage" : 25,
        "lvl"    : 40,
        "skill_name" : "玉女穿梭",
        "damage_type": "刺傷"
]),
([      "action" : "$N屈腕抬臂，劍由前向後上方抽帶，一式「黑沼靈狐」直刺向$n的$l",
        "force"  : 120,
        "dodge"  : 25,
        "damage" : 25,
        "lvl"    : 50,
        "skill_name" : "黑沼靈狐",
        "damage_type": "刺傷"
]),
([      "action" : "$N抱劍當胸，正反攪動，右手$w一式「順水推舟」，刺向$n的$l",
        "force" : 110,
        "dodge" : 15,
        "lvl"   : 60,
        "skill_name" : "順水推舟",
        "damage_type": "刺傷"
]),
([      "action" : "$N側身退步，左手劍指劃轉，一記「伊人消魂」自下上撩指向$n的$l",
        "force"  : 150,
        "dodge"  : 35,
        "damage" : 40,
        "lvl"    : 70,
        "skill_name" : "伊人消魂",
        "damage_type": "刺傷"
]),
});


int valid_enable(string usage) { return usage == "sword" || usage == "parry"; }

int valid_learn(object me)
{
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("emei-jian", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的峨嵋劍法。\n");

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
        level = (int) me->query_skill("emei-jian", 1);
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

        if( query("qi", me)<40 )
                return notify_fail("你的體力不夠練峨嵋劍法。\n");

        if( query("neili", me)<10 )
                return notify_fail("你的內力不夠練峨嵋劍法。\n");

        me->receive_damage("qi", 25);
        addn("neili", -1, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"emei-jian/" + action;
}