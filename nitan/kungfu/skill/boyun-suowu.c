// boyun-suowu 撥雲鎖霧

inherit SKILL;

mapping *action = ({
([      "action" : "$N雙手飄浮不定,突然從不可以思意的角度，拍向$n的胸口",
        "dodge" : 50,
        "damage": 60,
        "lvl" : 10,
        "skill_name" : "雲裏霧裏",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N長嘯一聲，平地飛起三丈，居高臨下腳上頭下，雙手重疊在一起，運勁壓向對手，$n大驚失色",
        "dodge" : 60,
        "damage": 100,
        "skill_name" : "撥開雲霧",
        "damage_type" : "瘀傷"
]),
([      "action" : "$n眼前一花，失去$N的身影，只聽見身後響起一陣掌風，只見$N雙手同時拍中$n背門要害",
        "dodge" : 70,
        "damage": 80,
        "skill_name" : "迷雲幽霧",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N掌指齊出，拍拿並施，拿向$n的三路要害",
        "dodge" : 90,
        "damage": 100,
        "lvl" : 10,
        "skill_name" : "雲深霧澤",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N運氣狂哮，四面八方出現無數掌影，一掌突出，夾着雷霆萬鈞之式拍向$n",
        "dodge" : 120,
        "damage": 150,
        "lvl" : 80,
        "skill_name" : "漫天雲霧",
        "damage_type" : "瘀傷"
]),
});

string *parry_msg = ({
        "$N一招擊在$n身上，卻被$n隨手破去。\n",
        "$n輕輕一帶，$N發現自己招數盡數落空。\n",
        "$n左牽右引，$N如身處漩流，連續轉了好幾個圈。\n",
        "$n輕輕一轉，$N一招擊在地上，只打得塵土飛揚。\n",
});
int valid_enable(string usage)
{
        return (usage == "hand") || (usage == "parry");
}
string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練撥雲鎖霧必需空手。\n");
        if ((int)me->query_skill("biyun-xinfa", 1) < 10)
                return notify_fail("你的碧雲心法火候不夠，無法學撥雲鎖霧。\n");
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練撥雲鎖霧。\n");
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
        int d_e1 = 20;
        int d_e2 = 40;
        int p_e1 = -35;
        int p_e2 = 15;
        int f_e1 = 200;
        int f_e2 = 300;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("boyun-suowu", 1);
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
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練撥雲鎖霧。\n");
        me->receive_damage("qi", 25);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"boyun-suowu/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("boyun-suowu", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
