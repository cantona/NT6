// jinshe-zhang.c 金蛇遊身掌
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "skill_name" : "千蛇出洞",
        "action" : "$N雙掌一錯，一招"HIY"「千蛇出洞」"NOR"幻出漫天掌影攏向$n的$l",
        "lvl"    : 0
]),
([        "skill_name" :  "魔吼天地",
        "action" : "$N暴喝一聲，雙掌連環推出，一招"HIY"「大沼龍蛇」"NOR"強勁的掌風直撲$n的$l",
        "lvl"    : 10
]),
([        "skill_name" : "雙蛇搶珠",
        "action" : "$N雙掌紛飛，一招"HIY"「雙蛇搶珠」"NOR"直取$n的$l",
        "lvl"    : 20
]),
([        "skill_name" : "遊走式",
        "action" : "$N提氣纏身遊走，一招"HIY"「遊走式」"NOR"，森森掌風無孔不入般地擊向$n的$l",
        "lvl"    : 30
]),
([        "skill_name" : "盤身式",
        "action" : "$N盤身錯步，雙掌平推，凝神聚氣，一招"HIY"「盤身式」"NOR"拍向$n的$l",
        "lvl"    : 40
]),
([        "skill_name" : "金蛇吐舋",
        "action" : "$N左掌立于胸前，右掌推出，一招"HIY"「金蛇吐舋」"NOR"擊向$n$l",
        "lvl"    : 50
]),
([        "skill_name" : "金蛇翻身咬",
        "action" : "$N使出"HIY"「金蛇翻身咬」"NOR"，身形凌空飛起，從空中當頭向$n的$l出掌攻擊",
        "lvl"    : 60
]),
([        "skill_name" : "杯弓蛇影",
        "action" : "$N使出一招"HIY"「杯弓蛇影」"NOR"，左掌化虛為實擊向$n的$l",
        "lvl"    : 70
]),
([        "skill_name" : "金蛇纏絲手",
        "action" : "$N左掌畫了個圈圈，右掌推出，一招"HIY"「金蛇纏絲手」"NOR"擊向$n$l",
        "lvl"    : 80
]),
([        "skill_name" : "靈蛇遊八方",
        "action" : "$N使出"HIY"「靈蛇遊八方」"NOR"，身形散作八處同時向$n的$l出掌攻擊",
        "lvl"    : 90
]),
([        "skill_name" : "金蛇探頭",
        "action" : "$N使出金蛇遊身掌法"HIY"「金蛇探頭」"NOR"，如鬼魅般欺至$n身前，一掌拍向$n的$l",
        "lvl"    : 100
]),
([        "skill_name" : "金龍升天",
        "action" : "$N內氣上提，全身拔起，一招"HIY"「金龍升天」"NOR"，雙掌凌空拍下，$n的全身都被籠罩在掌力之下",
        "lvl"    : 110
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_learn(object me)
{
        if( query("max_neili", me)<500 )
                return notify_fail("你的內力不足，無法練金蛇遊身掌。\n");

        if ((int)me->query_skill("force") < 80)
                return notify_fail("你的內功火候不夠，無法練金蛇遊身掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("jinshe-zhang", 1))
                return notify_fail("你的基本掌法水平有限，無法領會更高深的金蛇遊身掌。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力不夠了，休息一下再練吧。\n");
        if( query("neili", me)<15 )
                return notify_fail("你的內力不夠了，休息一下再練吧。\n");
        me->receive_damage("qi", 25);
        addn("neili", -10, me);
        return 1;
}
string *parry_msg = ({
        "$n使出「粘」字訣，雙掌一劃，引偏了$N的$w。\n",
});

string *unarmed_parry_msg = ({
        "$n施展出金蛇遊身掌，輕描淡寫的化解了$N的攻勢。\n",
});

string query_parry_msg(object weapon)
{
        if (weapon)
                return parry_msg[random(sizeof(parry_msg))];
        else
                return unarmed_parry_msg[random(sizeof(unarmed_parry_msg))];
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
        int d_e1 = -10;
        int d_e2 = 10;
        int p_e1 = 30;
        int p_e2 = 60;
        int f_e1 = 100;
        int f_e2 = 210;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jinshe-zhang", 1);
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
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"jinshe-zhang/" + action;
}

int help(object me)
{
        write(HIC"\n金蛇遊身掌："NOR"\n");
        write(@HELP

    金蛇遊身掌載于「金蛇密笈」，乃金蛇郎君夏雪宜的獨門武功。
夏雪宜幼時全家不幸被溫家五老劫掠滅門，立志報仇。後于苗疆得
識五毒教教主之妹何紅藥，並得其助獲得五毒教的「三寶」──金
蛇劍、金蛇錐及藏寶圖，因而練成絕世武功。
    夏雪宜性情古怪，為人陰狠，武功便正如其人般詭異難測。江
湖上人人聞其名而為之色變，乃是出名的難纏人物。夏雪宜留下的
「金蛇密笈」載有他一身武功，即金蛇劍法、金蛇錐法和金蛇遊身
掌。

        學習要求：
                內力500
HELP
        );
        return 1;
}
