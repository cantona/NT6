inherit SKILL;

mapping *action = ({
([      "action" : "$N左腳猛地飛起，一式「一步三環」，腳尖踢向$n的$l",
        "force"  : 80,
        "damage" : 20,
        "dodge" : 15,
        "lvl" : 0,
        "damage_type" : "瘀傷",
        "skill_name" : "一步三環"
]),
([      "action" : "$N左腳頓地，右腳一式「三步九轉」，猛地踹向$n的$l",
        "force"  : 120,
        "damage" : 25,
        "dodge" : 10,
        "lvl" : 10,
        "damage_type" : "瘀傷",
        "skill_name" : "三步九轉"
]),
([      "action" : "$N兩臂舒張，右腳橫踢，既猛且準，一式「十二連環」踢向$n",
        "force"  : 150,
        "damage" : 30,
        "dodge" : 15,
        "lvl" : 20,
        "damage_type" : "瘀傷",
        "skill_name" : "十二連環"
]),
([      "action" : "$N突然躍起，雙足連環圈轉，一式「雙打奇門」，攻向$n的全身",
        "force"  : 190,
        "damage" : 35,
        "dodge" : 15,
        "lvl" : 40,
        "damage_type" : "瘀傷",
        "skill_name" : "雙打奇門"
]),
([      "action" : "$N雙腳交叉踢起，一式「環變中盤」，腳腳不離$n的面門左右",
        "force"  : 220,
        "damage" : 40,
        "dodge" : 20,
        "lvl" : 60,
        "damage_type" : "瘀傷",
        "skill_name" : "環變中盤"
]),
([      "action" : "$N一個側身，右腳自上而下「繩掛一條鞭」，照$n的面門直劈下來",
        "force"  : 260,
        "damage" : 45,
        "dodge" : 35,
        "lvl" : 80,
        "damage_type" : "瘀傷",
        "skill_name" : "繩掛一條鞭"
]),
([      "action" : "$N使一式「十字繞三尖」，雙足忽前忽後，迅猛無及踹向$n的胸口",
        "force"  : 300,
        "damage" : 50,
        "dodge" : 30,
        "lvl" : 100,
        "damage_type" : "瘀傷",
        "skill_name" : "十字繞三尖"
]),
([      "action" : "$N開聲吐氣，大喝一聲，一式「犀牛望月轉回還」，雙腳猛踢$n",
        "force"  : 330,
        "damage" : 60,
        "dodge" : 35,
        "lvl" : 120,
        "damage_type" : "瘀傷",
        "skill_name" : "犀牛望月轉回還"
]),
});

int valid_enable(string usage) { return usage == "unarmed" ||  usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習十二路潭腿必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學十二路潭腿。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練十二路潭腿。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("tan-tui", 1))
                return notify_fail("你基本拳腳火候不夠，無法領會更高深的十二路潭腿。\n");

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

        level = (int)me->query_skill("tan-tui", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練十二路潭腿。\n");

        me->receive_damage("qi", 60);
        addn("neili", -51, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tan-tui/" + action;
}