// xianglong-zhang.c 降龍十八掌
// Last Modified by sega on Mar. 10 2000

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});
mapping *action = ({
([        "action" : "$N雙掌平平提到胸前，神色沉重的緩緩施出"+(order[random(13)])+"「亢龍有悔」"NOR"推向$n的$l",
]),
([        "action" : "$N突然身形飛起，雙掌居高臨下一招"+(order[random(13)])+"「飛龍在天」"NOR"拍向$n的$l",
]),
([        "action" : "$N右掌一招"+(order[random(13)])+"「見龍在田」"NOR"，迅捷無比地劈向$n的$l",
]),
([        "action" : "$N雙掌施出一招"+(order[random(13)])+"「鴻漸于陸」"NOR"，隱隱帶著風聲拍向$n的$l",
]),
([        "action" : "$N左掌聚成拳狀，右掌一招"+(order[random(13)])+"「潛龍勿用」"NOR"緩緩推向$n的$l",
]),
([        "action" : "$N施出一招"+(order[random(13)])+"「利涉大川」"NOR"，右掌插腰，左掌劈向$n的$l",
]),
([        "action" : "$N使出"+(order[random(13)])+"「突如其來」"NOR"，右掌從不可能的角度向$n的$l推出",
]),
([        "action" : "$N大吼一聲，雙掌使出"+(order[random(13)])+"「震驚百裡」"NOR"，不顧一切般擊向$n",
]),
([        "action" : "$N使出"+(order[random(13)])+"「或躍在淵」"NOR"，向$n的$l連拍數掌",
]),
([        "action" : "$N身形滑動，雙掌使一招"+(order[random(13)])+"「雙龍取水」"NOR"一前一後按向$n的$l",
]),
([        "action" : "$N使出"+(order[random(13)])+"「魚躍于淵」"NOR"，身形飛起，雙掌並在一起向$n的$l劈下",
]),
([        "action" : "$N雙掌立起，使出"+(order[random(13)])+"「時乘六龍」"NOR"向$n連砍六下",
]),
([        "action" : "$N使出"+(order[random(13)])+"「密雲不雨」"NOR"，左掌封住$n的退路，右掌斜斜地劈向$l",
]),
([        "action" : "$N使出"+(order[random(13)])+"「損則有孚」"NOR"，雙掌軟綿綿地拍向$n的$l",
]),
([        "action" : "$N腳下一轉，突然欺到$n身前，一招"+(order[random(13)])+"「龍戰于野」"NOR"拍向$n的$l",
]),
([        "action" : "$N門戶大開，一招"+(order[random(13)])+"「履霜冰至」"NOR"向$n的$l劈去",
]),
([        "action" : "$N使出"+(order[random(13)])+"「羝羊觸蕃」"NOR"，雙掌由下往上擊向$n的$l",
]),
([        "action" : "$N左掌護胸，右掌使一招"+(order[random(13)])+"「神龍擺尾」"NOR"上下晃動著擊向$n的$l",
]),
});

int valid_enable(string usage) { return usage=="strike" || usage=="parry"; }

string main_skill() { return "xianglong-zhang"; }

mapping sub_skills = ([
        "kanglong-youhui"  : 150,        // 1
        "feilong-zaitian"  : 150,        // 2
        "jianlong-zaitian" : 150,        // 3
        "hongjian-yulu"    : 150,        // 4
        "qianlong-wuyong"  : 150,        // 5
        "lishe-dachuan"    : 150,        // 6
        "turu-qilai"       : 150,        // 7
        "zhenjing-baili"   : 150,        // 8
        "huoyue-zaiyuan"   : 150,        // 9
        "shuanglong-qushui": 150,        // 10
        "yuyue-yuyuan"     : 150,        // 11
        "shicheng-liulong" : 150,        // 12
        "miyun-buyu"       : 150,        // 13
        "sunze-youfu"      : 150,        // 14
        "longzhan-yuye"    : 150,        // 15
        "lvshuang-bingzhi" : 150,        // 16
        "diyang-chufan"    : 150,        // 17
        "shenlong-baiwei"  : 150,        // 18
]);
int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        if( query("character", me) == "陰險姦詐" )
        {
                tell_object(me, "你演練完畢，發現此套掌法似乎跟自己的性格"
                                "不合，難于修煉。\n");
                return 0;
        }

        if( query("gender", me) == "無性" )
        {
                tell_object(me, "你演練完畢，只覺體內真氣陰陽不調，運功之"
                                "下幾欲昏厥。\n");
                return 0;
        }

        if( query("str", me)<36 )
        {
                tell_object(me, "你演練完畢，只覺手臂又酸又軟，痛得幾乎抬"
                                "不起來。\n");
                return 0;
        }

        if( query("con", me)<32 )
        {
                tell_object(me, "你演練完畢，就覺得眼前金星亂冒，太陽穴突"
                                "突的跳。\n");
                return 0;
        }

        if ((int)me->query_skill("force") < 300)
        {
                tell_object(me, "你演練完畢，幾乎虛脫，看來自身內功水平還"
                                "有待提高。\n");
                return 0;
        }

        if( query("max_neili", me)<3000 )
        {
                tell_object(me, "你演練完畢，丹田提不起半點力來，看來應該"
                                "繼續鍛煉內力。\n");
                return 0;
        }

        if (random(30) <= 28)
        {
                tell_object(me, "你對十八掌的奧妙頗有領悟，或許再演練幾次"
                                "就能融會貫通。\n");
                return 0;
        }

        tell_object(me, HIY "你一氣呵成，將十八掌從頭到尾演練了一變，心中"
                        "頓悟，通\n曉了降龍十八掌的奧妙精髓，融會貫通了掌"
                        "法的精微之處，\n再也非拆開使用那麼那麼簡單。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
int valid_learn(object me)
{
        if( query("character", me) == "陰險姦詐" )
                return notify_fail("你心中暗想：這武功難練得緊，學它做甚？\n");

        if( query("str", me)<36 )
                return notify_fail("你的先天膂力孱弱，難以修煉降龍十八掌。\n");

        if( query("con", me)<32 )
                return notify_fail("你的先天根骨孱弱，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("force") < 300)
                return notify_fail("你的內功火候不夠，難以修煉降龍十八掌。\n");

        if( query("max_neili", me)<3000 )
                return notify_fail("你的內力修為不足，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("strike", 1) < 180)
                return notify_fail("你的基本掌法火候不夠，難以修煉降龍十八掌。\n");

        if ((int)me->query_skill("strike", 1) < (int)me->query_skill("xianglong-zhang", 1))
                return notify_fail("你的基本掌法水平有限，難以領會更高深的降龍十八掌。\n");

        return 1;
}
int practice_skill(object me)
{
        if (!valid_learn(me)) return 0;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<100 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<40 )
                return notify_fail("你的內力不夠練降龍十八掌。\n");
        me->receive_damage("qi", 100);
        addn("neili", -40, me);
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
        int d_e1 = -60;
        int d_e2 = -40;
        int p_e1 = -20;
        int p_e2 = 10;
        int f_e1 = 520;
        int f_e2 = 640;
        int i, lvl, seq, ttl = sizeof(action);

        lvl = (int) me->query_skill("xianglong-zhang", 1);
        seq = random(ttl);       /* 選擇出手招數序號 */
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

        lvl = me->query_skill("xianglong-zhang", 1);

        if (damage_bonus < 100 || lvl < 150) return 0;

        if (damage_bonus > victim->query_con())
        {
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);

                return random(2) ? HIR "只聽$n" HIR "前胸「□嚓」一聲脆響，竟像是"
                                   "肋骨斷折的聲音。\n" NOR:

                                   HIR "$n" HIR "一聲慘叫，胸前「□嚓□嚓」幾聲脆"
                                   "響，口中鮮血狂噴。\n" NOR;
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me)
{
        if (me->query_skill("huntian-qigong",1) >= 10)        return 0.8;
        else return 1.0;
}

string perform_action_file(string action)
{
        return __DIR__"xianglong-zhang/" + action;
}
int help(object me)
{
        write(HIC"\n降龍十八掌："NOR"\n");
        write(@HELP

    降龍十八掌是丐幫鎮幫之寶，是天下最剛猛的武功。

        學習要求：
                自行演練，將十八路掌法合而為一
                內力3000
                先天臂力25
                先天根骨20
                基本掌法180
                基本掌法不低于降龍掌
HELP
        );
        return 1;
}
