// jiujie-whip 九節鞭法
// Last Modified by sir 10.20.01

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action": "$N使一招"HIB"「怪蟒出洞」"NOR"，手中$w向上一揚，猛的對準$n的$l橫掃過去",
        "lvl" : 0,
        "skill_name" : "怪蟒出洞",
]),
([        "action": "$N氣運雙臂，一招"BLU"「秋風颯颯」"NOR"$w幻出滿天鞭影，虛虛實實地襲向$n的$l",
        "lvl" : 20,
        "skill_name" : "秋風颯颯",
]),
([        "action": "$N不慌不忙掄去$w，一招"MAG"「巨蟒騰空」"NOR"點點鞭影飄浮不定地點向$n的$l",
        "lvl" : 60,
        "skill_name" : "巨蟒騰空",
]),
([        "action": "$N手中$w在空中連連抖動，一招"MAG"「巨蟒翻身」"NOR"忽然狠狠向$n的$l打去！",
        "lvl" : 90,
        "skill_name" : "巨蟒翻身",
]),
([        "action": "$N將手中$w向下一沉，一招"HIG"「風卷殘雲」"NOR"從下向上往$n腰部卷去",
        "lvl" : 120,
        "skill_name" : "風卷殘雲",
]),
});

int valid_enable(string usage) { return (usage=="whip") || (usage=="parry"); }
int valid_learn(object me)
{
        object weapon;

        if( query("max_neili", me)<100 )
                return notify_fail("你的內力修為不足，沒有辦法練九節鞭法。\n");
        if ((int)me->query_skill("zhanzhuang-gong", 1) < 20)
                return notify_fail("你的站樁功火候太淺。\n");
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "whip" )
                return notify_fail("你必須先找一條鞭子才能練鞭法。\n");
        return 1;
}
int practice_skill(object me)
{
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me)) || 
                query("skill_type", weapon) != "whip" )
                return notify_fail("你使用的武器不對。\n");
        if ((int)me->query_skill("yijinjing", 1) < 10)
                return notify_fail("你的易筋經火候太淺。\n");
        if( query("qi", me)<30 )
                return notify_fail("你的體力不夠練九節鞭法。\n");
        me->receive_damage("qi",25);
 
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
        int d_e1 = -40;
        int d_e2 = -30;
        int p_e1 = 10;
        int p_e2 = 20;
        int f_e1 = 50;
        int f_e2 = 100;
        int m_e1 = 50;
        int m_e2 = 150;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("jiujie-whip", 1);
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
                "damage_type" : random(2) ? "淤傷": "刺傷",
        ]);
}
int learn_bonus() { return 30; }
int practice_bonus() { return 30; }
int success() { return 20; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n九節鞭："NOR"\n");
        write(@HELP

    九節鞭是南少林入門鞭法。

        學習要求：
                站樁功50級
                內力修為100
HELP
        );
        return 1;
}
