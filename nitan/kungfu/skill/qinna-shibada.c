//擒拿十八打
//by gladiator
inherit SHAOLIN_SKILL;

mapping *action = ({
([  "action" : "$N馬步一立，身子微曲，暗喝一聲，一招「望月拜天」，似爪似拳直捅$n的$l",
        "force" : 170,
        "dodge" : 0,
       "parry" : 10,
        "lvl" : 0,
        "skill_name" : "望月拜天",
        "damage_type" : "瘀傷"
]),
([  "action" : "$N“哈哈”一笑，左拳由下至上，右手似擒似推，一招「跨日向天」，交替打向$n",
        "force" : 200,
        "dodge" :-5,
       "parry" : 5,
        "lvl" : 15,
        "skill_name" : "跨日向天",
        "damage_type" : "瘀傷"
]),
([  "action" : "$N對$n一聲大喝，使一招「長虹經天」，左拳擊出，右腳同時絆向的$l",
        "force" : 230,
        "dodge" : 0,
       "parry" : 10,
        "lvl" : 30,
        "skill_name" : "長虹經天",
        "damage_type" : "震傷"
]),
([        "action" : "$N悶喝一聲，雙拳向上分開，一記「舉火燒天」，拳劃弧線，左右同時擊向$n的$l",
        "force" : 260,
        "dodge" : 0,
       "parry" : 0,
        "lvl" : 45,
        "skill_name" : "舉火燒天",
        "damage_type" : "瘀傷"
]),
([  "action" : "$N施出「輕臂擎天」，左手凌空打出，直逼$n的$l",
        "force" : 290,
        "dodge" : 0,
       "parry" : 5,
        "lvl" : 60,
        "skill_name" : "一臂擎天",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N一聲長嘯，雙拳交錯擊出，一招「石破天驚」，拳風密佈$n的前後左右",
        "force" : 310,
        "dodge" : 10,
       "parry" : 10,
        "lvl" : 70,
        "skill_name" : "石破天驚",
        "damage_type" : "瘀傷"
]),
([        "action" : "$N怒吼一聲，凌空飛起，一式「天崩地裂」，雙拳居高臨下，齊齊捶向$n",
        "force" : 350,
        "dodge" : 20,
       "parry" : -10,
        "lvl" : 80,
        "skill_name" : "天崩地裂",
        "damage_type" : "內傷"
]),
([  "action" : "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招「無法無天」，左擒右拿，如雨點般向$n打去",
        "force" : 380,
        "dodge" : -5,
       "parry" : -10,
        "lvl" : 90,
        "skill_name" : "無法無天",
        "damage_type" : "內傷"
])
});

int valid_enable(string usage) { return usage=="unarmed" || usage=="parry"; }
int valid_combine(string combo) { return combo=="luohan-quan"; }


int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練「擒拿十八打」必須空手。\n");
    if ((int)me->query_skill("shaolin-xinfa", 1) < 100)
        return notify_fail("你的少林心法不夠，無法學「擒拿十八打」。\n");
    if( query("max_neili", me)<1500 )
        return notify_fail("你的內力太弱，無法練「擒拿十八打」。\n");

    if ((int)me->query_skill("unarmed", 1) < 100)
        return notify_fail("你的基本拳腳太弱，無法練「擒拿十八打」。\n");

    if ((int)me->query_skill("hunyuan-yiqi", 1) < 100)
        return notify_fail("你的心一氣混元功太弱，無法練「擒拿十八打」。\n");
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
        if (( (int)me->query_skill("unarmed", 1) >= 120 )
        &&  ( (int)me->query_skill("qinna-shibada", 1) >= 120 )
        && ( (int)me->query_skill("cuff",1) >= 120 )
        && ( (int)me->query_skill("luohan-quan", 1) >= 120 )
         && (query("neili", me) >= 500 )
      &&  (me->query_skill_prepared("cuff") == "luohan-quan")
      && (me->query_skill_mapped("unarmed") == "qinna-shibada")
      && random(10) > 8 )
      {
                return ([
        "action": "$N手中招式突然加快，一招“掌擒雙絕”，隔空向$n擊出一拳，隨即雙掌連環擊出",
               "parry":(int)me->query_skill("parry")/8,
             "dodge":(int)me->query_skill("dodge") / 20 + (int)me->query_skill("unarmed") / 15,
        "force": (int)me->query_skill("cuff") + (int)me->query_skill("unarmed"),
                "damage_type": "內傷"
  ]);
        }

    level   = (int) me->query_skill("qinna-shibada",1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
        if( query("jingli", me)<30 )
                return notify_fail("你的精力太低了。\n");
        if( query("qi", me)<20 )
        return notify_fail("你的內力不夠練「擒拿十八打」。\n");
        addn("jingli", -25, me);
        addn("qi", -5, me);
        return 1;
}
