// daojian-guizhen.c 刀劍歸真
// Edit By Vin 11/2/2001

#include <ansi.h>
inherit SKILL;

int difficult_level() { return 1400; }

mapping *action = ({
([      "action" : "$N手中$w緩緩橫推而出，左手驀地施一招「" HIW "推波助"
                   "瀾" NOR "」，右手同時又施展\n出「" HIY "洗劍懷中抱月"
                   NOR "」，由上至下同時朝向$n$l砍去",
        "force" : 410,
        "attack": 170,
        "dodge" :-60,
        "parry" :-80,
        "damage": 270,
        "damage_type" : "割傷",
]),
([      "action" : "$N一招「" HIY "黃龍轉身吐須" NOR "」，朝$n疾刺出三"
                   "劍，猛然間又變招為「" HIW "沙鷗掠波" NOR "」！\n自下"
                   "而上劃出個半弧形刀芒閃出，刀芒中$w幻作一道白光射向$n",
        "force" : 560,
        "attack": 220,
        "dodge" :-30,
        "parry" :-70,
        "damage": 280,
        "damage_type" : "刺傷",
]),
([      "action" : "$N神色微變，一招「" HIY "丹鳳朝陽" NOR "」，招式"
                   "頓時變得凌厲無比，接着使一招「" HIW "天設牢籠" NOR
                   "」！\n那$w便有如白霧一般壓向$n",
        "force" : 490,
        "attack": 170,
        "dodge" :-160,
        "parry" :-180,
        "damage": 290,
        "damage_type" : "割傷",
]),
([      "action" : "$N使一招胡家刀法的「" HIW "閉門鐵扇" NOR "」，$w毫"
                   "不經意的緩緩斜着推斬出，招至\n中途，剎那間忽然只見寒"
                   "光一閃而過，$N又一招苗家劍法之「" HIY "迎門腿反劈華"
                   "山" NOR "」！\n卻見$w光芒閃爍不定，已經反劈而下",
        "force" : 530,
        "attack": 210,
        "dodge" :-70,
        "parry" :-80,
        "damage": 270,
        "damage_type" : "割傷",
]),
([      "action" : "$N猛喝一聲，一招胡家刀法「" HIW "翼德闖帳" NOR "」"
                   "並苗家劍法「" HIY "返腕翼德闖帳" NOR "」，手中\n$w反"
                   "手疾挑而出，接着轉身躍起，一道白光射向$n的胸口",
        "force" : 470,
        "attack": 130,
        "dodge" :-70,
        "parry" :-40,
        "damage": 280,
        "damage_type" : "刺傷",
]),
([      "action" : "只見$N手中$w“嗤”的一聲斜刺向天空，隨即又向下“唰"
                   "唰”兩下，左右橫\n斬而出，頓時幻出一道閃亮的十字，向"
                   "$n湧出，正是胡家刀法中「" HIW "白鶴舒翅" NOR "」\n以"
                   "及苗家劍法中「" HIY "提撩劍白鶴舒翅" NOR "」的精髓",
        "force" : 430,
        "attack": 190,
        "dodge" :-110,
        "parry" :-140,
        "damage": 330,
        "damage_type" : "刺傷",
]),
([      "action" : "$N一招「" HIY "上步雲邊摘月" NOR "」，縱身躍起，不"
                   "見蹤影，忽然間卻見$w從半空中穿出\n變招「" HIW "春"
                   "風送暖" NOR "」，左腳躍步落地，$w順勢往前，呼嘯着劈"
                   "向$n的$l",
        "force" : 510,
        "attack": 180,
        "dodge" :-70,
        "parry" :-120,
        "damage": 300,
        "damage_type" : "割傷",
]),
([      "action" : "只見$N一招「" HIY "沖天掌蘇秦背劍" NOR "」，左手虛"
                   "擊，右手$w猛的自下方挑起，剎時\n又出殺着「" HIW "八方"
                   "藏刀勢" NOR "」，頓時劍光中閃出無數朵刀花從四面八方"
                   "湧向$n全身",
        "force" : 530,
        "attack": 190,
        "dodge" :-120,
        "parry" :-120,
        "damage": 280,
        "damage_type" : "割傷",
]),
});

string main_skill() { return "daojian-guizhen"; }

mapping sub_skills = ([
        "miaojia-jian" : 250,
        "hujia-daofa"  : 250,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword"
            && query("skill_type", ob) != "blade" )
        {
                tell_object(me, "你空手舞了半天，發現不拿把刀或是劍實在"
                                "難以演練。\n");
                return 0;
        }

        if( query("character", me) != "光明磊落" && query("character", me) != "國士無雙" )
        {
                tell_object(me, "你演練了半天，心中暗道：什麼刀劍合一竟"
                                "如此難練，看來不過是騙人的罷了。\n");
                return 0;
        }

        if( query("int", me)<32 )
        {
                tell_object(me, "你演練完畢，只感劍法和刀法毫無牽連，看"
                                "來依你的悟性，無法將其合一。\n");
                return 0;
        }

        if( query("dex", me)<26 )
        {
                tell_object(me, "你演練完畢，只覺依自己的身法靈動性，根"
                                "本無法將二者合一。\n");
                return 0;
        }

        if( query("con", me)<32 )
        {
                tell_object(me, "你演練完畢，只覺依自己的根骨不足，根"
                                "本無法將二者合一。\n");
                return 0;
        }

        if( query("str", me)<31 )
        {
                tell_object(me, "你演練完畢，只覺依自己的臂力不足，根"
                                "本無法將二者合一。\n");
                return 0;
        }

        if (me->query_skill("literate", 1) < 200)
        {
                tell_object(me, "你覺得苗家劍法和胡家刀法都極其深奧，看"
                                "來多研究一下學問可能更有幫助。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 250)
        {
                tell_object(me, "你演練完畢，發現自己的武學修養尚待提高"
                                "，暫且無法將二者合一。\n");
                return 0;
        }

        /*
        if (me->query_skill("hujia-daofa", 1) > 500 ||
            me->query_skill("miaojia-jian", 1) > 500)
        {
                tell_object(me, "你研究了半天，卻只感深受劍法和刀法影"
                                   "響太深，已無法融會貫通，合二為一。\n");
                return 0;
        }
        */

        if( query("max_neili", me)<4500 )
        {
                tell_object(me, "你覺得自己真氣不繼，無法將苗家劍法和胡"
                                "家刀法二者合一。\n");
                return 0;
        }

        if (random(30) < 27)
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會"
                                "貫通，將二者合一。\n");
                return 0;
        }

        tell_object(me, HIY "\n一陣凡塵往事湧上心頭，你幾欲放聲長歎。霎"
                        "那間，苗家劍法和胡家刀法交替着不斷在\n你腦海裏"
                        "閃現，終於融會貫通，合二為一。你終於通曉了刀劍"
                        "歸真的訣竅。\n" NOR);
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "blade" || usage == "parry";
}

int valid_learn(object me)
{
        object ob;
        int lvls, lvlb, lvld;

        lvls = me->query_skill("sword", 1);
        lvlb = me->query_skill("blade", 1);
        lvld = me->query_skill("daojian-guizhen", 1);

        if( !(ob=query_temp("weapon", me) )
            || query("skill_type", ob) != "sword"
            && query("skill_type", ob) != "blade" )
                return notify_fail("你必須先找一柄劍或一柄刀才能夠練習。\n");

        if( query("character", me) != "光明磊落" && query("character", me) != "國士無雙" )
                return notify_fail("你練習了半天，心中暗道：什麼刀劍合"
                                   "一，竟如此難練，這東西不練也罷。\n");

        if( query("int", me)<32 )
                return notify_fail("你研究了半天，卻只感劍法和刀法毫無"
                                   "牽連，看來是自己天資不足。\n");

        if( query("dex", me)<26 )
                return notify_fail("你研究了半天，只覺依自己的身法靈動"
                                   "性，根本無法修習這門武功。\n");

        if( query("con", me)<32 )
        {
                tell_object(me, "你演練完畢，只覺依自己的根骨不足，根"
                                "本無法修習這門武功。\n");
                return 0;
        }

        if( query("str", me)<31 )
        {
                tell_object(me, "你演練完畢，只覺依自己的臂力不足，根"
                                "本無法修習這門武功。\n");
                return 0;
        }

        if (me->query_skill("martial-cognize", 1) < 250)
                return notify_fail("你覺得苗家劍法和胡家刀法都極其深奧"
                                   "，依照自己武學修養難以理解。\n");

        if( query("max_neili", me)<4500 )
                return notify_fail("你的內力太弱，無法將苗家劍法和胡家"
                                   "刀法二者合一學習。\n");

        if (lvls < 250 || lvlb < 250)
                return notify_fail("你的刀劍根基火候不足，難以修煉刀劍"
                                   "歸真。\n");

        // 刀法和劍法均低於刀劍歸真
        if (lvls < lvld && lvlb < lvld)
                return notify_fail("你的刀劍根基火候不足，無法領會更高"
                                   "深的刀劍歸真。\n");

        // 刀法和劍法中其一低於刀劍歸真
        if (lvls < lvld || lvlb < lvld)
        {
                // 倘若修煉者為武學大宗師，且基本刀法及劍法等級均
                // 超過 320 級，則只需要其中之一支持即可
                if (! ultrap(me) || lvls < 320 || lvlb < 320)
                        return notify_fail("你的刀法或劍法火候不足，無"
                                           "法領會更高深的刀劍歸真。\n");
        }
        return 1;
}

int practice_skill(object me)
{
        if( query("qi", me)<100 )
                return notify_fail("你的體力不夠練刀劍歸真。\n");

        if( query("neili", me)<100 )
                return notify_fail("你的內力不夠練刀劍歸真。\n");

        me->receive_damage("qi", 85);
        addn("neili", -85, me);
        return 1;
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
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

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("daojian-guizhen", 1); 

        if( lvl >= 200 && 
            !query("can_perform/daojian-guizhen/ben", me) )  
        { 
                tell_object(me, HIC "你通曉了刀劍歸真「" HIR "萬馬奔騰" HIC "」的奧祕。\n" NOR);     
                set("can_perform/daojian-guizhen/ben", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 300 && 
            !query("can_perform/daojian-guizhen/po", me) )  
        { 
                tell_object(me, HIC "你通曉了刀劍歸真「" HIR "破定軍山" HIC "」的奧祕。\n" NOR);     
                set("can_perform/daojian-guizhen/po", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
        
        if( lvl >= 250 && 
            !query("can_perform/daojian-guizhen/tian", me) )  
        { 
                tell_object(me, HIC "你通曉了刀劍歸真「" HIR "刀劍七重天" HIC "」的奧祕。\n" NOR);     
                set("can_perform/daojian-guizhen/tian", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 280 && 
            !query("can_perform/daojian-guizhen/xue", me) )  
        { 
                tell_object(me, HIC "你通曉了刀劍歸真「" HIR "天下有血" HIC "」的奧祕。\n" NOR);     
                set("can_perform/daojian-guizhen/xue", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 
} 

mixed hit_ob(object me, object victim, int damage_bonus)
{
        if (damage_bonus < 100)
                return 0;

        if (damage_bonus < victim->query_int())
                return 0;

        // if (me->query_temp("daojian-guizhen/max_pfm"))
        {
                victim->receive_damage("qi", damage_bonus, me);
                victim->receive_wound("qi", damage_bonus / 2, me);
                return random(2) ? HIR "只聽「噗嗤」一聲，一股鮮血至$n"
                                   HIR "胸前射出。\n" NOR:

                                   HIR "霎時只見寒光一閃，一柱鮮血至$n"
                                   HIR "胸前射出。\n" NOR;
        }
}

string perform_action_file(string action)
{
        return __DIR__"daojian-guizhen/" + action;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;
        if( !objectp(query_temp("weapon", me)) )
                return 0;

        lvl = me->query_skill("daojian-guizhen", 1);
        if (lvl < 80)  return 0;
        if (lvl < 200) return 50;
        if (lvl < 280) return 80;
        if (lvl < 350) return 100;
        return 120;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp, level;

        if ((level = (int)me->query_skill("daojian-guizhen", 1)) < 100 ||
            !objectp(query_temp("weapon", me)) )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("force") + mp;
        dp = me->query_skill("parry", 1) / 2 +
             me->query_skill("daojian-guizhen", 1) + me->query_skill("hujia-daofa", 1);

        if (ap / 2 + random(ap) < dp)
        {
                result = ([ "damage": -damage ]);

                result += (["msg" : HIC "$n" HIC "突然使出一招「大雪紛紛」，發出萬長白芒，寒光四射，直劈向$N"
                            "化守勢為攻勢，對$N發動進攻！\n" NOR]);
                COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                return result;
        }
}
