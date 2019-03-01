// This program is a part of NT MudLIB
// yingzhua-gong.c 鷹爪功

#include <ansi.h>;
inherit SHAOLIN_SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N全身拔地而起，半空中一個筋鬥，一式"HIY"「兇鷹襲兔」"NOR"，迅猛地抓向$n的$l",
        "lvl"    : 0,
        "skills_name" : "兇鷹襲兔",
]),
([        "action" : "$N單腿直立，雙臂平伸，一式"HIW"「雄鷹展翅」"NOR"，雙爪一前一後攏向$n的$l",
        "lvl"    : 10,
        "skills_name" : "雄鷹展翅",
]),
([        "action" : "$N一式"HIB"「拔翅橫飛」"NOR"，全身向斜裡平飛，右腿一繃，雙爪搭向$n的肩頭",
        "lvl"    : 20,
        "skills_name" : "拔翅橫飛",
]),
([        "action" : "$N雙爪交錯上舉，使一式"HIM"「迎風振翼」"NOR"，一拔身，分別襲向$n左右腋空門",
        "lvl"    : 30,
        "skills_name" : "迎風振翼",
]),
([        "action" : "$N全身滾動上前，一式"HIR"「飛龍獻爪」"NOR"，右爪突出，鬼魅般抓向$n的胸口",
        "lvl"    : 40,
        "skills_name" : "飛龍獻爪",
]),
([        "action" : "$N伏地滑行，一式"CYN"「撥雲瞻日」"NOR"，上手襲向膻中大穴，下手反抓$n的襠部",
        "lvl"    : 50,
        "skills_name" : "撥雲瞻日",
]),
([        "action" : "$N左右手掌爪互逆，一式"YEL"「搏擊長空」"NOR"，無數道勁氣破空而出，迅疾無比地擊向$n",
        "lvl"    : 55,
        "skills_name" : "兇鷹襲兔",
]),
([        "action" : "$N騰空高飛三丈，一式"HIW"「鷹揚萬裡」"NOR"，天空中頓時顯出一個巨靈爪影，緩緩罩向$n",
        "lvl"    : 60,
        "skills_name" : "兇鷹襲兔",
])
});

int valid_enable(string usage) { return usage=="claw" || usage=="parry"; }
int valid_combine(string combo) { return combo=="fengyun-shou"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練鷹爪功必須空手。\n");

        if ((int)me->query_skill("force") < 50)
                return notify_fail("你的內功火候不夠，無法學鷹爪功。\n");

        if( query("max_neili", me)<250 )
                return notify_fail("你的內力太弱，無法練鷹爪功。\n");

        if ((int)me->query_skill("claw", 1) < (int)me->query_skill("yingzhua-gong", 1))
                return notify_fail("你的基本抓法火候水平有限，無法領會更高深的鷹爪功。\n");

        return 1;
}
int practice_skill(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練鷹爪功。\n");
        me->receive_damage("qi", 30);
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
        int d_e1 = 50;
        int d_e2 = 30;
        int p_e1 = -5;
        int p_e2 = -30;
        int f_e1 = 200;
        int f_e2 = 350;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("yingzhua-gong", 1);
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
                "damage_type" : random(2) ? "抓傷" : "內傷",
        ]);
}
int learn_bonus() { return 20; }
int practice_bonus() { return 20; }
int success() { return 15; }
int power_point(object me) { return 1; }

string perform_action_file(string action)
{
        return __DIR__"yingzhua-gong/" + action;
}

int help(object me)
{
        write(HIC"\n鷹爪功："NOR"\n");
        write(@HELP

    鷹爪功為少林七十二絕技之一。
    可與風雲手互備。

        學習要求：
                混元一氣功20級
                內力100
HELP
        );
        return 1;
}
