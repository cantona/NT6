// This program is a part of NT MudLIB
// yizhi-chan.c 一指禪

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N雙指並攏，一式"HIY"「佛恩濟世」"NOR"，和身而上，左右手一前一後戳向$n的胸腹間",
        "lvl" : 0,
        "skill_name" : "佛恩濟世"
]),
([        "action" : "$N左掌護胸，一式"HIY"「佛光普照」"NOR"，右手中指前後劃了個半弧，猛地一甩，疾點$n的$l",
        "lvl" : 20,
        "skill_name" : "佛光普照"
]),
([        "action" : "$N身形閃動，一式"HIY"「佛門廣渡」"NOR"，雙手食指端部各射出一道青氣，射向$n的全身要穴",
        "lvl" : 40,
        "skill_name" : "佛門廣渡"
]),
([        "action" : "$N盤膝跌坐，一式"HIY"「佛法無邊」"NOR"，左手握拳托肘，右手拇指直立，遙遙對著$n一捺",
        "lvl" : 60,
        "skill_name" : "佛法無邊"
])
});

int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }
int valid_combine(string combo) { return combo=="banruo-zhang"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練一指禪必須空手。\n");

        if ((int)me->query_skill("force") < 60)
                return notify_fail("你的內功火候不夠，無法學一指禪。\n");

        if( query("max_neili", me)<300 )
                return notify_fail("你的內力太弱，無法練一指禪。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("yizhi-chan", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的一指禪。\n");

        return 1;
}

int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<50 )
                return notify_fail("你的內力不夠練一指禪。\n");
        me->receive_damage("qi", 40);
        addn("neili", -25, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 25;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -15;
        int f_e1 = 360;
        int f_e2 = 460;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("yizhi-chan", 1);
        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : action[seq]["action"],
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}

void skill_improved(object me)
{
        int level = (int)me->query_skill("yizhi-chan", 1);

        if( level == 180 && !query("sl_gift/con", me) )
        {
                addn("con", 1, me);
                set("sl_gift/con", 1, me);
                tell_object(me, "你的一指禪和般若掌學有所成，提高了你的根骨。\n");
        }
        /*
        if( query("family/family_name", me) == "少林派" )
        {
                if( !(level % 10) && level >= (int)me->query_skill("hunyuan-yiqi", 1) )
                {
                        me->improve_skill("hunyuan-yiqi", (level - 5), 1);
                        tell_object(me, "你在一指禪方面的造詣增進了你的混元一氣功修為。\n");
                }
        }
        */
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        mixed result;

        if( damage_bonus < 50 ) return 0;

        if( random(damage_bonus/2) > victim->query_str()/10 )
        {
                result = ([ "damage" : damage_bonus ]);
                result += ([ "msg" : HIR "你聽到「咻」一聲輕響，一股勁氣直透$n的前胸！\n" NOR ]);
                return result;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("yizhi-chan", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

string perform_action_file(string action)
{
        return __DIR__"yizhi-chan/" + action;
}

int learn_bonus() { return 5; }
int practice_bonus() { return 5; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n一指禪："NOR"\n");
        write(@HELP

    一指禪為少林七十二絕技之一。
    可與般若掌互備。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
