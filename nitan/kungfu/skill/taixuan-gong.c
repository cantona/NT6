// taixuan-gong.c 俠客島太玄功
// Last Modified by winder on Mar. 10 2000

#include <ansi.h>;
inherit FORCE;
string type() { return "martial"; }
string martialtype() { return "force"; }

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 10; }
int power_point(object me) { return 1; }
int valid_force(string force) { return 1; }
string *dodge_msg = ({
        "$n體內太玄真氣迸發，忽見$n左手拍出，勁風到處，把$N震到一邊。\n",
        "$n手臂迴轉，抓住$N手肘一推，將$N遠遠擲開。\n",
        "$n默唸太玄口訣，兩腿輕蹬，激躍而出，竟已落在十數丈外。\n",
        "$N只覺眼前一花，只見到$n身形一幌，自己的招數居然莫名其妙就落空了。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("taixuan-gong", 1);
        return lvl * lvl * 15 / 100 / 10;
}
mapping *actionf = ({
([      "action":"$N雙手一舉，一股勁氣澎湃洶湧而來，逼得$n踉踉後退",
        "force" : 540,
        "attack": 220,
        "dodge" : 120,
        "parry" : 120,
        "damage": 155,
        "damage_type":  "瘀傷"
]),
([      "action":"$N右手伸出，霎時一股氣流激射而出襲向$n",
        "force" : 560,
        "attack": 240,
        "dodge" : 60,
        "parry" : 90,
        "damage": 230,
        "damage_type":  "瘀傷"
]),
([      "action":"$N大喝一聲，左掌一抖，頓時一股氣流向$n臉上湧去",
        "force" : 570,
        "attack": 235,
        "dodge" : 155,
        "parry" : 135,
        "damage": 260,
        "damage_type":  "瘀傷"
]),
([      "action":"$N猱身而上，全身真氣暴發，雙掌猛地拍向$n",
        "force" : 580,
        "attack": 250,
        "dodge" : 120,
        "parry" : 75,
        "damage": 295,
        "damage_type":  "瘀傷"
]),
([      "action":"$N身法陡快，忽左忽又，突然間$N雙掌連連拍出，數股太玄內勁已射向$n",
        "force" : 580,
        "attack": 265,
        "dodge" : 140,
        "parry" : 125,
        "damage": 260,
        "damage_type":  "瘀傷"
]),
([      "action":"$N突然間左手一捺，封住$n退路，右手掌力洶湧而出",
        "force" : 580,
        "attack": 280,
        "dodge" : 125,
        "parry" : 145,
        "damage": 380,
        "damage_type":  "瘀傷"
]),
});

mapping *actionw = ({
([      "action" : "$N攻勢如虹，氣勢非凡，$w忽隱忽現，捉摸不定向$n慢慢攻去",
        "force" : 510,
        "attack": 180,
        "dodge" : 115,
        "parry" : 125,
        "damage": 325,
        "damage_type": "內傷"
]),
([      "action":"$N手中的$w龍吟不定，猶如長江滾滾而來，將$n籠罩",
        "force" : 510,
        "attack": 188,
        "dodge" : 112,
        "parry" : 115,
        "damage": 310,
        "damage_type": "刺傷"
]),
([      "action":"$N捲起手中的$w，宛如翻江倒海直射向$n而去",
        "force" : 532,
        "attack": 225,
        "dodge" : 120,
        "parry" : 102,
        "damage": 365,
        "damage_type": "刺傷"
]),
([      "action":"$N手中$w幻出一個個光環，頓時將$n團團包圍",
        "force" : 565,
        "attack": 210,
        "dodge" : 115,
        "parry" : 105,
        "damage": 390,
        "damage_type": "內傷"
]),
([      "action":"$N飛身而起，手中$w猶如神龍般地卷向$n",
        "force" : 550,
        "attack": 248,
        "dodge" : 110,
        "parry" : 120,
        "damage": 420,
        "damage_type": "刺傷"
]),
});

mapping *actionbad = ({
([      "action" : "$N正欲施招，卻又突然覺得好像忘記了招式，只好胡亂使出。",
        "force" : 10,
        "attack": 10,
        "dodge" : -10,
        "parry" : -10,
        "damage": 10,
        "damage_type": "內傷"
]),
});
mapping *action = ({
([      "action":"$N雙手一舉，一股勁氣澎湃洶湧而來，逼得$n踉踉後退",
        "lvl": 0
]),
([      "action":"$N右手伸出，在$n臂膀上迅速無比的一按，$n一跤跌了出去",
        "lvl": 10
]),
([      "action":"$N大喝一聲，張口一股內氣向$n臉上噴去",
        "lvl": 20
]),
([      "action":"$N猱身而上，雙掌猛地拍向$n",
        "lvl": 30
]),
([      "action":"$N身體微側，突然飛起一腳，踢向$n下三路。腳到中途，猛地一抬，踢向$n面門",
        "lvl": 40
]),
([      "action":"$N突然間左手一捺，封住$n退路，右手掌力洶湧而出",
        "lvl": 50
]),
});

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = 10;
        int f_e1 = 440;
        int f_e2 = 600;
        int i, lvl, seq, ttl;

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return actionbad[0];

        if( random(me->query_skill("taixuan-gong",1))>220 && query("neili", me)>100 )
        {
                addn("neili", -50, me);
                return ([
        "action": HIR "$N的心中突然一片茫然，只覺得經脈中象有無數的蝌蚪在串來串去，難過非常，
當下不及多想，順着蝌蚪的走向一陣拳打腳踢！四周頓時勁風亂颮，好不熱鬧！"NOR,
        "damage": 1000,
        "parry" : -180,
        "dodge" : -140,
        "force" : 1000,
        "damage_type": "瘀傷"]);
        }
        lvl = (int) me->query_skill("taixuan-gong", 1);

        if( weapon )
                ttl = sizeof(actionw);
        else
                ttl = sizeof(actionf);

        for(i = ttl; i > 0; i--)
                if(lvl > action[i-1]["lvl"])
                {
                        seq = i; /* 獲得招數序號上限 */
                        break;
                }
        seq = random(seq);       /* 選擇出手招數序號 */
        return ([
                "action"      : (weapon ? actionw[seq]["action"] : actionf[seq]["action"]),
                "dodge"       : d_e1 + (d_e2 - d_e1) * seq / ttl,
                "parry"       : p_e1 + (p_e2 - p_e1) * seq / ttl,
                "force"       : f_e1 + (f_e2 - f_e1) * seq / ttl,
                "damage_type" : random(2) ? "內傷" : "瘀傷",
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}
int valid_enable(string usage)
{
        object me = this_player();

        if (! me)
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry" || usage == "sword";
        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
                return usage == 0;

        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
                return usage == "force" || usage == "unarmed"
                || usage == "dodge" || usage == "parry";
        else
        if (me->query_skill("sword", 1) < me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) < me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage == "parry";

        else
        if (me->query_skill("sword", 1) < me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) > me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry";

        else
        if (me->query_skill("sword", 1) > me->query_skill("taixuan-gong", 1)
            && me->query_skill("blade", 1) < me->query_skill("taixuan-gong", 1))
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="sword" || usage == "parry";

        else
                return usage == "force" || usage == "unarmed" || usage == "dodge"
                || usage =="blade" || usage == "parry" || usage == "sword";

}

int double_attack() { return 1; }
mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp;
        int cost;

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return;

        if ((int)me->query_skill("taixuan-gong", 1) < 150
           || me->query_skill_mapped("parry") != "taixuan-gong"
           || me->query_skill_mapped("force") != "taixuan-gong"
           || me->query_skill_mapped("unarmed") != "taixuan-gong"
           || query("neili", me)<500
           || ! living(me))
                return;

        cost = damage / 2;

        if (cost > 100) cost = 100;

        ap=ob->query_skill("force")*12+query("max_neili", ob)+
             ob->query_skill("count", 1) * 6;
        dp=me->query_skill("force")*12+query("neili", me);

        if (ap / 3 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(2))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默唸太玄功口訣，太玄內"
                                            "勁齊聚於全身，$N" HIR "只覺這招攻在"
                                            "$n" HIR "身上，猶如碰到銅牆鐵壁一般，"
                                            "絲毫不起作用。\n"NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招擊中$n" HIR "上身"
                                            "，可卻猶如擊在銅牆鐵壁上一般，力道頓時"
                                            "消失得無影無蹤。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "但見$n" HIR "一聲輕嘯，渾若無事"
                                            "的接下了$N" HIR "這一招，卻沒有受到"
                                            "半點傷害。\n" NOR]);
                        break;
                }
                return result;
        }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        mixed result;
        string msg;
        int lvl;
        object weapon=query_temp("weapon", me);

        lvl = me->query_skill("taixuan-gong", 1);

        if( !query("reborn/times", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return 0;

        if (damage_bonus < 100
           || lvl < 140
            || query("neili", me)<300
           || me->query_skill_mapped("force") != "taixuan-gong")
                return 0;

        // 未學會駕御兵器
        if( !query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                      return 0;
        }

        // 已經會駕御兵器
        if( query("can_learned/taixuan-gong/enable_weapon", me) )
        {
             if (! objectp(weapon))
                  if (me->query_skill_prepared("unarmed") != "taixuan-gong")
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) != "sword"
                  && query("skill_type", weapon) != "blade" )
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) == "sword"
                 && me->query_skill_mapped("sword") != "taixuan-gong")
                         return 0;

             if( objectp(weapon) && query("skill_type", weapon) == "blade"
                 && me->query_skill_mapped("blade") != "taixuan-gong")
                         return 0;
        }

        // if (random(2) == 1)return 0;

        damage_bonus += factor; // 加力效果體現
        if (damage_bonus / 2 > victim->query_con()/10)
        {
                addn("neili", -100, me);
                result = ([ "damage" : damage_bonus ]);
                // victim->receive_wound("qi", (damage_bonus - 76) / 2, me);
                // victim->add("neili", -((damage_bonus - random(70)) / 2), me);

                if( query("can_learned/taixuan-gong/enable_weapon", me) && objectp(weapon) )
                {
                        msg = random(2) ? HIM "$N" HIM "一招攻出，竟捲起千層氣浪，太玄內勁"
                                           "頓時源源不絕透過" + weapon->name() + HIM "湧入$n" HIM "體"
                                           "內！\n" NOR:
                                           HIM "$N" HIM "太玄內勁迸發，$n" HIM "只感全身一震，登時一"
                                           "股灼熱之氣透胸而過，" + weapon->name() + HIM "鮮血淋漓！\n" NOR;
                } else
                {
                        msg = random(2) ? HIW "$N" HIW "一招攻出，竟捲起千層氣浪，太玄內勁"
                                           "頓時源源不絕湧入$n" HIW "體內！\n" NOR:
                                           HIW "$N" HIW "太玄內勁迸發，$n" HIW "只感全身一"
                                           "震，登時“喀喀喀”斷了數根肋骨！\n" NOR;
                }
                result += ([ "msg" : msg ]);
                return result;
        }
}
int practice_skill(object me)
{
        return notify_fail("太玄功只能用學(learn)的來增加熟練度。\n");
}

int valid_learn(object me)
{
        int level;

        if( !query("jieti", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
                return notify_fail("你覺得太玄神功深奧之極，一時間難以領會。\n");

        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的太玄功。\n");

        if( query("int", me)<27 )
                return notify_fail("你若有所悟，然而總是有點不明白。\n");

        if( query("dex", me)<27 )
                return notify_fail("你研究了半天，只覺招式始終無法隨意施展。\n");

        if( query("con", me)<27 )
                return notify_fail("你研究了半天，只覺得根骨有些差，招式始終無法隨意施展。\n");

        if( query("str", me)<27 )
                return notify_fail("你研究了半天，感覺膂力有些低，始終無法隨意施展。\n");


        level = me->query_skill("taixuan-gong", 1);

        if (me->query_skill("force", 1) < level)
                return notify_fail("你對基本內功的理解還不夠，無法繼續領會更"
                                   "高深的太玄功。\n");

        if (me->query_skill("unarmed", 1) < level)
                return notify_fail("你對基本拳腳的理解還不夠，無法繼續領會更"
                                   "高深的太玄功。\n");

        return ::valid_learn(me);
}

int get_ready(object me)
{
        return 1;
}

int difficult_level()
{
        return 1000;
}

string perform_action_file(string action)
{
        object me = this_player();

        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return "學過讀書寫字再也無法施展太玄功。";

        return __DIR__"taixuan-gong/perform/" + action;
}

string exert_function_file(string action)
{
        object me = this_player();

        if( !query("reborn", me) && (me->query_skill("literate",1 )
             || query("learned_literate", me)) )
               return "學過讀書寫字再也無法施展太玄功。";

        return __DIR__"taixuan-gong/exert/" + action;
}

int help(object me)
{
        write(HIC"\n太玄功："NOR"\n");
        write(@HELP

    太玄功源自俠客島上洞壁武功。

        學習要求：
                各人自己的福緣
HELP
        );
        return 1;
}
