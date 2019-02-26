// duanyun-fu.c 斷雲斧
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N驀地騰空躍起，雙手緊握$w，對準$n的頭頂，自上而下地砍了下去，\n只在半空中留下一團巨大的黑影",
        "lvl" : 0,
        "skill_name" : "開天闢地"
]),
([        "action" : "$N突然發一聲喊，衝前兩步，手中$w由下而上反撩$n下三路，$n見到一\n道淡黃色的氣影逼向自己，情知不妙，急忙招架",
        "lvl" : 20,
        "skill_name" : "氣衝霄漢"
]),
([        "action" : "$N忽然虎吼一聲，閃身斜向左前方衝出一步，身體微晃，手中$w在空中\n劃出一道淡影，急速橫掃$n的右肩，氣勢迫人",
        "lvl" : 40,
        "skill_name" : "橫掃千軍"
]),
([        "action" : "$N突然抽身向右滾倒，隨即跳起，就在跳起的一瞬間，已單臂握着$w砸\n向$n的左肋，出手既快且狠",
        "lvl" : 60,
        "skill_name" : "以退為進"
]),
([        "action" : "$N雙手橫舉$w，平掃$n前胸，招式未使老就已打住猝然變招，斧尖直撞\n$n的小腹，",
        "lvl" : 80,
        "skill_name" : "金斧撞鐘"
]),
([        "action" : "$N不急不緩地轉身微蹲，$n見$N露出破綻，急忙搶攻，卻突然發現$N的\n身體已轉過來，手中$w正迅猛地掃向自己的下盤",
        "lvl" : 100,
        "skill_name" : "迴風轉雲"
]),
([        "action" : "$N身形微動，就在同一時間自上中下左右砍出五斧，$n見五把$w從不同\n的方位砍向自己，一時間竟不知該如何招架",
        "lvl" : 120,
        "skill_name" : "五斧奪命"
]),
([        "action" : "$N前腳猛地往地上一頓，大地也微微一震，接着舉起斧頭在頭頂急轉
數\n圈，$w就隱含風雲之聲平直而沉穩地襲向$n，$n無論向何處閃躲，總看見斧尖離\n自己不到一尺，不由大驚失色",
        "lvl" : 150,
        "skill_name" : "一斧斷雲"
])
});

int valid_enable(string usage) { return usage=="axe" ||        usage=="parry"; }

int valid_learn(object me)
{
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的內功心法火候不夠，無法學斷雲斧。\n");
        if( query("max_neili", me)<150 )
                return notify_fail("你的內力太弱，無法練斷雲斧。\n");
        return 1;
}

int practice_skill(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
                 || query("skill_type", weapon) != "axe" )
                return notify_fail("你使用的武器不對。\n");
        if( query("qi", me)<50 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<20 )
                return notify_fail("你的內力不夠練斷雲斧。\n");
        me->receive_damage("qi", 35);
        return 1;
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
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 60;
        int d_e2 = 30;
        int p_e1 = -30;
        int p_e2 = -60;
        int f_e1 = 200;
        int f_e2 = 400;
        int m_e1 = 300;
        int m_e2 = 500;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int)me->query_skill("duanyun-fu", 1);
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
                "damage_type" : random(2) ? "割傷" : "劈傷",
        ]);
}
int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        return 1;
}
string perform_action_file(string action)
{
        return __DIR__"duanyun-fu/" + action;
}

int help(object me)
{
        write(HIC"\n斷雲斧："NOR"\n");
        write(@HELP

    斷雲斧為天南大理段家的武功。

        學習要求：
                枯榮禪功20級
                內力150
HELP
        );
        return 1;
}
