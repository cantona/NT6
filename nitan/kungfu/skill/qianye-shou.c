// qianye-shou.c 如來千葉手

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N一式"HIB"「南海禮佛」"NOR"，右手虛晃，左手揚起，突然拍向$n的背後二穴",
        "lvl" : 0,
        "skill_name" : "南海禮佛"
]),
([        "action" : "$N側身一晃，一式"HIY"「金玉瓦礫」"NOR"，左手拿向$n的肩頭，右拳打向$n的胸口",
        "lvl" : 10,
        "skill_name" : "金玉瓦礫"
]),
([        "action" : "$N一式"HIG"「人命呼吸」"NOR"，右手環攏成爪，一出手就向扣$n的嚥喉要害",
        "lvl" : 20,
        "skill_name" : "人命呼吸"
]),
([        "action" : "$N左手虛招，右掌直立，一式"HIW"「鏡裡觀影」"NOR"，錯步飄出，疾拍$n的面門",
        "lvl" : 30,
        "skill_name" : "鏡裡觀影"
]),
([        "action" : "$N使一式"CYN"「水中捉月」"NOR"，左拳上格，右手探底突出，抓向$n的襠部",
        "lvl" : 38,
        "skill_name" : "水中捉月"
]),
([        "action" : "$N雙拳揮舞，一式"HIC"「浮雲去來」"NOR"，兩手環扣，攏成圈狀，猛擊$n的下頜",
        "lvl" : 45,
        "skill_name" : "浮雲去來"
]),
([        "action" : "$N一式"HIM"「水泡出沒」"NOR"，十指伸縮，虛虛實實地襲向$n的全身要穴",
        "lvl" : 51,
        "skill_name" : "水泡出沒"
]),
([        "action" : "$N雙手抱拳，一式"RED"「夢裡明明」"NOR"，掌影翻飛，同時向$n施出九九八十一招",
        "lvl" : 56,
        "skill_name" : "夢裡明明"
]),
([        "action" : "$N一式"HIR"「覺後空空」"NOR"，拳招若隱若現，若有若無，緩緩地拍向$n的丹田",
        "lvl" : 60,
        "skill_name" : "覺後空空"
]),
});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"; }
int valid_combine(string combo) { return combo == "longzhua-gong"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練如來千葉手必須空手。\n");

        if ((int)me->query_skill("force") < 40)
                return notify_fail("你的內功火候不夠，無法學如來千葉手。\n");

        if( query("max_neili", me)<200 )
                return notify_fail("你的內力太弱，無法練如來千葉手。\n");

        if ((int)me->query_skill("hand", 1) < (int)me->query_skill("qianye-shou", 1))
                return notify_fail("你的基本手法水平有限，無法領會更高深的如來千葉手。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練如來千葉手。\n");
        me->receive_damage("qi", 35);
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
        int d_e1 = -50;
        int d_e2 = -15;
        int p_e1 = 15;
        int p_e2 = 40;
        int f_e1 = 160;
        int f_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("qianye-shou", 1);
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
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

mixed hit_ob(object me, object target, int damage)
{
        string msg;
        mixed result;
        int j;

        j = me->query_skill("qianye-shou", 1);

        if ((random(10) > 5) && j > 150 &&
            me->query_skill("buddhism", 1) >180 &&
            query("neili", me)>1000 && query("max_neili", me)>2500 )
        {
                result = ([ "damage" : damage ]);
                msg = CYN"$N輕飄飄拍出一掌，掌到中途，忽然微微搖晃，登時一掌變兩掌，兩掌變四掌，四掌變八掌。\n"NOR;
                msg += "結果$n只須遲得頃刻，$N便八掌變十六掌，進而幻化為三十二掌。\n";
                msg +="$n躲閃不及被漫天掌影裹在核心。\n";
                result += ([ "msg" : msg ]);

                return result;
        }
}
string perform_action_file(string action)
{
        return __DIR__"qianye-shou/" + action;
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 10; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n如來千葉手："NOR"\n");
        write(@HELP

    如來千葉手為少林七十二絕技之一。
    可與龍爪功互備。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
