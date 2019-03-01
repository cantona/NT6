//xiuli-qiankun.c

inherit SHAOLIN_SKILL; 

mapping *action = ({ 
  ([      "action" : "$N一式「童子拜佛」，雙袖隆起，一道無邊暗勁湧向$n", 
    "force" : 200, 
    "dodge" : 5, 
    "parry" : 0,
    "damage": 10, 
    "lvl" : 9, 
    "skill_name" : "童子拜佛", 
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "$N身形突轉，雙袖飛舞，霎時間拍出千百道掌影，正是一招「煙雨飄渺」，令$n無可躲藏", 
    "force" : 230, 
    "dodge" : 15, 
    "parry" : 10, 
    "damage": 10, 
    "lvl" : 29, 
    "skill_name" : "煙雨飄渺",
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "$N雙袖一引一收，掌勁卻至下而上斜斜擊出，一式「回風舞柳」，$n待要避時已然不及", 
    "force" : 270, 
    "dodge" : 5,
    "parry" : 15,
    "damage": 20, 
    "lvl" : 39, 
    "skill_name" : "回風舞柳",
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "只見$N雙袖一擺，陡然滑出數尺，右掌順著來勢一招「桃墳撲蝶」往$n的$l按去",
    "force" : 320, 
    "dodge" : 10,
    "parry" : 5, 
    "damage": 15,
    "lvl" : 49, 
    "skill_name" : "桃墳撲蝶", 
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "$N身形陡進，罡陽柔氣從袖底揮出，湧向$n的$l，正是玄功若神的一招「曉陽雲暖」",
    "force" : 380, 
    "dodge" : 25,
    "parry" : -5,
    "damage": 25,
    "lvl" : 59, 
    "skill_name" : "曉陽雲暖",
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "$N長吸一口真氣，身形一振，一式「佛動山河」，雙掌當胸平推而出，看似緩慢，$n卻已無法閃避！",
    "force" : 420, 
    "dodge" : 15, 
    "parry" : 0, 
    "damage": 35,
    "lvl" : 69,
    "skill_name" : "佛動山河", 
    "damage_type" : "瘀傷" 
  ]),
  ([      "action" : "$N猛地門戶大開，迎著$n的掌勢合身而上，掌勁及身的一霎那，$N突然一個鷂子翻身，電光火石間$n的掌力已然全部返回，正是少林不傳之密「乾坤逆轉」", 
    "force" : 480, 
    "dodge" : 20, 
    "parry" : 10, 
    "damage": 50, 
    "lvl" : 80, 
    "skill_name" : "乾坤逆轉", 
    "damage_type" : "瘀傷" 
  ]) 
}); 
int valid_enable(string usage) { return  usage=="unarmed" || usage=="parry"; } 
int valid_combine(string combo) { return combo=="hunyuan-zhang"; } 
int valid_learn(object me) 
{ 
    if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
        return notify_fail("練袖裡乾坤須空手。\n"); 
    if ((int)me->query_skill("shaolin-xinfa", 1) < 100) 
        return notify_fail("你的少林心法不夠，無法學習袖裡乾坤。\n"); 
    if( query("max_neili", me)<1500 )
        return notify_fail("你的內力太弱，無法練習袖裡乾坤。\n"); 
    return 1; 
} 
mapping query_action(object me, object weapon) 
{ 
    int i, level; 
    level   = (int)me->query_skill("xiuli-qiankun",1); 
    for(i = sizeof(action); i > 0; i--) 
        if(level > action[i-1]["lvl"]) 
            return action[NewRandom(i, 20, level/5)]; 
} 
int practice_skill(object me) 
{
    if( query("qi", me)<30 )
        return notify_fail("你的體力太低了。\n"); 
    if( query("neili", me)<20 )
        return notify_fail("你的內力不夠練習袖裡乾坤。\n"); 
    me->receive_damage("qi", 30); 
    addn("neili", -10, me);
    return 1;
}
string perform_action_file(string action) 
{ 
    return __DIR__"xiuli-qiankun/" + action; 
}