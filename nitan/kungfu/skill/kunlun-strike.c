// kunlun-strike.c 崑崙掌

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N掌風激盪，雙掌錯落，來勢神妙無方，一招"HIY"「日入空山」"NOR"，劈向$n的$l",
        "lvl" : 0,
        "skill_name" : "日入空山"
]),
([        "action" : "$N雙掌驟起，一招"HIC"「天清雲淡」"NOR"，一掌擊向$n面門，另一掌卻按向$n小腹",
        "lvl" : 20,
        "skill_name" : "天清雲淡"
]),
([        "action" : "$N雙掌互錯，變幻莫測，一招"HIC"「秋風不盡」"NOR"，前後左右，瞬息之間向$n攻出了四四一十六招",
        "lvl" : 38,
        "skill_name" : "秋風不盡"
]),
([        "action" : "$N一聲清嘯，呼的一掌，一招"HIB"「山迴路轉」"NOR"，自巧轉拙，卻是去勢奇快，向$n的$l猛擊過去，",
        "lvl" : 55,
        "skill_name" : "山迴路轉"
]),
([        "action" : "$N雙掌交錯，若有若無，一招"BLU"「天衣無縫」"NOR"，拍向$n的$l",
        "lvl" : 72,
        "skill_name" : "天衣無縫"
]),
([        "action" : "$N一招"GRN"「青山斷河」"NOR"，右手一拳擊出，左掌緊跟着在右拳上一搭，變成雙掌下劈，擊向$n的$l",
        "lvl" : 87,
        "skill_name" : "青山斷河"
]),
([        "action" : "$N雙手齊劃，跟着雙掌齊推，一招"MAG"「北風捲地」"NOR"，一股排山倒海的掌力，直撲$n面門",
        "lvl" : 101,
        "skill_name" : "北風捲地"
]),
([        "action" : "$N突然滴溜溜的轉身，一招"HIW"「天山雪飄」"NOR"，掌影飛舞，霎時之間將$n四面八方都裹住了",
        "lvl" : 120,
        "skill_name" : "天山雪飄"
])
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_learn(object me)
{
        mapping fam=query("family", me);
        if (fam["family_name"] != "崑崙派" || fam["generation"] != 2)
                return notify_fail("崑崙掌只能從何足道處學到。\n");
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練崑崙掌必須空手。\n");
        if ((int)me->query_skill("xuantian-wuji", 1) < 120)
                return notify_fail("你的玄天無極功火候不夠，無法練崑崙掌。\n");
        if( query("gender", me) != "女性" )
        {
                if ((int)me->query_skill("zhentian-cuff", 1) < 80)
                        return notify_fail("你的相關功夫火候不夠，無法練崑崙掌。\n");
        } else
        {
                if ((int)me->query_skill("chuanyun-leg", 1) < 80)
                        return notify_fail("你的相關功夫火候不夠，無法練崑崙掌。\n");
        }
        if( query("max_neili", me)<800 )
                return notify_fail("你的內力修為不夠，無法練崑崙掌。\n");
        return 1;
}
int practice_skill(object me)
{
        int lvl = me->query_skill("kunlun-strike", 1);
        int i = sizeof(action);

        while (i--) if (lvl == action[i]["lvl"]) return 0;

        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練崑崙掌。\n");
        me->receive_damage("qi", 30);
        addn("neili", -15, me);
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
        int d_e1 = -30;
        int d_e2 = -10;
        int p_e1 = 10;
        int p_e2 = 40;
        int f_e1 = 160;
        int f_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("kunlun-strike", 1);
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
int learn_bonus() { return 25; }
int practice_bonus() { return 25; }
int success() { return 15; }
int power_point(object me) { return 1.0; }

string perform_action_file(string action)
{
        return __DIR__"kunlun-strike/" + action;
}

int help(object me)
{
        write(HIC"\n崑崙掌法："NOR"\n");
        write(@HELP

    崑崙掌法為崑崙派上乘絕技。

        學習要求：
                玄天無極功120級
                震天拳法或穿雲腿80級
                內力800
                何足道的嫡傳弟子
HELP
        );
        return 1;
}
