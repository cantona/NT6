inherit SHAOLIN_SKILL;
        
mapping *action = ({
([
       "action": "$N左手一個虛晃，右指跟進，一招「割肉飼鷹」，右指擊向$n的$l",
       "force" : 80,
       "attack": 25,
       "parry" : 15,
       "dodge" : -5,
       "damage" : 50,
       "lvl"   : 0,
       "skill_name" : "割肉飼鷹",
       "damage_type" : "刺傷"
]),
([
       "action": "$N揉身而上，隨後身形一矮，一式「投身餓虎」,試圖拿住$n的周身大穴",
       "force" : 100,
       "attack": 30,
       "parry" : 15,
       "dodge" : 0,
       "damage" : 65,
       "lvl"   : 20,
       "skill_name" : "投身餓虎",
       "damage_type" : "點穴"
]),
([
       "action": "$N面露兇光，一式「斫頭謝天」,手指直擊向$n的百匯大穴",
       "force" : 150,
       "attack": 50,
       "parry" : 5,
       "dodge" : -15,
       "damage" : 100,
       "lvl"   : 40,
       "skill_name" : "斫頭謝天",
       "damage_type" : "點穴"
]),
([
       "action": "$N摒指如刀，一招「折骨出髓」,雙指劃出一條刀路砍向$n的腰部",
       "force" : 150,
       "attack": 30,
       "parry" : 25,
       "dodge" : 10,
       "damage" : 100,
       "lvl"   : 60,
       "skill_name" : "折骨出髓",
       "damage_type" : "割傷"
]),
([
       "action": "$N忽然左騰右縱，雙指連點，一招「挑身千燈」，一時間無數道勁氣同時擊向$n",
       "force" : 180,
       "attack": 45,
       "parry" : 0,
       "dodge" : -15,
       "damage" : 120,
       "lvl"   : 80,
       "skill_name" : "挑身千燈",
       "damage_type" : "刺傷"
]),
([
       "action": "$N提起身形，一招「挖眼佈施」,居高臨下，以訊雷不及掩耳的速度功向$n",
       "force" : 180,
       "attack": 35,
       "parry" : 0,
       "dodge" : -15,
       "damage" : 100,
       "lvl"   : 100,
       "skill_name" : "挖眼佈施",
       "damage_type" : "割傷"
]),
([
       "action": "$N雙指分左右兩路，一招「剝皮書經」，分別點向$n兩處大穴，令$n措不及防",
       "force" : 200,
       "attack": 50,
       "parry" : 10,
       "dodge" : 15,
       "damage" : 120,
       "lvl"   : 120,
       "skill_name" : "剝皮書經",
       "damage_type" : "點穴"
]),
([
       "action": "$N一招「剜心決志」，一指對準自己，隨後就地一個翻滾，右手食指戳向$n的$l",
       "force" : 220,
       "attack": 60,
       "parry" : 20,
       "dodge" : 25,
       "damage" : 130,
       "lvl"   : 160,
       "skill_name" : "剜心決志",
       "damage_type" : "刺傷"
]),
([
       "action": "$N一招「刺血滿地」，雙手十指連彈，一時間無數道勁氣如潮水般湧向$n，令$n無從躲閃",
       "force" : 300,
       "attack": 100,
       "parry" : 40,
       "dodge" : 55,
       "damage" : 200,
       "lvl"   : 200,
       "skill_name" : "刺血滿地",
       "damage_type" : "刺傷"
]),
});

string main_skill() { return "canhe-zhi"; }

int valid_enable(string usage) { return usage == "finger" || usage == "parry"; } 
      
int valid_learn(object me) 
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練修羅指必須空手。\n"); 
      
        if ((int)me->query_skill("force") < 200) 
                return notify_fail("你的內功火候不夠，無法學修羅指。\n"); 
     
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力太弱，無法練修羅指。\n"); 
      
        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("xiuluo-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的修羅指。\n"); 
      
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
        level = (int) me->query_skill("xiuluo-zhi", 1); 
        for (i = sizeof(action); i > 0; i--) 
                if (level > action[i-1]["lvl"]) 
                        return action[NewRandom(i, 20, level/5)]; 
} 
      
int practice_skill(object me) 
{
        if ((int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你已將這種指法融入參合指，不必再分開練習了。\n");

        if( query_temp("weapon", me) || 
            query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手練習。\n"); 
      
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了，無法練修羅指。\n"); 
      
        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠，無法練修羅指。\n");
      
        me->receive_damage("qi", 80);
        addn("neili", -80, me);
        return 1; 
} 
      
string perform_action_file(string action) 
{ 
        return __DIR__"xiuluo-zhi/" + action; 
} 
