//pili-daofa.c 霹靂刀法

inherit SKILL;

mapping *action = ({
([      "action" : "$N發出一聲厲吼，手中$w以一招「翻江攪海」，帶着呼呼風聲向$n的$l砍去",
        "force"  : 30,
        "attack" : 10,
        "dodge"  : 30,
        "parry"  : 20,
        "damage" : 20,
        "lvl"    : 0,
        "skill_name" : "翻江攪海",
        "damage_type" : "砍傷"
]),
([      "action":"$N舞動$w，使出「八方風雨」，幻出了無數$w向$n劈去。",
        "force" :45,
        "attack":22,
        "dodge" :40,
        "parry" :32,
        "damage":28,
        "lvl"   :20,
        "skill_name" :"八方風雨",
        "damage_type":"劈傷"
]),
([      "action":"$N大喝一聲，一招「旋風驟起」，揮動$w快速擊向$n$l。",
        "force" :60,
        "attack":34,
        "dodge" :53,
        "parry" :40,
        "damage":35,
        "lvl"   :50,
        "skill_name" :"旋風驟起",
        "damage_type":"割傷"
]),
([      "action":"$N俯身搶上，一記「攬月高塘」，$w直砍$n雙腿。",
        "force" :80,
        "attack":50,
        "dodge" :70,
        "parry" :55,
        "damage":50,
        "lvl"   :90,
        "skill_name" :"攬月高塘",
        "damage_type":"砍傷"
]),
([      "action":"$N一招「斜陽疏影」，身形一躍，斜衝向前，右手揮動$w向下直斬$n的$l。",
        "force" :100,
        "attack":65,
        "dodge" :82,
        "parry" :68,
        "damage":65,
        "lvl"   :110,
        "skill_name" :"斜陽疏影",
        "damage_type":"砍傷"
]),
([      "action":"只見$N弓步上前，雙手緊握$w，一招「鳳凰展翼」，飛速擊向$n的$l。",
        "force" :150,
        "attack":80,
        "dodge" :95,
        "parry" :80,
        "damage":80,
        "lvl"   :150,
        "skill_name" :"鳳凰展翼",
        "damage_type":"割傷"
]),
});

int valid_enable(string usage) { return usage == "blade" || usage == "parry"; }

int valid_learn(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你必須手裏拿着刀才能練刀法。\n");

        if ((int)me->query_skill("riyue-xinfa", 1) < 100)
                return notify_fail("你的內功心法火候太淺，不能學霹靂刀法。\n");

        if ((int)me->query_skill("blade", 1) < 80)
                return notify_fail("你的基本刀法火候不夠。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太低，無法學霹靂刀法。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("pili-daofa", 1))
                return notify_fail("你的刀法水平有限，無法領會更高深的霹靂刀法。\n");

        return 1;
}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level;
        level = (int) me->query_skill("pili-daofa",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<70 )
                return notify_fail("你的體力不夠練霹靂刀法。\n");

        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練霹靂刀法。\n");

        me->receive_damage("qi", 65);
        addn("neili", -68, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"pili-daofa/" + action;
}
