// This program is a part of NT MudLIB
// jiuyang-shengong.c 九陽神功

#include <ansi.h>;

inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }
int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyang-shengong", 1);
        return lvl / 10 * lvl / 10 * 15 * 28 / 10 / 20;
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }

mapping *actionf = ({
([      "action": "$N飛身一躍而起，身法陡然加快，朝着$n$l快速攻出數十拳",
        "force" : 510,
        "attack": 190,
        "dodge" : -100,
        "parry" : -90,
        "damage": 180,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action": "$N沉身運氣，一拳擊向$n，剎那間，$N全身竟浮現出一道金光",
        "force" : 510,
        "attack": 185,
        "dodge" : -90,
        "parry" : -120,
        "damage": 175,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action": "$N將九陽神功運勁於臂，一掌凌空劈斬而出，劃出一道熾熱的黃芒",
        "force" : 530,
        "attack": 175,
        "dodge" : -90,
        "parry" : -110,
        "damage": 200,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "割傷"
]),
([      "action": "$N跨步上前，身形微微一展，雙掌對準$n$l一併攻出",
        "force" : 525,
        "attack": 185,
        "dodge" : -85,
        "parry" : -115,
        "damage": 185,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action": "$N急催九陽神功內勁，猛的一拳在呼嘯聲中陡然揮擊而出",
        "force" : 530,
        "attack": 165,
        "dodge" : -90,
        "parry" : -115,
        "damage": 200,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action": "$N一聲暴喝，十指暮的張開，一股雄厚的內勁澎湃而出",
        "force" : 540,
        "attack": 200,
        "dodge" : -115,
        "parry" : -120,
        "damage": 180,
        "weapon": HIR "九陽無極勁" NOR,
        "damage_type":  "割傷"
]),
});

mapping *actionw = ({
([      "action" : "$N攻勢忽緩而不疏，$w變化無常，捉摸不定向$n慢慢捲去",
        "force" : 330,
        "attack": 140,
        "dodge" : -35,
        "parry" : -85,
        "damage": 325,
        "damage_type": "內傷"
]),
([      "action":"$N手中的$w突煥氣象森嚴，便似千軍萬馬奔馳而來，$w幻作一道紅芒貫向$n",
        "force" : 310,
        "attack": 120,
        "dodge" : -25,
        "parry" : -25,
        "damage": 310,
        "damage_type": "刺傷"
]),
([      "action":"$N捲起手中的$w，霎時劍芒暴漲，宛如驕陽烈火直射向$n而去",
        "force" : 340,
        "attack": 115,
        "dodge" : -20,
        "parry" : -25,
        "damage": 365,
        "damage_type": "刺傷"
]),
([      "action":"$N運用$w幻化做一個一個圓圈，頓時無數火圈將$n團團包圍",
        "force" : 285,
        "attack": 110,
        "dodge" : -25,
        "parry" : -25,
        "damage": 390,
        "damage_type": "內傷"
]),
([      "action":"$N迴轉$w遙指$n，頓時$w頂端頓時透出一道吞吐不定的火光，電射而出",
        "force" : 330,
        "attack": 118,
        "dodge" : -10,
        "parry" : -20,
        "damage": 420,
        "damage_type": "刺傷"
]),
});

string main_skill() { return "jiuyang-shengong"; }

mapping sub_skills = ([
        "wudang-jiuyang"   : 180,
        "shaolin-jiuyang"  : 180,
        "emei-jiuyang"     : 180,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        /*
        if (query("character", me) != "光明磊落" &&
            query("character", me) != "心狠手辣" &&
            query("character", me) != "國士無雙")
        {
                tell_object(me, "你發現你的天性不太適合學習九陽神功！\n");
                return 0;
        }
        */

        if (me->query_skill("yinyang-shiertian", 1))
        {
                tell_object(me, "你演練完畢，發現自從通曉陰陽十二重天后，再"
                                "分開修煉已全然無用。\n");
                return 0;
        }

        if (query("gender", me) == "無性")
        {
                tell_object(me, "你演練完畢，只感氣血上湧，看來自己陰陽不調"
                                "，無法學此奇功。\n" NOR);
                return 0;
        }

        if (query("int", me) < 30)
        {
                tell_object(me, "你演練完畢，只感三種九陽神功毫無牽連，看來"
                                "依你的悟性，無法將其合一。\n");
                return 0;
        }

        if (query("con", me) < 32)
        {
                tell_object(me, "你演練完畢，發現自己的先天根骨太差，無法將"
                                "三種九陽神功合一。\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 200)
        {
                tell_object(me, "你覺得自己基本內功修為太淺，看來暫且無法將"
                                "三種九陽神功合一。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 100)
        {
                tell_object(me, "你演練完畢，發現自己的武學修養尚待提高，暫"
                                "且無法將三種九陽神功合一。\n");
                return 0;
        }

        if ((int)query("max_neili", me) < 3500)
        {
                tell_object(me, "你覺得自己的內力修為太淺，無法將三種九陽神"
                                "功合一。\n");
                return 0;
        }

        if (random(10) < 8)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通"
                                "，將二者合一。\n");
                return 0;
        }

        tell_object(me, HIW "一陣凡塵往事湧上心頭，你幾欲放聲長歎。霎那間，"
                        "你放眼回首，竟有一股莫名\n的悲哀。宗師泰斗那種高出"
                        "不勝寒、登泰山而小天下之感猶然而生，你只覺得以\n往"
                        "的武學現在看來是多麼的渺小可笑。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        object me = this_player();

        if (!query("can_learn/jiuyang-shengong/enable_weapon", me))
                return usage == "force" || usage == "unarmed" || usage == "parry";
        else
                return usage == "force" || usage == "unarmed" || usage =="parry"
                    || usage == "sword" || usage =="blade";

}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

int valid_learn(object me)
{
        int level;
        int i;

        /*
        if (query("character", me) != "光明磊落" &&
            query("character", me) != "心狠手辣" &&
            query("character", me) != "國士無雙")
        {
                tell_object(me, "你發現你的天性不太適合學習九陽神功！\n");
                return 0;
        }
        */

        if ((int)me->query_skill("yinyang-shiertian", 1))
                return notify_fail("你已將九陽神功融匯貫通，合成了普天之下最"
                                   "強的武功，不必再分開學習了。\n");

        if( (!query("family/family_name", me) ||
            me->query_family() != "明教") && (!query("reborn/times", me) || member_array("明教", query("reborn/fams", me)) == -1) )
                return notify_fail("你沒有經過張教主的指點，難以理解。\n");

          if (query("gender", me) == "無性")
                return notify_fail("你無根無性，陰陽不調，難以領會高深的九陽"
                                   "神功。\n");

          if (query("int", me) < 30)
                return notify_fail("你覺得九陽神功過於艱深，難以理解。\n");

          if (query("con", me) < 32)
                return notify_fail("你的先天根骨孱弱，無法運轉九陽神功。\n");

        if ((int)query("max_neili", me) < 3500)
                return notify_fail("你的內力修為太淺，無法運轉九陽神功。\n");

        level = me->query_skill("jiuyang-shengong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 100)
                return notify_fail("你覺得九陽神功過於深奧，以自己的武學修養"
                                   "全然無法明白。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的基本內功修為不足，難以運轉九陽神功。\n");

        if (me->query_skill("force", 1) < level)
                return notify_fail("你對基本內功的理解還不夠，無法繼續領會更"
                                   "高深的九陽神功。\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("你對基本拳腳的理解還不夠，無法繼續領會更"
                                   "高深的九陽神功。\n");

        if (query("can_learn/jiuyang-shengong/enable_weapon", me) &&
            me->query_skill("sword", 1) < level &&
            me->query_skill("blade", 1) < level)
                return notify_fail("你對刀劍功夫的理解還不夠，無法繼續領會更"
                                   "高深的九陽神功。\n");

        if (!query("can_learn/jiuyang-shengong/enable_weapon", me))
        {
                write(HIG "你學會了利用九陽神功駕御兵器！\n");
                set("can_learn/jiuyang-shengong/enable_weapon", 1, me);
        }

        return 1;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if ((int)me->query_skill("jiuyang-shengong", 1) < 150
           || me->query_skill_mapped("parry") != "jiuyang-shengong"
           || me->query_skill_mapped("force") != "jiuyang-shengong"
           || me->query_skill_mapped("unarmed") != "jiuyang-shengong"
           || (int)query("neili", me) < 500
           || (query_temp("weapon", ob) && me->query_skill("force-cognize", 1) < 2000)
           || ! living(me))
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force") * 12 + query("max_neili", ob) + ob->query_skill("count", 1) * 12;
        dp = me->query_skill("force") * 12 + query("neili", me);

        if (ap / 3 + random(ap/2) < dp) // 提高防禦的能力
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默唸九陽神功總訣，收斂"
                                            "內勁，承下$N" + HIR "這一招，$N" HIR
                                            "只覺猶如石沉大海，絲毫不起作用。\n"
                                            NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招擊中$n" HIR "上身"
                                            "，可卻猶如擊在棉花上一般，力道頓時"
                                            "消失得無影無蹤。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "但見$n" HIR "微微一笑，渾若無事"
                                            "的接下了$N" HIR "這一招，卻沒有受到"
                                            "半點傷害。\n" NOR]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        int lvl;

        lvl = me->query_skill("jiuyang-shengong", 1);

        if (damage_bonus < 150
           || lvl < 150
           || query("neili", me) < 300
           || me->query_skill_mapped("force") != "jiuyang-shengong"
           || me->query_skill_mapped("unarmed") != "jiuyang-shengong"
           || me->query_skill_prepared("unarmed") != "jiuyang-shengong")
                return 0;

        damage_bonus += factor; // 加力效果體現
        if (damage_bonus/2 > victim->query_con()/10) // 提高攻擊能力
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", damage_bonus, me);
                return random(2) ? HIR "只見$N" HIR "九陽內勁自體內迸發，真氣隨招式"
                                   "而盪漾，摧毀了$n" HIR "的真元！\n" NOR:

                                   HIR "$N" HIR "九陽神功的潛力發揮了出來，突然間$n"
                                   HIR "只感喉嚨一甜，噴出一口鮮血！\n" NOR;
        }
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("jiuyang-shengong", 1);
        if (lvl < 150) return 0;
        if (lvl < 200) return 50;
        if (lvl < 250) return 60;
        if (lvl < 300) return 70;
        if (lvl < 350) return 80;
        if (lvl < 400) return 90;
        return 100;
}

int practice_skill(object me)
{
        return notify_fail("九陽神功只能用學(learn)的來增加熟練度。\n");
}

int difficult_level()
{
        return 700;
}

string perform_action_file(string action)
{
        return __DIR__"jiuyang-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyang-shengong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n九陽神功："NOR"\n");
        write(@HELP

    九陽神功來自《九陽真經》。
    在少林寺中的一部《楞伽經》中的夾縫之中，達摩祖師親手書
寫的一部經書，稱為《九陽真經》。《九陽真經》中記着許多強身
健體、易筋洗髓的法門，覺遠大師依此練習。後瀟湘子和尹克西盜
得此書，為逃避追繳，置入猿腹。直到百年之後，方被張無忌在昆
侖仙境的白猿腹中偶然取得，九陽神功才重見天日。

    〖特殊功效〗

        學習要求：
                基本內功200級
HELP
        );
        return 1;
}
