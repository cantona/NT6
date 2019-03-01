// weituo-gun.c 韋陀棍

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action":"$N一招"YEL"「黃石納履」"NOR"，手中$w如蜻蜓點水般，招招向$n的下盤要害點去
",
        "lvl" : 0,
        "skill_name" : "黃石納履"
]),
([        "action":"$N把$w平提胸口，一擰身，一招"BLU"「勒馬停鋒」"NOR"，$w猛地撩向$n的頸部",
        "lvl" : 8,
        "skill_name" : "勒馬停鋒"
]),
([        "action":"$N一招"HIC"「平地龍飛」"NOR"，全身滴溜溜地在地上打個大轉，舉棍向$n的胸腹間戳去",
        "lvl" : 16,
        "skill_name" : "平地龍飛"
]),
([        "action":"$N伏地一個滾翻，一招"HIB"「伏虎聽風」"NOR"，$w挾呼呼風聲迅猛掃向$n的足脛
",
        "lvl" : 24,
        "skill_name" : "伏虎聽風"
]),
([        "action":"$N一招"HIW"「流星趕月」"NOR"，身棍合一，棍端逼成一條直線，流星般向頂向$n的$l",
        "lvl" : 35,
        "skill_name" : "流星趕月"
]),
([        "action":"$N雙手持棍劃了個天地大圈，一招"RED"「紅霞貫日」"NOR"，一棍從圓心正中擊出，撞向$n的胸口",
        "lvl" : 44,
        "skill_name" : "紅霞貫日"
]),
([        "action":"$N一招"YEL"「投鞭斷流」"NOR"，$w高舉，以雷霆萬鈞之勢對準$n的天靈當頭劈下",
        "lvl" : 52,
        "skill_name" : "投鞭斷流"
]),
([        "action":"$N潛運真力，一招"HIW"「蒼龍歸海」"NOR"，$w頓時長了數丈，矯龍般直射$n的胸口",
        "lvl" : 60,
        "skill_name" : "蒼龍歸海"
]),
});

int valid_enable(string usage) { return usage == "club" || usage == "parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<250 )
                return notify_fail("你的內力不夠。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候太淺。\n");

        if ((int)me->query_skill("club", 1) < (int)me->query_skill("weituo-gun", 1))
                return notify_fail("你的基本棍法水平有限，無法領會更高深的韋陀棍法。\n");

        return 1;
}
int practice_skill(object me)
{
        object weapon;

        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "club" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 || query("neili", me)<50 )
                return notify_fail("你的內力或氣不夠練韋陀棍。\n");
        me->receive_damage("qi", 20);
        addn("neili", -10, me);
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
        int d_e1 = -45;
        int d_e2 = -60;
        int p_e1 = -15;
        int p_e2 = -25;
        int f_e1 = 200;
        int f_e2 = 250;
        int m_e1 = 50;
        int m_e2 = 150;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("weituo-gun", 1);
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
                "damage"      : m_e1 + (m_e2 - m_e1) * seq / ttl,
                "damage_type" : "挫傷",
        ]);
}
int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"weituo-gun/" + action;
}

int help(object me)
{
        write(HIC"\n韋陀棍："NOR"\n");
        write(@HELP

    韋陀棍為少林七十二絕技之一。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
