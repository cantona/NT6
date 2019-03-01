// xuwu-piaomiao.c 虛無縹緲拳

inherit SKILL;

mapping *action = ({
([      "action":"$N左掌虛按，右拳下擊，直奔$n的$l而去。",
        "force" :50,
        "parry" :8,
        "dodge" :10,
        "damage":5,
        "lvl"   :0,
        "damage_type" :"瘀傷"
]),
([      "action":"$N大步跨前，立右拳，挽左拳向$n的$l擊去。",
        "force" :55,
        "parry" :10,
        "dodge" :15,
        "damage":10,
        "lvl"   :15,
        "damage_type" :"瘀傷"
]),
([      "action":"$N連踏上兩步，雙拳飛擊$n頭部兩側。",
        "force" :65,
        "parry" :10,
        "dodge" :10,
        "damage":20,
        "lvl"   :25,
        "damage_type" :"瘀傷"
]),
([      "action":"$N收拳腰間，晃到$n身後，「呼」地揮出一拳,擊向$n的$l。",
        "force" :80,
        "parry" :30,
        "dodge" :20,
        "damage":35,
        "lvl"   :40,
        "damage_type" :"瘀傷"
]),
([      "action":"$N退身側步，讓過$n，右拳反擊$n後腰。",
        "force" :100,
        "parry" :40,
        "dodge" :30,
        "damage":40,
        "lvl"   :50,
        "damage_type" :"瘀傷"
]),
([      "action":"$N左拳劃過$n右臂，右拳向$n肩頭拍了下去。",
        "force" :130,
        "parry" :30,
        "dodge" :20,
        "damage":50,
        "lvl"   :70,
        "damage_type" :"瘀傷"
]),
([      "action":"$N輕輕一縱，身體倒轉，雙拳向$n腦後擊出。",
        "force" :170,
        "parry" :50,
        "dodge" :80,
        "damage":70,
        "lvl"   :80,
        "damage_type" :"瘀傷"
])
});

int valid_enable(string usage) { return usage=="cuff" || usage=="parry"; }

int valid_combine(string combo) { return combo=="huanmo-longtianwu"; }

int valid_learn(object me)
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練虛無縹緲必須空手。\n"); 

    if ((int)me->query_skill("force", 1) < 50) 
        return notify_fail("你的內功火候不夠，無法學虛無縹緲。\n"); 

    if( query("max_neili", me)<250 )
        return notify_fail("你的內力太弱，無法練虛無縹緲。\n"); 

    if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("xuwu-piaomiao", 1))
        return notify_fail("你的基本拳法火候不夠，無法領會更高深的虛無縹緲。\n");

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("xuwu-piaomiao", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if( query("qi", me)<50 )
         return notify_fail("你的體力太低了。\n"); 

    if( query("neili", me)<40 )
         return notify_fail("你的內力不夠練「虛無縹緲」。\n"); 

    me->receive_damage("qi", 30); 
    addn("neili", -20, me);

    return 1; 
}
