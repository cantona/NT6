inherit SKILL;

mapping *action = ({
([      "action": "$N手中$w斜指，一招「回身誅殺勢」，反身一頓，一刀向$n的$l撩去",
        "force" : 72,
        "dodge" : 10,
        "parry" : 25,
        "attack": 16,
        "damage": 15,
        "lvl"   : 0,
        "skill_name"  : "回身誅殺勢",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「臨圖現匕勢」，左右腿虛點，$w一提一收，平刃揮向$n的頸部",
        "force" : 90,
        "dodge" : 30,
        "parry" : 40,
        "attack": 24,
        "damage": 21,
        "lvl"   : 20,
        "skill_name"  : "臨圖現匕勢",
        "damage_type" : "割傷"
]),
([      "action": "$N展身虛步，提腰躍落，一招「下步劈山勢」，刀鋒一卷，攔腰斬向$n",
        "force" : 124,
        "dodge" : 35,
        "parry" : 45,
        "attack": 29,
        "damage": 35,
        "lvl"   : 40,
        "skill_name"  : "下步劈山勢",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「戮妖降魔勢」，$w大開大闔，自上而下劃出一個大弧，筆直劈向$n",
        "force" : 136,
        "dodge" : 45,
        "parry" : 45,
        "attack": 34,
        "damage": 52,
        "lvl"   : 60,
        "skill_name"  : "戮妖降魔勢",
        "damage_type" : "割傷"
]),
([      "action": "$N手中$w一沉，一招「破玉穿梭勢」，雙手持刃攔腰反切，砍向$n的胸口",
        "force" : 158,
        "dodge" : 50,
        "parry" : 55,
        "attack": 37,
        "damage": 65,
        "lvl"   : 80,
        "skill_name"  : "破玉穿梭勢",
        "damage_type" : "割傷"
]),
([      "action": "$N揮舞$w，使出一招「抱月藏刀勢」，上劈下撩，左擋右開，齊齊罩向$n",
        "force" : 169,
        "dodge" : 65,
        "parry" : 55,
        "attack": 46,
        "damage": 73,
        "lvl"   : 100,
        "skill_name"  : "抱月藏刀勢",
        "damage_type" : "割傷"
]),
([      "action": "$N一招「寒星凸起勢」，左腳躍步落地，$w順勢往前，挾風聲劈向$n的$l",
        "force" : 210,
        "dodge" : 75,
        "parry" : 85,
        "attack": 55,
        "damage": 85,
        "lvl"   : 130,
        "skill_name"  : "寒星凸起勢",
        "damage_type" : "割傷"
]),
([      "action": "$N盤身駐地，一招「翻天弒穹勢」，揮出一片流光般的刀影，向$n的全身湧去",
        "force" : 240,
        "dodge" : 90,
        "parry" : 90,
        "attack": 76,
        "damage": 104,
        "lvl"   : 160,
        "skill_name"  : "翻天弒穹勢",
        "damage_type" : "割傷"
]),
([      "action": "$N回首施出一招「十二轉破神勢」，$w頓時捲起無數閃耀的刀芒籠罩$n全身",
        "force" : 240,
        "dodge" : 90,
        "parry" : 90,
        "attack": 76,
        "damage": 104,
        "lvl"   : 200,
        "skill_name"  : "十二轉破神勢",
        "damage_type" : "割傷"
]),
});


int valid_enable(string usage)
{
        return usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力修為不夠。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < 50)
                return notify_fail("你的基本刀法火候太淺。\n");

        if ((int)me->query_skill("blade", 1) < (int)me->query_skill("shiying-lianhuan", 1))
                return notify_fail("你的基本刀法水平有限，無法領會更高深的弒鷹九連環。\n");

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
        level = (int) me->query_skill("shiying-lianhuan", 1);
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "blade" )
                return notify_fail("你使用的武器不對。\n");

        if( query("qi", me)<60 )
                return notify_fail("你的體力不夠練弒鷹九連環。\n");

        if( query("neili", me)<60 )
                return notify_fail("你的內力不夠練弒鷹九連環。\n");

        me->receive_damage("qi", 55);
        addn("neili", -53, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"shiying-lianhuan/" + action;
}