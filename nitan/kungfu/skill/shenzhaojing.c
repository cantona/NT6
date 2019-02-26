// 神照經神功 shenzhaojing.c

#include <ansi.h>
inherit FORCE;

string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) 
{
        return 1;
}

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("shenzhaojing", 1);
        return lvl * lvl * 15 * 18 / 100 / 200;
}

mapping *action = ({
([      "action" : "$N倏然躍近，擊出一拳，這一拳無聲無影，去勢快極，向$n的胸口打去",
        "dodge"  : 81,
        "force"  : 323,
        "attack" : 119,
        "parry"  : 94,
        "damage" : 68,
        "lvl"    : 0,
        "damage_type": "內傷"
]),
([      "action" : "$N絲毫不動聲色，右掌平伸，左掌運起神照經神功的勁力，呼的一聲拍向$n",
        "dodge"  : 73,
        "force"  : 362,
        "attack" : 138,
        "parry"  : 51,
        "damage" : 73,
        "lvl"    : 200,
        "damage_type": "內傷"
]),
([      "action" : "$N身形微微一展，已然遊走至$n跟前，陡然間雙掌齊施，向$n猛拍而去",
        "dodge"  : 78,
        "force"  : 389,
        "attack" : 152,
        "parry"  : 53,
        "damage" : 87,
        "lvl"    : 220,
        "damage_type": "內傷"
]),
([      "action" : "$N退後一步，雙掌回收，凌空劃出一個圓圈，頓時一股澎湃的氣勁直湧$n而出",
        "dodge"  : 75,
        "force"  : 410,
        "attack" : 163,
        "parry"  : 67,
        "damage" : 93,
        "lvl"    : 250,
        "damage_type": "內傷"
]),
});

int valid_enable(string usage)
{
        int lvl;
        lvl = (int)this_player()->query_skill("shenzhaojing", 1);

        if(lvl >= 180)
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force";

}

int valid_learn(object me)
{
        if( query("str", me)<32 )
                return notify_fail("你先天膂力孱弱，無法修煉神照經神功。\n");

        if( query("con", me)<32 )
                return notify_fail("你先天根骨孱弱，無法修煉神照經神功。\n");

        if( query("gender", me) == "無性" && query("shenzhaojing", me)>29 )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的神照經神功。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本內功火候不足，不能學神照經神功。\n");

        if ((int)me->query_skill("unarmed", 1) < 200)
                return notify_fail("你的基本拳腳火候不足，不能學神照經神功。\n");

        if( query("max_neili", me)<4000 )
                return notify_fail("你的內力修為不足，不能學神照經神功。\n");

        if (me->query_skill("force", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本內功水平不夠，難以鍛鍊更深厚的神照經神功。\n");

        if (me->query_skill("unarmed", 1) < me->query_skill("shenzhaojing", 1))
                return notify_fail("你的基本拳腳水平不夠，難以鍛鍊更深厚的神照經神功。\n");

        return ::valid_learn(me);
}

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 25;
        int d_e2 = 45;
        int p_e1 = -30;
        int p_e2 = 10;
        int f_e1 = 140;
        int f_e2 = 240;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("shenzhaojing", 1);
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


mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;

        lvl = me->query_skill("shenzhaojing", 1);

        if (damage_bonus < 160
           || lvl < 180
           || query("neili", me)<300
           || query_temp("weapon", me )
           || query_temp("secondary_weapon", me )
           || me->query_skill_mapped("force") != "shenzhaojing"
           || me->query_skill_mapped("unarmed") != "shenzhaojing"
           || me->query_skill_prepared("unarmed") != "shenzhaojing")
                return 0;

        // 神照經神功所具有的既添設額外傷害又使對手中
        // 毒的max_hit 在所有武功中是絕無僅有的，但是
        // 它出現的機率以及傷害值又及毒性傷害相對於其
        // 他武功大大減弱。
        if (damage_bonus > victim->query_con()/10)
        {
                victim->receive_wound("qi", damage_bonus, me);
                victim->affect_by("shenzhao",
                               (["level":query("jiali", me)+random(query("jiali", me)),
                                  "id":query("id", me),
                                  "duration" : lvl / 100 + random(lvl / 10) ]));
                return HIR "$n" HIR "一聲慘嚎，全身骨骼格格格格爆聲不"
                       "絕，肋骨、臂骨、腿骨同時斷折。\n" NOR;
        }
}

int practice_skill(object me)
{
        return notify_fail("神照經神功只能用學(learn)的來增加熟練度。\n");
}

int difficult_level()
{
        return 400;
}

string perform_action_file(string action)
{
        return __DIR__"shenzhaojing/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"shenzhaojing/exert/" + action;
}


int help(object me)
{
        write(HIC"\n神照經："NOR"\n");
        write(@HELP

    丁典是荊門人，出生於武林世家。父母雙亡，家財不少，卻不
想結親，只是勤於練武，結交江湖上的朋友。
    某次他乘船從四川下來，出了三峽後，船泊在三鬥坪。晚上，
在船中聽得岸上有打鬥的聲音。從窗中向外張望。那晚月光明亮，
看得清清楚楚，是三個人在圍攻一個老者。一個是五雲手萬震山。
另一個是陸地神龍言達平。第三個人使一口長劍，身手甚是矯捷，
那是鐵鎖橫江戚長髮。老者便是鐵骨墨萼梅念笙。他們的師父。梅
念笙受傷在先，抵敵不住三個徒弟的毒招，跳江而逃。
    丁典身邊帶得有金創藥，救起梅念笙後，便替他治傷。可是他
背上那一劍刺得好深，穿通了肺，這傷是治不好的了。這麼治了三
天，梅念笙從懷中取出一個油紙包來交給丁典，道：“我在這世上
的親人，就這麼三個徒兒。他們想奪我一部劍譜，可是沒有劍訣，
那又有什麼用？連城劍法雖然神奇，又怎及得上神照經了？這部神
照經，我送了給你，好好地練罷，此經若然練成，威力奇大，千萬
不可誤傳匪人。”神照經，就是這樣來的。

        學習要求：
                憑機緣向丁典學習
HELP
        );
        return 1;
}
