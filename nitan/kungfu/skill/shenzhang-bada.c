// shenzhang-bada.c - 神掌八打
       
inherit SHAOLIN_SKILL;
        
mapping *action = ({
([     "action": "$N一招「橫雲斷峰」左掌佯攻，右掌蓄勢擊向$n的$l",
       "force" : 120,
       "attack": 40,
       "parry" : 20,
       "dodge" : -15,
       "damage": 20,
       "lvl"   : 0,
       "skill_name" : "橫雲斷峰",
       "damage_type" : "淤傷"
]),
([     "action": "$N飛身上前，雙掌同時擊出，一招「三羊開泰」，將$n籠罩于掌風之中",
       "force" : 150,
       "attack": 50,
       "parry" : 15,
       "dodge" : 0,
       "damage": 35,
       "lvl"   : 20,
       "skill_name" : "三羊開泰",
       "damage_type" : "淤傷"
]),
([     "action": "$N一招「跨虎登山」，左掌長驅直進，迅雷般拍向$n的$l",
       "force" : 180,
       "attack": 60,
       "parry" : 25,
       "dodge" : -5,
       "damage": 50,
       "lvl"   : 40,
       "skill_name" : "跨虎登山",
       "damage_type" : "淤傷"
]),
([     "action": "$N一招「龍躍深淵」，後退了一步，隨後身形往後一個倒縱，右掌凌空拍向$n的$l",
       "force" : 200,
       "attack": 70,
       "parry" : 35,
       "dodge" : -15,
       "damage": 80,
       "lvl"   : 60,
       "skill_name" : "龍躍深淵",
       "damage_type" : "淤傷"
]),
([     "action": "$N一招「雁落平沙」，身體半蹲，雙掌一掃，兩道勁風擊向$n的下盤",
       "force" : 230,
       "attack": 80,
       "parry" : 30,
       "dodge" : -15,
       "damage": 110,
       "lvl"   : 80,
       "skill_name" : "雁落平沙",
       "damage_type" : "淤傷"
]),
([     "action": "$N一個轉身，一招「玄鳥劃抄」，右掌連拍，掌風分三路擊向$n",
       "force" : 270,
       "attack": 100,
       "parry" : 30,
       "dodge" : 5,
       "damage": 140,
       "lvl"   : 120,
       "skill_name" : "玄鳥劃抄",
       "damage_type" : "淤傷"
]),
([     "action": "$N縱身而上，一招「盤龍繞步」，左掌一圈，右掌隨即直拍向$n的胸口",
       "force" : 300,
       "attack": 100,
       "parry" : 10,
       "dodge" : -15,
       "damage": 160,
       "lvl"   : 160,
       "skill_name" : "盤龍繞步",
       "damage_type" : "淤傷"
]),
([     "action": "$N身體旋轉起來，一招「威鎮八方」，幻出無數掌影，同時擊向$n",
       "force" : 350,
       "attack": 120,
       "parry" : 50,
       "dodge" : 15,
       "damage": 200,
       "lvl"   : 200,
       "skill_name" : "威鎮八方",
       "damage_type" : "淤傷"
]),
});

int valid_enable(string usage) { return usage == "strike" || usage == "parry"; } 
     
int valid_combine(string combo) { return combo == "wuxiang-zhi"; } 
      
int valid_learn(object me) 
{ 
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練神掌八打必須空手。\n"); 
      
        if ((int)me->query_skill("force") < 300) 
                return notify_fail("你的內功火候不夠，無法學神掌八打。\n"); 
     
        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力太弱，無法練神掌八打。\n"); 
      
        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("shenzhang-bada", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的大力金剛指。\n"); 
      
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
        int i, level; 
        level = (int) me->query_skill("shenzhang-bada", 1); 
        for (i = sizeof(action); i > 0; i--) 
                if (level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{ 
        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習！\n"); 
      
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n"); 
      
        if( query("neili", me)<80 )
                return notify_fail("你的內力不夠練神掌八打。\n"); 
      
        me->receive_damage("qi", 90); 
        addn("neili", -70, me);
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"shenzhang-bada/" + action; 
} 