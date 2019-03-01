inherit SHAOLIN_SKILL;



mapping *action = ({
([      "action" : "$N使出一招「蓮花手」，雙掌合十，直直撞向$n的前胸",
        "skill_name" : "蓮花手",
        "force" : 120,
        "attack": 70,
        "dodge" : 20,
        "lvl" : 0,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「觀音手」，飛身躍起，雙手如勾，抓向$n的$l",
        "skill_name" : "觀音手",
        "force" : 170,
        "attack": 80,
        "dodge" : 20,
        "lvl" : 25,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「佛母手」，運力于指，直取$n的$l",
        "skill_name" : "佛母手",
        "force" : 220,
        "attack": 60,
        "dodge" : 20,
        "lvl" : 50,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「紅閻婆羅手」，怒吼一聲，一掌當頭拍向$n的$l",
        "skill_name" : "紅閻婆羅手",
        "force" : 250,
        "attack": 80,
        "dodge" : 30,
        "lvl" : 80,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「慈悲手」，猛沖向前，掌如遊龍般攻向$n",
        "skill_name" : "慈悲手",
        "force" : 360,
        "attack": 80,
        "dodge" : 30,
        "lvl" : 100,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「大慈大悲手」，伏身疾進，雙掌自下掃向$n的$l",
        "skill_name" : "大慈大悲手",
        "force" : 550,
        "attack": 160,
        "dodge" : 70,
        "lvl" : 180,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「金剛手」，飛身橫躍，雙掌前後擊出，抓向$n的嚥"
                   "喉",
        "skill_name" : "金剛手",
        "force" : 500,
        "attack": 120,
        "dodge" : 80,
        "lvl" : 140,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「六臂智慧手」，頓時勁氣彌漫，天空中出現無數掌影打"
                   "向$n的$l",
        "skill_name" : "六臂智慧手",
        "force" : 500,
        "attack": 120,
        "dodge" : 100,
        "lvl" : 160,
        "damage_type" : "瘀傷",
]),
});

int valid_enable(string usage) { return usage == "hand" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練大慈大悲手必須空手。\n");

        if( query("max_neili", me)<3500 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 250)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你對禪宗心法的知識了解太少，無法理解大慈大悲手。\n");

        if ((int)me->query_skill("buddhism", 1) < (int)me->query_skill("dacidabei-shou",1) &&
            (int)me->query_skill("buddhism", 1) < 400)
                return notify_fail("你受禪宗心法知識的知識所限，難以進一步領悟大慈大悲手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("dashou-yin",1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的大慈大悲手。\n");

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
                  level   = (int) me->query_skill("dashou-yin",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        object weapon;

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練「大慈大悲手」必須空手。\n");

        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠，練不了大慈大悲手。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，練不了大慈大悲手。\n");

        me->receive_damage("qi", 60);
        addn("neili", -70, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"dacidabei-shou/" + action;
}
