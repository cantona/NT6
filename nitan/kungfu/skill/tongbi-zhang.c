inherit SKILL;

mapping *action = ({
([      "action" : "$N使出一招「孤雁出羣」，雙掌合十，直直撞向$n的前胸",
        "force"  : 120,
        "attack" : 25,
        "dodge"  : 10,
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "孤雁出羣",
]),
([      "action" : "$N使出一招「 穿掌閃劈」，飛身躍起，雙手猛拍，打向$n",
        "force"  : 170,
        "attack" : 30,
        "dodge"  : 15,
        "lvl"    : 25,
        "damage_type" : "瘀傷",
        "skill_name"  : "穿掌閃劈",
]),
([      "action" : "只見$N使出一招「跨虎蹬山」，身形一展，運力於掌直取$n",
        "force"  : 220,
        "attack" : 35,
        "dodge"  : 5,
        "lvl"    : 50,
        "damage_type" : "瘀傷",
        "skill_name"  : "跨虎蹬山",
]),
([      "action" : "$N使出一招「穿心透骨」，怒吼一聲，一掌當頭拍向$n的$l",
        "force"  : 250,
        "attack" : 40,
        "dodge"  : 25,
        "lvl"    : 80,
        "damage_type" : "瘀傷",
        "skill_name"  : "穿心透骨",
]),
([      "action" : "$N使出一招「金陽破嶺」，猛衝向前，掌如游龍般攻向$n",
        "force"  : 280,
        "attack" : 45,
        "dodge"  : 15,
        "lvl"    : 100,
        "damage_type" : "瘀傷",
        "skill_name"  : "金陽破嶺",
]),
([      "action" : "$N使出一招「六合劈」，伏身疾進，雙掌自下掃向$n的$l",
        "force"  : 320,
        "attack" : 50,
        "dodge"  : 15,
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "六合劈",
]),
([      "action" : "$N使出一招「齊天神威」，飛身橫躍，雙掌前後擊出，拍向$n",
        "force"  : 340,
        "attack" : 55,
        "dodge"  : 20,
        "lvl"    : 140,
        "damage_type" : "瘀傷",
        "skill_name"  : "齊天神威",
]),
([      "action" : "$N施展「大輪迴」勁氣瀰漫，天空中出現無數掌影打向$n的$l",
        "force"  : 360,
        "attack" : 65,
        "dodge"  : 25,
        "lvl"    : 160,
        "damage_type" : "瘀傷",
        "skill_name"  : "大輪迴",
]),
});

int valid_enable(string usage)
{
        return usage == "strike" || usage == "parry";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練通臂六合掌必須空手。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 20)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("tongbi-zhang",1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的通臂六合掌。\n");

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
        level = (int) me->query_skill("tongbi-zhang", 1);

        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練通臂六合掌必須空手。\n");

        if( query("qi", me)<50 )
                return notify_fail("你的體力不夠，練不了通臂六合掌。\n");

        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠，練不了通臂六合掌。\n");

        me->receive_damage("qi", 35);
        addn("neili", -30, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tongbi-zhang/" + action;
}