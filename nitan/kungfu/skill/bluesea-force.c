// bluesea-force.c 南海玄功

#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        "$n暗運內力，$N的進攻就如擊到氣牆上，沒有半點效果。\n",
        "$n大喝一聲，一股氣流直沖而出，硬生生震退了$N。\n",
        "$n身子一轉，一股旋風將$N的招數全部化解。\n",
        "$n哼然冷笑，微微移動，內力回旋使$N的進攻差之毫厘。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("bluesea-force", 1);
        return lvl * lvl * 20 * 15 / 100 / 200;
}

mapping *actionf = ({
([      "action":"$N跨出一步，一指緩緩戳向$n的$l，籠罩了方圓數寸的范圍",
        "force" : 500,
        "attack": 150,
        "dodge" : 90,
        "parry" : 88,
        "damage": 170,
        "damage_type":  "刺傷"
]),
([      "action":"$N一聲震喝，隨即一掌劈出，中途卻忽然一指刺向$n的$l",
        "force" : 510,
        "attack": 165,
        "dodge" : 110,
        "parry" : 90,
        "damage": 160,
        "damage_type":  "刺傷"
]),
([      "action":"$N疾走數步，左掌掌劈向$n的肩頭，右手食卻點向$n的$l，",
        "force" : 515,
        "attack": 155,
        "dodge" : 85,
        "parry" : 85,
        "damage": 175,
        "damage_type":  "刺傷"
]),
([      "action":"$N深吸一口氣，步步進逼，雙掌連環劈向$n的$l",
        "force" : 520,
        "attack": 140,
        "dodge" : 80,
        "parry" : 90,
        "damage": 180,
        "damage_type":  "瘀傷"
]),
([      "action":"$N身體原地不動，雙掌平推，一股掌力凌空奔$n而去",
        "force" : 535,
        "attack": 135,
        "dodge" : 80,
        "parry" : 95,
        "damage": 170,
        "damage_type":  "內傷"
]),
([      "action":"$N足下暗和八卦，步法變幻莫測，左右掌連翻出擊，攻向$n",
        "force" : 500,
        "attack": 150,
        "dodge" : 85,
        "parry" : 115,
        "damage": 165,
        "damage_type":  "震傷"
]),
});

mapping *actionw = ({
([      "action":"$N跨出一步，手中$w緩緩砸向$n，籠罩了方圓數寸的范圍",
        "force" : 450,
        "attack": 170,
        "dodge" : 100,
        "parry" : 110,
        "damage": 200,
        "damage_type":  "震傷"
]),
([      "action":"$N一聲震喝，手中的$w隨即橫掃$n，中途卻忽然刺向$n的$l",
        "force" : 460,
        "attack": 165,
        "dodge" : 80,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "刺傷"
]),
([      "action":"$N疾走數步，左掌掌劈向$n的肩頭，右手的$w卻點向$n的$l，",
        "force" : 480,
        "attack": 175,
        "dodge" : 85,
        "parry" : 100,
        "damage": 210,
        "damage_type":  "刺傷"
]),
([      "action":"$N深吸一口氣，步步進逼，手中的$w連環劈向$n的$l",
        "force" : 475,
        "attack": 180,
        "dodge" : 75,
        "parry" : 120,
        "damage": 205,
        "damage_type":  "瘀傷"
]),
([      "action":"$N身體原地不動，手中的$w一劃，一股內力凌空奔$n而去",
        "force" : 480,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 210,
        "damage_type":  "割傷"
]),
([      "action":"$N足下暗合八卦，步法變幻莫測，手中的$w化作數道光芒，攻向$n",
        "force" : 490,
        "dodge" : 160,
        "parry" : 110,
        "damage": 220,
        "damage_type":  "內傷"
]),
});

string *usage_skills = ({ "finger", "strike", "staff", "dodge",
                          "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int valid_combo(string combo)
{
        return combo == "bluesea-force" ||
               combo == "tanzhi-shentong";
}

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
/* d_e=dodge_effect p_e=parry_effect f_e=force_effect m_e=damage_effect */
        int d_e1 = -80;
        int d_e2 = -100;
        int p_e1 = -80;
        int p_e2 = -100;
        int f_e1 = 450;
        int f_e2 = 630;
        int m_e1 = 440;
        int m_e2 = 540;
        int i, lvl, seq, ttl;
        mapping *action;

        if (objectp(weapon))
                action = actionw;
        else
                action = actionf;

        ttl = sizeof(action);
        lvl = (int) me->query_skill("bluesea-force", 1);
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
                "damage_type" : action[seq]["damage_type"],
        ]);
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("combat_exp", me)<3000000 )
                return notify_fail("你覺得南海玄功深奧之極，"
                                   "憑自己的戰鬥經驗一時間難以領會。\n");

        if ((int)me->query_skill("martial-cognize", 1) < 50)
                return notify_fail("你覺得南海玄功過于深奧之極，以"
                                   "自己的武學修養全然無法明白。\n");

      if( query("character", me) != "心狠手辣" && 
          query("character", me) != "國士無雙" )
                return notify_fail("你發覺南海神功招招狠、式式險，舍"
                                   "生忘死，自己實在領會不了。\n");

        if( query("con", me)<22 && me->query_con()<63 )
                return notify_fail("你試圖運用真力修煉南海玄功，卻突"
                                   "然覺得眼前一黑，看來是根骨不好，"
                                   "不能勉強修行。\n");

        if( query("gender", me) == "無性" && 
            (int)me->query_skill("bluesea-force", 1) > 219)
                return notify_fail("你無根無性，陰陽不調，難以領會高深的南海玄功。\n");

        level = me->query_skill("bluesea-force", 1);

        if ((int)me->query_skill("martial-cognize", 1) < level)
                return notify_fail("你覺得自己的武學修養有限，難以領會更高深的南海玄功。\n");

        for (i = 0; i < sizeof(usage_skills); i++)
                if (me->query_skill(usage_skills[i], 1) < level)
                        return notify_fail("你對" + to_chinese(usage_skills[i]) +
                                           "的理解還不夠，無法繼續領會更高深的南海玄功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("南海玄功博大精深，無法簡單的通過練習進步。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;

        if ((int)me->query_skill("bluesea-force", 1) < 200
         || !living(me) || query("neili", me)<500
        ||  me->query_skill_mapped("parry") != "bluesea-force")
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("bluesea-force", 1);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -300, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIB "$n" HIB "默運南海玄功，真氣護住全身。$N" HIB
                                            "一招擊中$n" HIB "，只覺落手處勁力石沉大海，"
                                            "大感驚訝，連忙退回。 \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIB "$N" HIB "一招攻出，$n" HIB "怒吼一聲，不退"
                                            "反進，巨濤般的氣牆竟將$N" HIB "這招逼回。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIB "$n" HIB "全身真氣流動，一股罡氣護住全身，已將$N" HIB "所"
                                            "有進攻招式擋在罡氣之外。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "默運南海玄功，護住全身。但是$N" HIY
                                 "內力深厚無比，冷笑一聲，一招竟結實地打在$n" HIY
                                 "身上。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "不退反進，試圖將$N" HIY "的招式逼回。但是"
                                 "$N" HIY "招式陡然一變，$n" HIY "頓時一驚，卻已然中招。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "一股護體罡氣欲將$N" HIY "的進攻"
                                 "招式封死。但是$N" HIY "早已看去其中玄虛，冷笑一聲，$N" HIY
                                 "卻已中招。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
            || query("neili", me)<200
           || me->query_skill("bluesea-force", 1) < 250)
                return 0;


        if (damage_bonus / 2 > victim->query_con())
        {
                addn("neili", -100, me);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                addn("neili", -((damage_bonus-random(80))/2), victim);

                return random(2) ? HIR "$N" HIR "灌注全身勁力如南海巨濤般襲向$n" HIR "周身大穴，$n" HIR "根本無法抵擋，立受內傷，鮮血狂吐！" NOR:
                                   HIR "$n" HIR "硬接$N" HIR "一招，不想對方內力如海浪般襲來，$n" HIR "猛的吐出一口鮮血，看來已受內傷！\n" NOR;
        }
}

int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"bluesea-force/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"bluesea-force/exert/" + action;
}
