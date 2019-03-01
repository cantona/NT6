// jiuyin-shengong.c 九陰神功
// 九陰白骨爪、催心掌、大伏魔拳法、銀龍鞭法、蛇行貍翻以及易筋鍛骨合為一體所出，S級武學。
// 九陰神功可以激發為基本拳腳、爪法、拳法、掌法、手法、鞭法、輕功和內功。
// Edit By Vin On 14/2/2001 
// modify by Rcwiz for yhonline 18/3/2003

#include <ansi.h>

inherit FORCE;

string *dodge_msg = ({
        "$n動也不動，把$N震到一邊。\n",
        "$n身形微微一抖，將$N迫退。\n",
        "$n手足忽的一晃，$N竟然無法進擊，只能自保。\n",
        "$n輕輕一格，將天下所有進攻招數全部封死。\n",
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * lvl * 22 * 15 / 100 / 200;
}

int query_jingli_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("jiuyin-shengong", 1);
        return lvl * 14 / 5;
}

mapping *actionf = ({
([      "action":"$N伸手一探，頓時氣流呼嘯而至，單手毫無花巧的插向$n$l",
        "force" : 510,
        "attack": 190,
        "dodge" : 100,
        "parry" : 90,
        "damage": 180,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N雙手齊抓，幻出千萬道耀眼的金光，齊齊照向$n的$l",
        "force" : 510,
        "attack": 185,
        "dodge" : 90,
        "parry" : 120,
        "damage": 175,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N身形一轉，拳頭攜著疾速旋轉的氣流揮出，疾如閃電，勢如雷霆，擊向$n",
        "force" : 530,
        "attack": 175,
        "dodge" : 90,
        "parry" : 110,
        "damage": 200,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "刺傷"
]),
([      "action":"$N移步向前，一掌不緊不慢的拍向$n的$l，空氣中頓時傳來一陣刺耳的暴響",
        "force" : 525,
        "attack": 185,
        "dodge" : 85,
        "parry" : 115,
        "damage": 185,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N身體一側，一掌凌空劈出，一股凜冽的氣流頓時澎湃湧至$n的$l處",
        "force" : 530,
        "attack": 165,
        "dodge" : 90,
        "parry" : 115,
        "damage": 200,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "割傷"
]),
([      "action":"$N雙手合拳，驀的張開，只聽“嗤嗤”破空之聲，十道勁氣一齊射向$n的$l",
        "force" : 540,
        "attack": 200,
        "dodge" : 115,
        "parry" : 120,
        "damage": 280,
        "weapon": HIW "九陰無極勁" NOR,
        "damage_type":  "刺傷"
]),
});

mapping *actionw = ({
([      "action" : "$N攻勢忽緩而不疏，$w變化無常，捉摸不定向$n慢慢卷去",
        "force" : 470,
        "attack": 180,
        "dodge" : 75,
        "parry" : 115,
        "damage": 225,
        "damage_type": "擦傷"
]),
([      "action":"$N手中的$w突煥氣象森嚴，便似千軍萬馬奔馳而來，$w就如棍棒一般橫掃$n",
        "force" : 450,
        "attack": 160,
        "dodge" : 85,
        "parry" : 125,
        "damage": 210,
        "damage_type": "擦傷"
]),
([      "action":"$N卷起手中的$w，就如鐵錘一般對著$n亂砍亂砸，沒有半點章法",
        "force" : 460,
        "attack": 175,
        "dodge" : 80,
        "parry" : 125,
        "damage": 205,
        "damage_type": "割傷"
]),
([      "action":"$N運用$w幻化做一個一個圓圈，似乎要將$n團團包圍",
        "force" : 525,
        "attack": 160,
        "dodge" : 65,
        "parry" : 125,
        "damage": 190,
        "damage_type": "內傷"
]),
([      "action":"$N含笑回轉$w，伸手一指，頗得拈花指之意，點向$n的$l",
        "force" : 540,
        "attack": 180,
        "dodge" : 70,
        "parry" : 120,
        "damage": 260,
        "damage_type": "刺傷"
]),
});

string main_skill() { return "jiuyin-shengong"; }

mapping sub_skills = ([
        "dafumo-quan"      : 230,
        "jiuyin-baiguzhao" : 230,
        "cuixin-zhang"     : 230,
        "shexing-lifan"    : 230,
        "yijin-duangu"     : 230,
        "yinlong-bian"     : 230,
        ]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("gender", me) == "無性" )
        {
                tell_object(me, "你演練完畢，只感氣血上湧，看來自己陰陽不調，無法演練九陰神功。\n" NOR);
                return 0;
        }

        if( query("character", me) == "狡黠多變" )
        {
                tell_object(me, "你演練完畢，覺得九陰神功正大恢弘，氣度儼然，自己怎麼也無法將其合一。\n" NOR);
                return 0;
        }

        if( query("character", me) == "陰險狡詐" )
        {
                tell_object(me, "你演練完畢，覺得九陰神功正大恢弘，氣度儼然，自己怎麼也無法將其合一。\n" NOR);
                return 0;
        }

        if( query("con", me)<34 )
        {
                tell_object(me, "你演練完畢，發現自己的先天根骨太差，無法將九陰真經內的武功合一。\n");
                return 0;
        }

        if( query("str", me)<38 )
        {
                tell_object(me, "你演練完畢，發現自己的先天膂力孱弱，無法將九陰真經內的武功合一。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 250)
        {
                tell_object(me, "你覺得九陰真經內的武功都極其深奧，看來多研究一下學問可能更有幫助。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 250)
        {
                tell_object(me, "你演練完畢，發現自己的武學修養尚待提高，暫且無法將九陰真經內的武功合一。\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你覺得自己真氣不繼，無法繼續演練九陰神功。\n");
                return 0;
        }

        if (random(10) < 8)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通，將二者合一。\n");
                return 0;
        }

        tell_object(me, HIW "一陣凡塵往事湧上心頭，你幾欲放聲長嘆。霎那間，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗師泰鬥那種高出不勝寒、登泰山而小天下之感猶然而生，你只覺得以\n往的"
                        "武學現在看來是多麼的渺小可笑。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

string *usage_mapped_skills = ({ "unarmed", "dodge", "parry", "force" });
string *usage_skills = ({ "unarmed", "strike", "claw", "hand", "cuff", "dodge", "whip", "parry", "force", "finger" });
string *usage_skills2 = ({ "unarmed", "claw", "hand", "dodge", "parry", "force" });

int valid_enable(string usage)
{
        return (member_array(usage, usage_skills) != -1);
}

int valid_force(string force) { return 1; }

int double_attack() { return 1; }

mapping query_action(object me, object weapon)
{
        return weapon ? actionw[random(sizeof(actionw))] :
                        actionf[random(sizeof(actionw))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int valid_learn(object me)
{
        int level;
        int i;

        if( query("character", me) == "狡黠多變" )
                return notify_fail("九陰神功正大恢弘，氣度儼然，你怎麼也學不得神似。\n");

        if( query("character", me) == "陰險狡詐" )
                return notify_fail("九陰神功正大恢弘，氣度儼然，你怎麼也學不得神似。\n");

        if( query("str", me)<22 && me->query_str()<63 )
                return notify_fail("你發現自己的膂力不足，無法將九陰神功運用自如。\n");

//        if (me->query("con") < 34)
//                return notify_fail("你發現自己先天根骨不足，無法運轉九陰神功。\n");

        if( query("gender", me) == "無性" )
                return notify_fail("你無根無性，陰陽不調，難以領會高深的九陰神功。\n");

        level = me->query_skill("jiuyin-shengong", 1);

        if ((int)me->query_skill("martial-cognize", 1) < 150)
                return notify_fail("你覺得九陰神功過于深奧，以自己的武學修養全然無法明白。\n");

        for (i = 0; i < sizeof(usage_skills2); i++)
                if (me->query_skill(usage_skills2[i], 1) < level)
                        return notify_fail("你對" + to_chinese(usage_skills2[i]) +
                                           "的理解還不夠，無法繼續領會更高深的九陰神功。\n");

        return 1;
}

int practice_skill(object me)
{
        return notify_fail("九陰神功博大精深，無法簡單的通過練習進步。\n");
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        int cost;

        if ((int)me->query_skill("jiuyin-shengong", 1) < 150 ||
            !living(me) || query("neili", me)<150 || 
            me->query_skill_mapped("parry") != "jiuyin-shengong" ||
            query_temp("weapon", ob) )
                return;

        cost = damage / 2;
        if (cost > 100) cost = 100;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("jiuyin-shengong", 1);

        if (ap / 2 + random(ap) < dp)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIR "$n" HIR "默運九陰神訣，護住全身。$N" HIR
                                            "一招擊中$n" HIR "小腹，只覺落手處軟"
                                            "綿綿的，力道竟消失得無影無蹤。 \n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIR "$N" HIR "一招攻出，$n" HIR "怒喝一聲，不退"
                                            "反進，竟將$N" HIR "這招逼回。\n" NOR]);
                        break;
                default:
                        result += (["msg" : HIR "$n" HIR "面帶微笑，輕描淡寫間，已將$N" HIR "所"
                                            "有進攻招式全部封死。\n" NOR]);
                        break;
                }
                return result;
        } else
        if (mp >= 100)
        {
                switch (random(3))
                {
                case 0:
                        result = HIY "$n" HIY "默運九陰神訣，護住全身。但是$N" HIY
                                 "內力深厚無比，長嘆一聲，一招竟結實地打在$n" HIY
                                 "身上。\n" NOR;
                        break;
                case 1:
                        result = HIY "$n" HIY "不退反進，試圖將$N" HIY "的招式逼回。但是"
                                 "$N" HIY "招式陡然一變，$n" HIY "頓時一驚，卻已然中招。\n" NOR;
                        break;

                default:
                        result = HIY "$n" HIY "面帶微笑，輕描淡寫間欲將$N" HIY "的進攻"
                                 "招式封死。但是$N" HIY "早已看去其中玄虛，冷笑一聲，$N" HIY
                                 "卻已中招。\n" NOR;
                        break;
                }
                COMBAT_D->set_bhinfo(result);
         }
}


mixed hit_ob(object me, object victim, int damage_bonus)
{
        if( query_temp("weapon", me))return 1;

        if (me->is_busy()
           || random(2) == 0
           || ! living(victim)
           || damage_bonus < 120
            || query("neili", me)<200
           || me->query_skill("jiuyin-shengong", 1) < 250)
                return 0;


        if (damage_bonus / 4 > victim->query_con())
        {
                addn("neili", -100, me);
                victim->receive_wound("qi", (damage_bonus - 88) / 2, me);
                addn("neili", -((damage_bonus - random(80)) / 2), victim);

                return random(2) ? HIR "$N" HIR "招式陡然一變，右手成爪，猛然間抓向$n" HIR "周身大穴。\n" NOR:
                                   HIR "$N" HIR "快步上前，全身真氣貫于左手食指，猛地刺$n" HIR "胸口大穴！\n" NOR;
        }        
}

int difficult_level()
{
        return 1400;
}

string perform_action_file(string action)
{
        return __DIR__"jiuyin-shengong/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"jiuyin-shengong/exert/" + action;
}
