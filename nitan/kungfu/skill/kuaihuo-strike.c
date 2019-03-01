// kuaihuo-strike.c 快活十三掌
// Last Modified by sir 10.22.2001

#include <ansi.h>
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

mapping *action = ({
([        "action" : "$N左手一拳直攻，右手如開似閉，封住對方出手，底下暗出撩陰腿，正是"GRN"「痛快淋漓」"NOR"",
        "lvl"    : 0,
        "skill_name" : "痛快淋漓"
]),
([        "action" : "$N右手一掌封向$n面門，手掌暗顫，已是封住$n視線，左手直拳攻向$n胸口，正是一招"HIG"「敞開胸臆」"NOR"",
        "lvl"    : 20,
        "skill_name" : "敞開胸臆"
]),
([        "action" : "$N右手五直叉開，揮向$n面門，左手揮動，急點$n右身數處大穴，乃是"HIB"「六月揮扇」"NOR"",
        "lvl"    : 40,
        "skill_name" : "六月揮扇"
]),
([        "action": "$N使出"HIR"「臘月圍爐」"NOR"，雙臂向$n身體抱去，正中出腿疾踢$n$l",
        "lvl"    : 60,
        "skill_name" : "臘月圍爐"
]),
([        "action" : "$N使出"MAG"「月下賞梅」"NOR"，左掌入彎月，斜斜向$n面門劈下，右手五指半曲，如梅枝斜出，指向$n",
        "lvl"    : 80,
        "skill_name" : "月下賞梅"
]),
([        "action" : "$N腰間使出鐵板橋功夫，雙手成提壺斟酒狀，片刻間已指向$n嘴角，正是一招"HIW"「花間酌酒」"NOR"",
        "lvl"    : 100,
        "skill_name" : "花間酌酒"
]),
([        "action" : "$N右手五指直顫，急點$n數處大穴，左手成鶴形擊出，乃是"HIM"「弄鶴閒琴」"NOR"",
        "lvl"    : 120,
        "skill_name" : "弄鶴閒琴"
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }
int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練快活十三掌必須空手。\n");
        if ((int)me->query_skill("panshi-shengong", 1) < 20)
                return notify_fail("你磐石神功火候不夠，無法學快活十三掌。\n");
        if( query("max_neili", me)<50 )
                return notify_fail("你的內力太弱，無法練快活十三掌。\n");
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<40 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練快活十三掌。\n");
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
        int d_e2 = -5;
        int p_e1 = 15;
        int p_e2 = 40;
        int f_e1 = 150;
        int f_e2 = 260;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("kuaihuo-strike", 1);
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
        return __DIR__"kuaihuo-strike/" + action;
}

int help(object me)
{
        write(HIC"\n快活十三掌："NOR"\n");
        write(@HELP

    快活十三掌是泰山派的武功。

        學習要求：
                磐石神功20級
                內力50
HELP
        );
        return 1;
}
