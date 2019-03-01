inherit SKILL;

mapping *action = ({
([      "action": "$N馬步一立，身子微曲，暗喝一聲，一招「貓躥」，一拳直捅$n的$l",
        "force" : 130,
        "dodge" : 5,
        "parry" : 7,
        "attack": 14,
        "damage": 4,
        "lvl"   : 0,
        "skill_name" : "貓躥",
        "damage_type": "瘀傷"
]),
([      "action": "$N哈哈一笑，左拳由下至上，右拳平平擊出，一招「兔滾」，交替打向$n",
        "force" : 145,
        "dodge" : 18,
        "parry" : 17,
        "attack": 16,
        "damage": 6,
        "lvl"   : 20,
        "skill_name" : "兔滾",
        "damage_type": "瘀傷"
]),
([      "action": "$N對$n一聲大喝，使一招「鷹翻」，左拳擊出，隨即右拳跟上，兩重力道打向$n的$l",
        "force" : 157,
        "dodge" : 16,
        "parry" : 19,
        "attack": 17,
        "damage": 11,
        "lvl"   : 40,
        "skill_name" : "鷹翻",
        "damage_type": "瘀傷"
]),
([      "action": "$N悶喝一聲，雙拳向上分開，一記「鷂子翻身」，拳劃弧線，左右同時擊向$n的$l",
        "force" : 165,
        "dodge" : 24,
        "parry" : 21,
        "attack": 19,
        "damage": 14,
        "lvl"   : 60,
        "skill_name" : "鷂子翻身",
        "damage_type": "瘀傷"
]),
([      "action": "$N施出「細胸巧」，一聲大吼，一拳凌空打出，拳風直逼$n的$l",
        "force" : 185,
        "dodge" : 24,
        "parry" : 28,
        "attack": 33,
        "damage": 19,
        "lvl"   : 80,
        "skill_name" : "細胸巧",
        "damage_type": "瘀傷"
]),
([      "action": "$N一聲長嘯，雙拳交錯擊出，一招「跺子腳」，拳風密布$n的前後左右",
        "force" : 197,
        "dodge" : 28,
        "parry" : 30,
        "attack": 36,
        "damage": 21,
        "lvl"   : 100,
        "skill_name" : "跺子腳",
        "damage_type": "瘀傷"
]),
([      "action": "$N怒吼一聲，凌空飛起，一式「鬆子靈」，雙拳居高臨下，齊齊捶向$n",
        "force" : 285,
        "dodge" : 24,
        "parry" : 21,
        "attack": 47,
        "damage": 24,
        "lvl"   : 120,
        "skill_name" : "鬆子靈",
        "damage_type": "瘀傷"
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練百勝神拳必須空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不夠，無法學百勝神拳。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練百勝神拳。\n");

        if ((int)me->query_skill("cuff", 1) < 40)
                return notify_fail("你的基本拳腳火候太淺。\n");

        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("baisheng-quan", 1))
                return notify_fail("你的基本拳腳水平有限，無法領會更高深的百勝神拳。\n");

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

        lvl = (int) me->query_skill("baisheng-quan", 1);
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
        if( query("qi", me)<60 )
                return notify_fail("你現在手足酸軟，休息一下再練吧。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 50);
        addn("neili", -34, me);

        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"baisheng-quan/" + action;
}