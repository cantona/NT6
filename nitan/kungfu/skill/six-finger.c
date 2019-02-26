// six-fingers.c 六脈神劍
// Last Modified by sir 10.22.2001

#include <ansi.h>;
inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }

string main_skill() { return "yinyang-shiertian"; }

mapping *action = ({
([      "name":   "少商劍",
        "action": "$N雙手拇指同時捺出，嗤嗤兩聲急響，「" HIW "少商劍" NOR "」有如石破"
                  "天驚、風雨大至",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 0,
        "weapon" : HIW "少商劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少商劍",
        "action": "$N大拇指一按，嗤嗤兩指，勁道使得甚巧，「" HIW "少商劍" NOR "」劍氣"
                  "如怒潮般湧至",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 10,
        "weapon" : HIW "少商劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少商劍",
        "action": "$N大拇指連揮，「" HIW "少商劍" NOR "」便如是一幅潑墨山水，縱橫倚斜"
                  "，劍路雄勁",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 20,
        "weapon" : HIW "少商劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少商劍",
        "action": "$N雙手拇指同時捺出，「" HIW "少商劍" NOR "」大開大闔，氣派宏偉，每"
                  "一劍都有風雨大至之勢",
        "force" : 460,
        "attack": 140,
        "dodge" : 90,
        "parry" : 90,
        "damage": 260,
        "lvl"   : 30,
        "weapon" : HIW "少商劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "商陽劍",
        "action": "$N食指連動，手腕園轉，「" HIW "商陽劍" NOR "」一劍又一劍的刺出，輕"
                  "靈迅速，劍氣縱橫",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 40,
        "weapon" : HIW "商陽劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "商陽劍",
        "action": "$N變招奇速，右手食指疾從袖底穿出，「" HIW "商陽劍" NOR "」登時幻出"
                  "無數指影",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 50,
        "weapon" : HIW "商陽劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "商陽劍",
        "action": "$N拇指一屈，食指隨即點出，嗤嗤兩聲急響，變成商陽劍法，「" HIW "商"
                  "陽劍" NOR "」激射刺出",
        "force" : 440,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 60,
        "weapon" : HIW "商陽劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "商陽劍",
        "action": "$N以食指急運「" HIW "商陽劍" NOR "」之無形劍氣，卻不過是手指在數寸"
                  "範圍內一點一戳",
        "force" : 480,
        "attack": 145,
        "dodge" : 110,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 70,
        "weapon" : HIW "商陽劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "中衝劍",
        "action": "$N右手中指一豎，「" HIW "中衝劍" NOR "」向前刺出。真氣鼓盪，嗤然聲"
                  "響，無形劍氣直指$n",
        "force" : 560,
        "attack": 155,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 80,
        "weapon" : HIW "中衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "中衝劍",
        "action": "$N將中指向上一刺，「" HIW "中衝劍" NOR "」拔地而起，接着手指向下一"
                  "劃，劍氣如利刀般砍出",
        "force" : 560,
        "attack": 145,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 90,
        "weapon" : HIW "中衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "中衝劍",
        "action": "電光火石之間，$N猛然翻掌，右手陡然探出，中指「" HIW "中衝劍" NOR
                  "」向$n一豎",
        "force" : 560,
        "attack": 135,
        "dodge" : 10,
        "parry" : 70,
        "damage": 220,
        "lvl"   : 100,
        "weapon" : HIW "中衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "關衝劍",
        "action": "$N右手無名指伸出，「" HIW "關衝劍" NOR "」劍路拙滯古樸，一股雄渾無"
                  "比的內力鼓盪而出",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 110,
        "weapon" : HIW "關衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "關衝劍",
        "action": "$N俯身斜倚，無名指「" HIW "關衝劍" NOR "」彈射而出，指尖已對準$n發"
                  "出了一縷強烈的勁風",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 120,
        "weapon" : HIW "關衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "關衝劍",
        "action": "$N無名指輕輕一揮，「嗤啦」一聲，拙滯古樸的「" HIW "關衝劍" NOR "」"
                  "劍氣向$n直射而出",
        "force" : 530,
        "attack": 140,
        "dodge" : 100,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 130,
        "weapon" : HIW "關衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少澤劍",
        "action": "$N左手小指一伸，一條氣流從少衝穴中激射而出，「" HIW "少澤劍" NOR
                  "」出手入風，指向$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 140,
        "weapon" : HIW "少澤劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少澤劍",
        "action": "忽見$N左手小指一伸，一條氣流從$P少衝穴中激射而出，一股「" HIW "少"
                  "澤劍" NOR "」登時射向$n",
        "force" : 500,
        "attack": 160,
        "dodge" : 95,
        "parry" : 92,
        "damage": 270,
        "lvl"   : 150,
        "weapon" : HIW "少澤劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少衝劍",
        "action": "$N右手小指伸出，真氣自少衝穴激盪而出，「" HIW "少衝劍" NOR "」橫生"
                  "奇變，颼的刺向$n",
        "force" : 480,
        "attack": 150,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 160,
        "weapon" : HIW "少衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少衝劍",
        "action": "$N掌託於胸前，伸出右小指，一招「" HIW "少衝劍" NOR "」緩緩地點向$n"
                  "的周身大穴",
        "force" : 530,
        "attack": 170,
        "dodge" : 90,
        "parry" : 95,
        "damage": 260,
        "lvl"   : 170,
        "weapon" : HIW "少衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少衝劍",
        "action": "$N小指一彈，「" HIW "少衝劍" NOR "」化式「分花拂柳」，劍勢如同柳絮"
                  "一般，飄而不亂",
        "force" : 430,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 180,
        "weapon" : HIW "少衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少衝劍",
        "action": "$N一招「" HIW "少衝劍" NOR "」，劍氣迴轉無定形，竟從左側繞了過來，"
                  "點向$n",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 240,
        "lvl"   : 190,
        "weapon" : HIW "少衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
([      "name":   "少衝劍",
        "action": "$N右手小指一揮，一招「" HIW "少衝劍" NOR "」點點刺刺破空刺出，宛如"
                  "雕花刺畫一般",
        "force" : 530,
        "attack": 180,
        "dodge" : 90,
        "parry" : 95,
        "damage": 280,
        "lvl"   : 200,
        "weapon" : HIW "少衝劍氣" NOR,
        "damage_type":  "刺傷"
]),
});

mapping sub_skills = ([
        "shaoshang-sword"  : 120,
        "shangyang-sword"  : 120,
        "zhongchong-sword" : 120,
        "guanchong-sword"  : 120,
        "shaoze-sword"     : 120,
        "shaochong-sword"  : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "段氏皇族") && (!query("reborn/times", me) || member_array("段氏皇族", query("reborn/fams", me)) == -1) )
        {
                tell_object(me, "你研究了一會兒，只覺的不是段氏皇族的根本無法理解其中奧妙\n");
                return 0;
        }

        if( query("int", me)<32 || me->query_int()<44 )
        {
                tell_object(me, "你演練完畢，只感六種劍法毫無牽連，看來依你的悟性，無"
                                "法將其合一。\n");
                return 0;
        }

        if( query("con", me)<26 || me->query_con()<39 )
        {
                tell_object(me, "你演練完畢，只覺全身真氣亂竄，眼冒金星，兩耳轟鳴，好"
                                "不容易才控制下來。\n");
                return 0;
        }

        if( query("gender", me) == "無性" )
        {
                tell_object(me, "你無根無性，陰陽不調，難以演練六脈神劍。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "你覺得六脈神劍極其深奧，看來多研究一下學問可能更有幫"
                                "助。\n");
                return 0;
        }

        if (me->query_skill("lamaism", 1) < 200)
        {
                tell_object(me, "你演練完畢，發現如果通曉密宗心法應該更有幫助。\n");
                return 0;
        }

        if (me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "你演練完畢，發現如果通曉禪宗心法應該更有幫助。\n");
                return 0;
        }

        if ((int)me->query_skill("force") < 300)
        {
                tell_object(me, "你演練完畢，幾乎虛脱，自己的內功水平看來還有待提高。\n");
                return 0;
        }

        if( query("max_neili", me)<5000 )
        {
                tell_object(me, "你演練完畢，丹田提不起半點力來，看來應該繼續鍛鍊內力。\n");
                return 0;
        }

        if ((int)me->query_skill("martial-cognize", 1) < 100)
        {
                tell_object(me, "你演練完畢，發現如果武學修養更上一層因該更有所幫助。\n");
                return 0;
        }

        if (random(10) < 5)
        {
                tell_object(me, "你對六脈神劍的奧妙頗有領悟，或許再演練一次就能夠融會貫通。\n");
                return 0;
        }

        tell_object(me, HIY "一陣凡塵往事湧上心頭，你幾欲放聲長歎。眼前不斷閃現出六脈"
                            "劍法，\n霎那間，你終於通曉六脈神劍。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}
int valid_enable(string usage) { return usage=="finger" || usage=="parry"; }

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練六脈神劍必須空手。\n");

        if( (!query("family/family_name", me) ||
            query("family/family_name", me) != "段氏皇族") &&
            (!query("reborn/times", me) || member_array("段氏皇族", query("reborn/fams", me)) == -1))
                return notify_fail("你研究了一會兒，只覺的不是段氏皇族的根本無法理解其中奧妙\n");

        if( query("int", me)<32 )
                return notify_fail("你研究了半天，只感六種劍法毫無牽連，無法再作研究。\n");

        if( query("con", me)<26 )
                return notify_fail("你研究了一會兒，只覺得眼前金星亂冒，太陽穴突突的跳。\n");

        if (me->query_skill("literate", 1) < 120)
                return notify_fail("你覺得六脈神劍極其深奧，不是你這種學問水平所能研究的。\n");

        if (me->query_skill("lamaism", 1) < 120)
                return notify_fail("你發現這裏面有很多奧妙都和密宗心法有關，難以理解。\n");

        if (me->query_skill("buddhism", 1) < 120)
                return notify_fail("你發現這裏面有很多奧妙都和禪宗心法有關，難以理解。\n");

        if( query("max_neili", me)<1200 )
                return notify_fail("你的內力太弱，無法學六脈神劍。\n");

        if ((int)me->query_skill("finger", 1) < 120)
                return notify_fail("你的基本指法火候不夠。\n");

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("你的現在必須先提高你基本內功的水平。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("six-finger", 1) + 10)
                return notify_fail("你的現在必須先提高你基本指法的水平。\n");

        return 1;
}

int practice_skill(object me)
{
        object* ob, obj;
        int i,skill,damage,cost;
        cost=40;
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("你的必須空手才能練習。\n");
        if( query("qi", me)<160 )
                return notify_fail("你的體力太低了。\n");
        if( query("neili", me)<160 )
                return notify_fail("你的內力不夠練六脈神劍。\n");
        if( skill>100 && query("shen", me)<1 )
                return notify_fail("這種武功當得行俠義事。\n");
        if ((int)me->query_skill("six-finger", 1)>150) cost=80;
        if ((int)me->query_skill("six-finger", 1)>250) cost=150;
        me->receive_damage("qi", cost);
        addn("neili", -150, me);
        return 1;
}
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action); i > 0; i--)
                if(level >= action[i-1]["lvl"])
                        return action[i-1]["skill_name"];
}
mixed hit_ob(object me, object victim, int damage_bonus, int i, int attack_time)
{
        string name;

        if (userp(me))
                attack_time = (int)(me->query_skill("six-finger", 1) / 50);
        else
                attack_time = (int)(me->query_skill("six-finger", 1) / 25);

        // 放寬NPC的攻擊力度
        if (userp(me) && attack_time > 6)
                attack_time = 6;

        if (! me->is_busy()
        && living(victim)
        && random(3) == 0
        && !query_temp("action_flag", me)
        && !query_temp("six-finger/hit_msg", me)
        && damage_bonus > 120
        && query("neili", me)>400
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 180
        && me->query_skill("jingluo-xue", 1) >= 200)
        {
                if( !query_temp("six-finger/hit_msg", me) )
                        message_combatd(HIW "\n霎時間$N" HIW "只覺思緒狂湧，六脈劍譜中"
                                       "的六路劍法交替展現，登時十指紛彈，此去彼來，連"
                                       "綿無盡。\n" NOR, me, victim);

                //me->start_busy(1);

                addn("neili", -attack_time*50, me);

                set_temp("action_flag", 1, me);
                for (i = 0; i < attack_time; i++)
                {
                        if (! me->is_fighting(victim))
                                break;
                        COMBAT_D->do_attack(me, victim, 0, 0);
                }
                delete_temp("action_flag", me);
        }

        if (damage_bonus > victim->query_dex() / 10
        && damage_bonus > 150
        && query("neili", me)>200
        && me->query_skill("martial-cognize", 1) >= 220
        && me->query_skill("six-finger", 1) >= 160
        && me->query_skill("jingluo-xue", 1) >= 180)
        {
                addn("neili", -50, me);
                victim->receive_wound("qi", damage_bonus, me);
                return random(2) ? HIR "你聽到「嗤啦」一聲輕響，臉上竟飛濺到了一些血滴"
                                   "！\n" NOR:

                                   HIR "你只聽「噗嗤」一聲輕響，一股血柱至$n" HIR "身上"
                                   "濺出！\n" NOR;
        }
        return 1;
}


/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);
        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames);
}
*/

int double_attack()
{
        return 1;
}
mapping query_action(object me, object weapon)
{
        int d_e1 = 25;
        int d_e2 = 5;
        int p_e1 = -30;
        int p_e2 = -50;
        int f_e1 = 800;
        int f_e2 = 1000;
        int i, lvl, seq, ttl = sizeof(action);

        if (random(me->query_skill("six-finger",1)) > 60 &&
                me->query_skill("kurong-changong",1) > 60 &&
                query("neili", me)>100 )
        {
                addn("neili", -50, me);
                return ([
                        "action" : "$N忽然覺得劍譜中的六路劍法一一湧向心頭，十指紛彈，此去彼來，連綿無盡。劍氣縱橫，塵煙四起，\n"
                        "六路劍法迴轉運使，$n頓時心神大亂，但覺全身幾處刺痛，幾股鮮血從身上標出。忍痛抬頭一看，一柱劍氣迎面又到\n",
                        "dodge": -50,
                        "parry": -50,
                        "damage": 800,
                        "force": 800,
                        "damage_type": "刺傷"]);
        }
        else
        {
                if (random(10) == 8)
                {
                        addn("neili", -200, me);
                        return ([
                                "action": HIC "$N" HIC "忽然覺得劍譜中的六路劍法一一湧向心頭，十指紛彈，此去彼來，連綿無盡。\n" NOR
                                "頓時只見四處劍氣縱橫，塵煙四起，六路劍法迴轉運使，$n頓時心神大亂，但覺全身幾處刺\n"
                                "痛，幾股" HIR "鮮血" NOR "從身上標出。忍痛抬頭一看，一柱劍氣迎面又到",
                                "attack": 140,
                                "dodge" : -150,
                                "parry" : -120,
                                "damage": 1000,
                                "force" : 1000,
                                "damage_type": "刺傷"]);
                }
                lvl = (int)me->query_skill("six-finger", 1);
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
                        "damage_type" : random(2) ? "內傷" : "刺傷",
                ]);
        }
}

string query_parry_msg(object victim_weapon)
{
        switch (random(4))
        {
        case 0:
                return "$n隨意揮灑，道道劍氣縱橫交錯，宛若天網，$N唯有望洋興歎，徒呼奈何。\n";
        case 1:
                return "$n不閃不避，一招中衝劍直襲$N的胸前大穴，迫得$N只有回身自救。\n";
        case 2:
                return "$n六劍連出，劍氣迴盪，直割得$N眉毛削落，臉面生通，再也不能前進半分！\n";
        default:
                return "$n一聲長笑，無形劍氣四處散開，將$N層層裹住，惟有勉強支撐。才約略擺脱了$n的反擊。\n";
        }
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("six-finger", 1)) < 100 ||
            ! living(me))
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + ob->query_skill("parry") + mp;
        dp = me->query_skill("parry") / 2 +
             me->query_skill("force") / 2 +
             me->query_skill("six-finger", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);


                result += (["msg" : HIC "$n" HIC "危急之時，心中一亂，隨手一指，一道劍氣凌鋭的直奔$N而去。\n"
                                    HIC "$N" HIC "見這招來勢兇狠，不得不收招自守，縱身避開。\n" NOR]);

                return result;
        }
}

/*
int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("six-finger", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

*/
int difficult_level()
{
        return 500;
}

string perform_action_file(string action)
{
        return __DIR__"six-finger/" + action;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("six-finger", 1); 

        if( lvl >= 180 && 
            !query("can_perform/six-finger/qi", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "無形劍氣" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/qi", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 200 && 
            !query("can_perform/six-finger/gz", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "六脈歸宗" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/gz", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
        
        if( lvl >= 220 && 
            !query("can_perform/six-finger/shen", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "六脈驚神" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/shen", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 240 && 
            !query("can_perform/six-finger/six", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "六脈劍氣" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/six", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 260 && 
            !query("can_perform/six-finger/zong", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "縱橫天下" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/zong", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                             

        if( lvl >= 800 && query("reborn/times", me) &&
            !query("can_perform/six-finger/tian", me) )  
        { 
                tell_object(me, HIC "你通曉了六脈神劍「" HIR "天脈神劍" HIC "」的奧祕。\n" NOR);     
                set("can_perform/six-finger/tian", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }                 
} 


int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int help(object me)
{
        write(HIC"\n六脈神劍："NOR"\n");
        write(@HELP

    六脈神劍是大理段氏不傳之祕。天龍寺為大理武學之根本，此
技即為天龍鎮寺之寶，俗家弟子無法窺其堂奧。六脈神劍並非普通
劍法，而是以無上內力運指作劍，傷敵於無形，亦即“氣劍”。

        學習要求：
                枯榮禪功120級
                內力1200
HELP
        );
        return 1;
}

