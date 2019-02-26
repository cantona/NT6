#include <ansi.h>;

inherit SKILL;

mapping *action = ({
([      "action" : "$N左掌劃一半圓，右掌劃出另一半圓，呈合攏之勢，疾拍$n的胸前大穴",
        "force"  : 160,
        "attack" : 10,
        "parry"  : 10,
        "dodge"  : 10,
        "damage" : 10,
        "lvl"    : 0,
        "damage_type" : "瘀傷",
]),
([      "action" : "$N左掌護胸，右拳凝勁後發，深吸一口氣，緩緩推向$n的$l",
        "force"  : 195,
        "attack" : 20,
        "parry"  : 25,
        "dodge"  : 15,
        "damage" : 15,
        "damage_type" : "瘀傷",
        "lvl"    : 30,
]),
([      "action" : "$N縱身向前撲去，一下急衝疾縮，就在兩臂將合未合之際，雙手抱向$n的$l",
        "force"  : 230,
        "attack" : 30,
        "parry"  : 30,
        "dodge"  : 20,
        "damage" : 32,
        "lvl"    : 60,
        "damage_type" : "瘀傷"
]),
([      "action" : "$N兩掌上下護胸，掌勢突然一變，驟然化為滿天掌雨，攻向$n",
        "force"  : 260,
        "attack" : 40,
        "parry"  : 40,
        "dodge"  : 20,
        "damage" : 40,
        "damage_type" : "瘀傷",
        "lvl"    : 90,     
]),
([      "action" : "$N長袖揮處，兩股袖風撲出，$n只覺得密不透風，周身都是掌印，怎麼也閃躲不開",
        "force"  : 270,
        "attack" : 50,
        "parry"  : 55,
        "dodge"  : 35, 
        "damage" : 65,
        "lvl"    : 120,        
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙臂飛舞，兩隻手掌宛似化成了千手千掌，任$n如何躍騰閃躲，始終飛不出"
                   "只掌所圍作的圈圈", 
        "force"  : 300,
        "attack" : 65,
        "parry"  : 70,
        "dodge"  : 40,
        "damage" : 80,
        "lvl"    : 150,
        "damage_type" : "瘀傷"
]), 
});

int valid_enable(string usage) 
{ 
        int lvl;
        lvl = this_player()->query_skill("tianluo-diwang", 1);
        
        if (lvl > 30)
               return usage == "strike" || usage == "parry";
        else
               return  usage == "strike";
}

int valid_combine(string combo)
{ 
        return combo == "meinv-quan"; 
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你必須空手方能練習天羅地網掌。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功基礎不夠，無法修習天羅地網掌。\n");

        if ((int)me->query_skill("strike", 1) < 40)
                return notify_fail("你的基本掌法水平太低，無法研習天羅地網掌。\n");

        if ((int)me->query_skill("strike", 1) < me->query_skill("tianluo-diwang", 1))
                return notify_fail("你的基本掌法水平水平有限，無法研習更高深的天羅地網掌。\n");

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("tianluo-diwang", 1) < 100 ||
            !living(me) || query_temp("weapon", me) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("tianluo-diwang", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:                                             
                                            
                        result += (["msg" : HIC "$n" HIC "雙臂飛舞，似有千掌拍出，密"
                                            HIC "不透風，竟將$N" HIC "的攻勢化解。\n" NOR]);
                        break;

                default:
                        result += (["msg" : HIC "$n" HIC "掌勢突然一變，驟然化為滿天掌雨，"
                                            HIC "護於胸前，$N" HIC "竟無從攻擊。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 80)
        {
                switch (random(2))
                {
                case 0:
                        result = HIY "$n" HIY "雙臂飛舞，似有千掌拍出，密不透風，"
                                 HIY "然而$N" HIY "視之無物，隨意出招，進襲$n" 
                                 HIY "！\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "掌勢突然一變，驟然化為滿天掌雨，"
                                 HIY "護於胸前，可是$N" HIY "卻看透其中虛實，徑"
                                 HIY "直攻向$n\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( query_temp("weapon", me) )
                return 0;

        lvl = me->query_skill("tianluo-diwang", 1);
        if (lvl < 60)  return 0;
        if (lvl < 160) return 40;
        if (lvl < 240) return 60;
        if (lvl < 320) return 80;
        return 100;
}

mapping query_action(object me, object weapon)
{
        int i, level;

        level = (int)me->query_skill("tianluo-diwang", 1);

        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 20, level / 5)];
}

int practice_skill(object me)
{
        if( query("qi", me)<60 )
                return notify_fail("你的體力太低了。\n");

        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 50);
        addn("neili", -35, me);
        return 1;
}

string perform_action_file(string action)
{
        return __DIR__"tianluo-diwang/" + action;
}