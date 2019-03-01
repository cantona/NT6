inherit SKILL;

mapping *action = ({
([      "action" : "$N左腳猛地飛起，一式「盤古開天」，腳尖踢向$n的$l",
        "force"  : 80,
        "damage" : 20,
        "dodge"  : 15,
        "lvl"    : 0,
        "damage_type" : "瘀傷",
        "skill_name"  : "盤古開天"
]),
([      "action" : "$N左腳頓地，右腳一式「流星趕月」，猛踹$n的$l",
        "force"  : 120,
        "damage" : 25,
        "dodge"  : 10,
        "lvl"    : 15,
        "damage_type" : "瘀傷",
        "skill_name"  : "流星趕月"
]),
([      "action" : "$N兩臂舒張，右腳橫踢，既猛且準，一式「橫掃千軍」踢向$n",
        "force"  : 150,
        "damage" : 30,
        "dodge"  : 15,
        "lvl"    : 30,
        "damage_type" : "瘀傷",
        "skill_name"  : "橫掃千軍"
]),
([      "action" : "$N突然躍起，雙足連環圈轉，一式「百步穿楊」，攻向$n的全身",
        "force"  : 190,
        "damage" : 35,
        "dodge"  : 15,
        "lvl"    : 50,
        "damage_type" : "瘀傷",
        "skill_name"  : "百步穿楊"
]),
([      "action" : "$N雙腳交叉踢起，一式「川流不息」，腳腳不離$n的面門左右",
        "force"  : 220,
        "damage" : 40,
        "dodge"  : 20,
        "lvl"    : 70,
        "damage_type" : "瘀傷",
        "skill_name"  : "川流不息"
]),
([      "action" : "$N一個側身，右腳自上而下「獨踹華山」，照$n的面門直劈下來",
        "force"  : 260,
        "damage" : 45,
        "dodge"  : 35,
        "lvl"    : 90,
        "damage_type" : "瘀傷",
        "skill_name"  : "獨踹華山"
]),
([      "action" : "$N使一式「夸父追日」，雙足忽前忽後，迅猛無及踹向$n的胸口",
        "force"  : 300,
        "damage" : 50,
        "dodge"  : 30,
        "lvl"    : 100,
        "damage_type" : "瘀傷",
        "skill_name"  : "夸父追日"
]),
([      "action" : "$N開聲吐氣，大喝一聲，一式「驚天動地」，雙腳猛地踢向$n的$l",
        "force"  : 330,
        "damage" : 60,
        "dodge"  : 35,
        "lvl"    : 120,
        "damage_type" : "瘀傷",
        "skill_name"  : "驚天動地"
]),
});

int valid_enable(string usage)
{
        return usage == "unarmed" ||  usage == "parry";
}

int valid_combine(string combo)
{
        return combo == "xiaoyaoyou";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("學習絕命腿必須空手。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法學絕命腿。\n");

        if( query("max_neili", me)<500 )
                return notify_fail("你的內力太弱，無法練絕命腿。\n");

        if ((int)me->query_skill("unarmed", 1) < (int)me->query_skill("jueming-tui", 1))
                return notify_fail("你的基本拳腳火候不夠，無法領會更高深的絕命腿法。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -60;
        int d_e2 = -30;
        int p_e1 = 0;
        int p_e2 = 30;
        int f_e1 = 220;
        int f_e2 = 320;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jueming-tui", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

int practice_skill(object me)
{
        if( query("qi", me)<70 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<70 )
                return notify_fail("你的內力不夠練絕命腿。\n");

        me->receive_damage("qi", 60);
        addn("neili", -51, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"jueming-tui/" + action;
}