// huanmo-longtianwu.c 幻魔朧天舞

inherit SKILL;

mapping *action = ({
([      "action":"$N左掌微分，右手一伸，扣向$n的$l。",
        "force" :10,
        "dodge" :10,
        "damage":10,
        "lvl"   :0,
        "damage_type" :"瘀傷"
]),
([      "action":"$N倏地一個轉身，雙手一翻，直摜$n下頜。",
        "force" :20,
        "dodge" :15,
        "damage":20,
        "lvl"   :10,
        "damage_type" :"瘀傷"
]),
([      "action":"$N身子一縱，雙手滑溜異常對準$n的後心抓去。",
        "force" :35,
        "dodge" :30,
        "damage":30,
        "lvl"   :25,
        "damage_type" :"瘀傷"
]),
([      "action":"$N左手虛晃，右手飄飄，拍向$n$l",
        "force" :50,
        "dodge" :40,
        "damage":40,
        "lvl"   :40,
        "damage_type" :"瘀傷"
]),
([      "action":"$N身形微動，晃至$n身後，雙手變爪，直襲$n後腦。",
        "force" :70,
        "dodge" :60,
        "damage":55,
        "lvl"   :60,
        "damage_type" :"瘀傷"
])
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_combine(string combo) { return combo=="xuwu-piaomiao"; }

int valid_learn(object me)
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練幻魔朧天舞必須空手。\n"); 

    if ((int)me->query_skill("force", 1) < 60)
        return notify_fail("你的內功火候不夠，無法學幻魔朧天舞。\n"); 

    if( query("max_neili", me)<250 )
        return notify_fail("你的內力太弱，無法練幻魔朧天舞。\n"); 

    if ((int)me->query_skill("hand", 1) < (int)me->query_skill("huanmo-longtianwu", 1)) 
        return notify_fail("你的基本手法火候不夠，無法領會更高深的幻魔朧天舞。\n"); 

    return 1;
}

mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level = (int)me->query_skill("huanmo-longtianwu", 1);
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
             return action[NewRandom(i, 20, level/5)]; 
} 

int practice_skill(object me) 
{ 
    if( query("qi", me)<45 )
         return notify_fail("你的體力太低了。\n"); 

    if( query("neili", me)<35 )
         return notify_fail("你的內力不夠練「幻魔朧天舞」。\n"); 

    me->receive_damage("qi", 28); 
    addn("neili", -20, me);

    return 1; 
}
