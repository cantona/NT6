inherit SKILL;

mapping *action = ({
([      "action": "$N雙掌驟起，一招「電」字訣，一掌擊向$n面門，另一掌卻按向$n小腹",
        "force" : 185,
        "dodge" : 11,
        "parry" : 12,
        "attack": 9,
        "damage": 12,
        "lvl"   : 0,
        "skill_name" : "電字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌互錯，變幻莫測，一招「雨」字訣，瞬息之間向$n攻出了四四一十六招",
        "force" : 205,
        "dodge" : 18,
        "parry" : 17,
        "attack": 13,
        "damage": 17,
        "lvl"   : 20,
        "skill_name" : "雨字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲清嘯，呼的一掌，一招「霜」字訣，去勢奇快，向$n的$l猛擊過去，",
        "force" : 217,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 21,
        "lvl"   : 40,
        "skill_name" : "霜字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙掌交錯，若有若無，一招「震」字訣，自巧轉拙，拍向$n的$l",
        "force" : 225,
        "dodge" : 24,
        "parry" : 21,
        "attack": 22,
        "damage": 33,
        "lvl"   : 60,
        "skill_name" : "震字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N一招「靂」字訣，右手一拳擊出，左掌緊跟着在右拳上一搭，變成雙掌下劈，擊向$n的$l",
        "force" : 255,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 41,
        "lvl"   : 80,
        "skill_name" : "靂字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N雙手齊劃，跟着雙掌齊推，一招「霹」字訣，一股排山倒海的掌力，直撲$n面門",
        "force" : 267,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 49,
        "lvl"   : 100,
        "skill_name" : "霹字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N突然滴溜溜的轉身，一招「霆」字訣，掌影飛舞，霎時之間將$n四面八方都裹住了",
        "force" : 280,
        "dodge" : 24,
        "parry" : 21,
        "attack": 37,
        "damage": 51,
        "lvl"   : 120,
        "skill_name" : "霆字訣",
        "damage_type": "瘀傷"
]),
([      "action": "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招「雷」字訣，掌風凌厲，如雨點般向$n打去",
        "force" : 320,
        "dodge" : 36,
        "parry" : 35,
        "attack": 41,
        "damage": 58,
        "lvl"   : 140,
        "skill_name" : "雷字訣",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練霹靂奔雷掌必須空手。\n");

        if ((int)me->query_skill("force") < 30)
                return notify_fail("你的內功火候不夠，無法學霹靂奔雷掌。\n");

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練霹靂奔雷掌。\n");

        if ((int)me->query_skill("strike", 1) < 80)
                return notify_fail("你的基本掌法火候太淺。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("benlei-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的霹靂奔雷掌。\n");

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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -35;
        int p_e2 = 15;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("benlei-zhang", 1);
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

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }


int practice_skill(object me)
{
        if( query("qi", me)<80 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練霹靂奔雷掌。\n");

        me->receive_damage("qi", 55);
        addn("neili", -90, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"benlei-zhang/" + action;
}