// /lungfu/skill/fuhu-quan
// by dubei
// 羅漢伏虎拳

inherit SHAOLIN_SKILL;

mapping *action = ({
([      "action" : "$N並舉雙拳，使出一招「灌頂」，當頭砸向$n的$l  ",
        "skill_name" : "灌頂",
        "force" : 80,
        "dodge" : 5,
        "lvl" : 0,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「解苦」，身形一低，左手護頂，右手一拳擊向$n的襠部  ",
        "skill_name" : "解苦",
        "force" : 60,
        "dodge" : -5,
        "lvl" : 10,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「顰眉」，左拳虛擊$n的前胸，一錯身，右拳橫掃$n的太陽穴  ",
        "skill_name" : "顰眉",
        "force" : 80,
        "dodge" : 10,
        "lvl" : 20,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N神形怪異，使一招「嗔恚」，雙拳上下擊向$n的$l  ",
        "skill_name" : "嗔恚",
        "force" : 100,
        "dodge" : 5,
        "lvl" : 40,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「靜寂」，雙拳交錯，緩緩擊出，勁氣直指$n的$l  ",
        "skill_name" : "靜寂",
        "force" : 120,
        "dodge" : -5,
        "lvl" : 50,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N微微一笑，使出一式「妙音」，雙拳前後擊出，直取$n的左胸  ",
        "skill_name" : "妙音",
        "force" : 150,
        "dodge" : 10,
        "lvl" : 60,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N使出一招「明心」，全身疾轉，雙拳橫掃$n的$l  ",
        "skill_name" : "明心",
        "force" : 270,
        "dodge" : 20,
        "lvl" : 80,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N飛身一躍，使出一招「制勝」，一拳猛擊$n咽喉  ",
        "skill_name" : "制勝",
        "force" : 260,
        "dodge" : 5,
        "lvl" : 100,
        "damage_type" : "瘀傷",
]),
});

int valid_enable(string usage) { return usage == "cuff" || usage == "parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練羅漢伏虎拳必須空手。\n");
    else if( query("max_neili", me)<1000 )
                return notify_fail("你的內力不夠練羅漢伏虎拳。\n");
    if ((int)me->query_skill("hunyuan-yiqi", 1) < 100 )
                      return notify_fail("你的心意氣混元功還不夠，還不能練羅漢伏虎拳。\n");
 
        if ((int)me->query_skill("cuff", 1) < (int)me->query_skill("fuhu-quan", 1))
                      return notify_fail("你的基本拳法火候，還不能練羅漢伏虎拳。\n");
          return 1;
}
 int valid_combine(string combo)
 {
         object me;
         me = this_player();
 
         if ((int)me->query_str() > 32)
                 return combo=="qinlong-shou";
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
          level = (int)me->query_skill("fuhu-quan", 1);
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}

int practice_skill(object me)
{
            if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練羅漢伏虎拳必須空手。\n");
         if( query("jingli", me)<30 )
                 return notify_fail("你的體力太低了。\n");
         if( query("neili", me)<20 )
                 return notify_fail("你的內力不夠練羅漢伏虎拳。\n");
         addn("jingli", -25, me);
         addn("neili", -5, me);
         return 1;
}
