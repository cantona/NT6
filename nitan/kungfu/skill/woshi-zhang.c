inherit SHAOLIN_SKILL; 

mapping *action = ({ 
([      "action" : "$N馬步一立，身子微曲，暗喝一聲，一招「望月拜天」，一掌直劈$n的$l", 
        "force" : 110, 
        "dodge" : 10, 
        "parry" : 10, 
        "attack": 30, 
        "damage": 40, 
        "lvl" : 10, 
        "skill_name" : "望月拜天", 
        "damage_type" : "瘀傷" 
]), 
([      "action" : "$N“哈哈”一笑，左掌由下至上，右掌平平擊出，一招「跨日向天」，交替打向$n", 
        "force" : 130, 
        "dodge" : 20, 
        "parry" : 30, 
        "attack": 30, 
        "damage": 50, 
        "lvl" : 30, 
        "skill_name" : "跨日向天", 
        "damage_type" : "瘀傷" 
]), 
([      "action" : "$N對$n一聲大喝，使一招「長虹經天」，左掌擊出，隨即右掌跟上，兩重力道打向$n的$l", 
        "force" : 140, 
        "dodge" : 27, 
        "parry" : 43, 
        "attack": 40, 
        "damage": 60, 
        "lvl" : 60, 
        "skill_name" : "長虹經天", 
        "damage_type" : "震傷" 
]),
([      "action" : "$N悶喝一聲，雙掌向上分開，一記「舉火燒天」，掌劃弧線，左右同時擊向$n的$l", 
        "force" : 160, 
        "dodge" : 37, 
        "parry" : 33, 
        "attack": 54, 
        "damage": 78, 
        "lvl" : 80, 
        "skill_name" : "舉火燒天", 
        "damage_type" : "瘀傷" 
]), 
([      "action" : "$N施出「一臂擎天」，一聲大吼，一掌凌空劈出，掌風直逼$n的$l", 
        "force" : 180, 
        "dodge" : 42, 
        "parry" : 23, 
        "attack": 64, 
        "damage": 89, 
        "lvl" : 110, 
        "skill_name" : "一臂擎天", 
        "damage_type" : "瘀傷" 
]), 
([      "action" : "$N一聲長嘯，雙掌交錯擊出，一招「石破天驚」，掌風密佈$n的前後左右", 
        "force" : 190, 
        "dodge" : 46, 
        "parry" : 33, 
        "attack": 54, 
        "damage": 93, 
        "lvl" : 140, 
        "skill_name" : "石破天驚", 
        "damage_type" : "瘀傷" 
]), 
([      "action" : "$N怒吼一聲，凌空飛起，一式「天崩地裂」，雙掌居高臨下，齊齊拍向$n", 
        "force" : 200, 
        "dodge" : 43, 
        "parry" : 43, 
        "attack": 55, 
        "damage": 103, 
        "lvl" : 170, 
        "skill_name" : "天崩地裂", 
        "damage_type" : "內傷" 
]), 
([      "action" : "$N仰天大笑，勢若瘋狂，衣袍飛舞，一招「無法無天」，掌風凌厲，如雨點般向$n",  
        "force" : 210, 
        "dodge" : 33, 
        "parry" : 53, 
        "attack": 58, 
        "damage": 105, 
        "lvl" : 190, 
        "skill_name" : "無法無天", 
        "damage_type" : "內傷" 
]) 
}); 
int valid_enable(string usage) { return usage=="strike" || usage=="parry"; } 

int valid_learn(object me) 
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練「握石掌」必須空手。\n"); 
        if (me->query_skill("weituo-zhang", 1) < 80
        && me->query_skill("sanhua-zhang", 1) < 80
        && me->query_skill("weituo-zhang", 1) < 80
        && me->query_skill("banruo-zhang", 1) < 80)
                return notify_fail("你的必須先精通散花掌，般若掌，韋陀掌中的一種才能繼續學習高深的掌法。\n"); 

        if ((int)me->query_skill("force", 1) < 80) 
                return notify_fail("你的基本內功火候不夠，還無法研習握石掌。\n"); 

        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法修煉韋陀掌。\n"); 
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

        level   = (int) me->query_skill("woshi-zhang",1); 
        for(i = sizeof(action); i > 0; i--) 
                if(level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
}

int practice_skill(object me) 
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太差，沒法繼續練習握石掌。\n"); 
        if( query("neili", me)<70 )
                return notify_fail("你的內力太差，無法繼續練習握石掌。\n"); 
        addn("qi", -55, me);
        addn("neili", -50, me);
        return 1; 
}

string perform_action_file(string action) 
{
return __DIR__"woshi-zhang/" + action; 
}
