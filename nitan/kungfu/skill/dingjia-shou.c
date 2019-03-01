// dingjia-qinnashou.c 丁家擒拿手


inherit SKILL;

string *action_msg = ({
        "$N使出一招「鳳尾手」，右手繞個半圈，欺上去抓住了$n的手腕一扭。",
        "$N隨手使出一招「鶴翔手」，左手肘橫過，右手便去抓$n的肩頭。",
        "$N突然一招「龍騰抓」，雙手一前一後，直取$n的左肩。",
        "$N右手一招「虎爪手」，抓向$n背心後的「靈台穴」。",
        "$N左手使出一招「玉女拈針」，內力直透中指指尖，拿向$n的後腰。",
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練丁家擒拿手必須空手。\n");
                
        if( query("max_neili", me)<100 )
                return notify_fail("你的內力太弱，無法練丁家擒拿手。\n");
        return 1;
}

mapping query_action(object me, object weapon)
{
        return ([
                "action": action_msg[random(sizeof(action_msg))], 
                "force": 260 + random(50), 
                "attack": 40 + random(10), 
                "dodge" : 40 + random(10), 
                "parry" : 40 + random(10), 
                "damage_type" : random(2)?"內傷":"瘀傷", 
        ]); 
}

int practice_skill(object me)
{
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練丁家擒拿手。\n");
        me->receive_damage("qi", 40);
        addn("shen", -10, me);
        addn("neili", -40, me);
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"dingjia-shou/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("dingjia-shou", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}
