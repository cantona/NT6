// 基本指法及特殊指法數種。
// 少林武功秘籍藏于慕容世家：    天竺佛指、多羅葉指、修羅指法
// 杭州靈隱寺住持「大悲尊者」：  蓮花指
// 南海「孫玉溪」：              七星指
// 關東「大天龍」：              大天龍指
// 祁連山「無洞上人」：          祁連五絕指
// 嶺南「幽冥道人」              幽冥指
// 演練為：
// canhe-zhi.c 參合指神功

#include <ansi.h>
#include <combat.h>
#include "/kungfu/skill/eff_msg.h";
//inherit F_SSERVER;
inherit SKILL;

string martialtype() { return "skill"; }

string *xue_name = ({
        "勞宮穴","膻中穴","曲池穴","關元穴","曲骨穴","中極穴","承漿穴","天突穴","百會穴",
        "幽門穴","章門穴","大橫穴","紫宮穴","冷淵穴","天井穴","極泉穴","清靈穴","至陽穴",
});

string *xue2_name = ({
        MAG "$N默運神元神功，將內力聚于手指，平平淡淡毫無花俏地點向$n的膻中穴" NOR,
        YEL "$N兩掌豎合，掌心微虛，如蓮花之開放，接著雙手食指輕輕一彈，兩股指風同時襲向$n" NOR,
        WHT "$N凌空虛點數指，數道指風合成一股劍氣，直向$n攻去"NOR,
        RED "$N緩緩舉手，五指先是箕張，再緩緩攏指合拳，霎時生出氣凝河岳般的劍氣狂揚" NOR,
        HIR "$N指風犀利，似一道無形劍氣，將$n籠罩于內，$n只覺胸口一痛，全身真氣狂瀉而出" NOR
});
mapping *action = ({
([      "action": "$N雙指並攏虛點而出，合「"NOR + MAG "天竺佛指" NOR "」及"
                  "「" NOR + MAG "修羅指" NOR "」為一式，頓時一股罡風直射$n",
        "force" : 480,
        "attack": 110,
        "parry" :-90,
        "dodge" :-95,
        "damage": 160,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
]),
([      "action": "$N雙指齊點而出，合「" HIG "蓮花指" NOR "」及「" HIG "多羅葉"
                  "指" NOR "」為一式，頓時劍氣已籠罩$n全身各處",
        "force" : 460,
        "attack": 100,
        "parry" :-90,
        "dodge" :-115,
        "damage": 180,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
]),
([
        "action": "只見$N十指箕張，隨手指指點點，將「" HIY "祁連五絕指" NOR "」及"
                  "「" HIY "大天龍指" NOR "」的精髓招式同時使出，\n頓時劍氣縱橫，塵"
                  "砂四起，逼向$n而去",
        "force" : 460,
        "attack": 100,
        "parry" :-135,
        "dodge" :-125,
        "damage": 180,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
]),
([
        "action": "只見$N縱身躍起，長嘯一聲，凌空而下，「" HIM "七星劍氣" NOR "」已射"
                  "向$n全身各處",
        "force" : 460,
        "attack": 100,
        "parry" :-115,
        "dodge" :-145,
        "damage": 200,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
]),
([      "action": "$N伸出兩指，彈指無聲，陡見兩縷紫氣由指尖透出，「" HIW "幽冥劍氣" NOR
                  "」射向$n周身大穴",
        "force" : 460,
        "attack": 120,
        "parry" :-130,
        "dodge" :-125,
        "damage": 200,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
]),
([      "action": "遙見$N伸出一指輕輕拂向$n，指未到，「" HIR "參合劍氣" NOR "」已將$n壓"
                  "得透不過氣來",
        "force" : 480,
        "attack": 120,
        "parry" :-150,
        "dodge" :-165,
        "damage": 240,
        "weapon" : HIR "參合破體劍氣" NOR,
        "damage_type" : "刺傷"
])
});

string main_skill() { return "canhe-zhi"; }

mapping sub_skills = ([
        "lianhua-zhi"    : 120,
        "tianlong-zhi"   : 120,
        "qilian-zhi"     : 120,
        "tianzhu-fuzhi"  : 120,
        "qixing-zhi"     : 120,
        "youming-zhi"    : 120,
        "xiuluo-zhi"     : 120,
        "duoluoye-zhi"   : 120,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( query("int", me)<30 )
        {
                tell_object(me, "你只覺依自己的悟性，無法合成參合指神功。\n");
                return 0;
        }

        if( query("dex", me)<30 )
        {
                tell_object(me, "你只覺依自己的身法靈動性，根本無法合成參合指神功。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "你覺得參合指神功極其深奧，看來多研究一下學問可能更有幫"
                                "助。\n");
                return 0;
        }

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
        {
                tell_object(me, "你演練完畢，發現如果通曉經絡學應該更有所幫助。\n");
                return 0;
        }
        */

        if (me->query_skill("martial-cognize", 1) < 200)
        {
                tell_object(me, "你發現自己的武學修養尚待提高，暫且無法演練成功。\n");
                return 0;
        }

        if (me->query_skill("force", 1) < 240)
        {
                tell_object(me, "你發現自己的內功根基不夠，暫且無法演練成功。\n");
                return 0;
        }

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你覺得自己真氣不繼，無法合成參合指神功。\n");
                return 0;
        }

        if (random(10) < 7)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通。\n");
                return 0;
        }

        tell_object(me, HIY "\n霎那間，你只覺自身所修煉的數種指法不斷在腦海中交替呈\n"
                            "現，最後又如百川歸海，終于融會貫通，合為本家絕學參合\n"
                            "指神功。你終于通曉了參合指的訣竅。\n" NOR);

        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "finger" || usage == "parry";
}

int double_attack()
{
        return 1;
}

int valid_combine(string combo)
{
        /*
         object me = this_player();
         mappingmyfam=query("family", me);
         if (myfam["master_name"] == "慕容博")
        */
        return combo == "xingyi-zhang";
}

int valid_learn(object me)
{
        if( query_temp("weapon", me) || query_temp("secondary_weapon", me) )
                return notify_fail("練參合指必須空手。\n");

        if( query("int", me)<30 )
                return notify_fail("你的先天悟性太低，無法領會參合指。\n");

        if( query("dex", me)<30 )
                return notify_fail("你的先天身法孱弱，無法修煉參合指。\n");

        if ((int)me->query_skill("force", 1) < 200)
                return notify_fail("你的內功火候不夠，無法修煉合指。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的內力太弱，無法修煉參合指。\n");

        if ((int)me->query_skill("finger", 1) < 160)
                return notify_fail("你的基本指法火候不夠，無法修煉參合指。\n");

        /*
        if (me->query_skill("jingluo-xue", 1) < 160)
                return notify_fail("你發現這裡面有很多奧妙都和人體的經絡構造有關，難以理解。\n");
        */

        if (me->query_skill("martial-cognize", 1) < 120)
                return notify_fail("你的武學修養尚待提高，暫且無法修煉參合指。\n");

        if ((int)me->query_skill("finger", 1) < (int)me->query_skill("canhe-zhi", 1))
                return notify_fail("你的基本指法水平有限，無法領會更高深的參合指。\n");

        return 1;
}

int practice_skill(object me)
{
        int cost;

        if (me->query_skill("canhe-zhi", 1) > 120
            && me->query_skill("zihui-xinfa", 1) < 120)
                return notify_fail("你紫徽心法修為不夠，這樣下去恐怕會走火入魔！\n");

        if( query("qi", me)<130 )
                return notify_fail("你的體力太低了。\n");

        cost = me->query_skill("canhe-zhi", 1) / 2 + 60;

        if( query("neili", me)<cost )
                return notify_fail("你的內力不夠了。\n");

        me->receive_damage("qi", 100);
        addn("neili", -cost, me);
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

        int d_e1 = 30;
        int d_e2 = 50;
        int p_e1 = -30;
        int p_e2 = -10;
        int f_e1 = 280;
        int f_e2 = 380;
        int i, lvl, seq, ttl = sizeof(action);

        // if (! undefinedp(me->query_temp("canhe-action")))
        //        return action[me->query_temp("canhe-action")];

        if( random(10) == 1 && query("neili", me)>1000 )
        {
                addn("neili", -300, me);
                return ([       "action": HIC "$N" HIC "凝神聚氣，雙指連續點出，指風凌"
                                          "厲，破空而出的「參合劍氣」已經逼向$n",
                                "dodge" :-140,
                                "parry" :-140,
                                "damage": 320,
                                "force" : 560,
                                "weapon" : HIR "參合破體劍氣" NOR,
                                "damage_type": "刺傷"
                        ]);
        }

        lvl = (int) me->query_skill("canhe-finger", 1);
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
                "damage_type" : random(2) ? "刺傷" : "瘀傷",
        ]);
}

int learn_bonus() { return 15; }
int practice_bonus() { return 15; }
int success() { return 15; }
int power_point() { return 1.0; }

string query_parry_msg(object victim_weapon)
{
        switch (random(3))
        {
        case 0:
                return NOR + WHT "$n" NOR + WHT"不退反進，右手食指徑直指向$N" NOR + WHT
                       "胸前大穴，$N一驚，連忙回身自救。\n" NOR;
        case 1:
                return NOR + WHT "$n" NOR + WHT"雙指連連點出，迅捷有力，無數道鋼勁的參"
                       "合劍氣護出周身，令$N" NOR + WHT"無從下手。\n" NOR;
        default:
                return NOR + WHT "$n" NOR + WHT"長嘯一聲，但見無數劍氣自$N" NOR + WHT
                       "雙指而出，籠罩在$P周圍，猶如一張網一般，毫無破綻。\n";
        }
}

/*
void skill_improved(object me)
{
        int i;
        string *sub_skillnames;

        sub_skillnames = keys(sub_skills);

        for (i = 0; i < sizeof(sub_skillnames); i++)
                me->delete_skill(sub_skillnames[i]);
}
*/

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl, slv, p;
        object target;
        string msg;

        if (! target) target = offensive_target(me);
        if (! target) {return "";}
        lvl = me->query_skill("canhe-zhi", 1);

        // 身負六脈神劍絕技可以將參合劍氣折回
        if (slv = target->query_skill("six-finger", 1) > 200
            && target->query_skill_prepared("finger") == "six-finger"
            && slv >= me->query_skill("canhe-zhi", 1) - 60
            && random(10) == 0)
        {
                msg = action[random(sizeof(action))]["action"];
                msg += HIY "\n但見$n" HIY "斜斜一指點出，指出如風，劍氣縱橫，嗤然"
                       "作響，竟將$N" HIY "的劍氣全部折回，反向自己射去！\n" NOR;

                me->receive_wound("qi", slv / 4 + random(slv / 6), target);
                p=query("qi", me)*100/query("max_qi", me);
                msg += "( $N" + eff_status_msg(p) + ")\n";
                return msg;
        }

        if (damage_bonus < 120 || lvl < 140) return 0;

        if (random(damage_bonus) > victim->query_dex()/10
            && query("neili", me)>200)
        {
                addn("neili", -80, me);
                victim->receive_wound("qi", (damage_bonus - 80) / 3, me);
                        return HIR "你只聽「嗤嗤嗤」破空聲驟響，臉上竟濺到一些血滴！\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"canhe-zhi/" + action;
}

/*
mixed hit_ob(object me, object victim, int damage_bonus)
{
        string name, weapon;
        name = xue_name[random(sizeof(xue_name))];

        if (victim->is_busy() || damage_bonus < 100) return 0;

        if( !objectp(weapon=query_temp("weapon", me)) )
        {
                if( (query("neili", me)>200) && random(me->query_skill("canhe-zhi",1))>60 )
                {
                        victim->start_busy(2);
                        addn("neili", -30, me);
                        if( query("neili", victim) <= (damage_bonus/2+30) )
                                set("neili", 0, victim);
                        else
                                addn("neili", -damage_bonus/2+30, victim);

                        return HIW "$N默運神元神功，指風輕飄飄地點向$n，一股內勁無聲無息的繞向$n周身大穴！\n"
                               HIW "$n只覺全身一麻，已被一招點中「" HIR + name + HIW "」！\n" NOR;
                }
        }
}
*/

int help(object me)
{
        write(HIC"\n參合指："NOR"\n");
        write(@HELP

    參合指為姑蘇慕容家指法絕技。慕容氏家學淵源，參合指威力
亦不遜于少林派大力金剛指。
    可與星移掌互備。

        學習要求：
                神元功15級
                內力100
HELP
        );
        return 1;
}
