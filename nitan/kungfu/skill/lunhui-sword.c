#include <ansi.h>
inherit FORCE;

string *dodge_msg = ({
        HIW "$n" HIW "身前一道劍光閃過，竟與劍光合為一體，$N" HIW "目瞪口呆，一時難以找出其間破綻。\n" NOR,
        HIW "只見$n" HIW "以氣御劍，劍中生劍，頓時，無數劍影令$N" HIW "眼花繚亂，無從攻擊。\n" NOR,
        HIW "$n" HIW "運氣內功，呵氣成劍，以神御劍，劍花乍現將將$N" HIW "團團圍住，哪裡還有機會攻擊。\n" NOR,
});

string *parry_msg = ({
        HIG "$N" HIG "一招攻出，$n" HIG "不退不避，無數劍芒飛射而出，將此招竟數化解與無形。\n" NOR,
        HIG "$n" HIG "面露微笑，身體猛然間幻化為一把氣劍，任$N" HIG "怎樣攻擊都無法傷之毫厘。\n" NOR,
        HIG "$n" HIG "不慌不忙，手中劍光在面前畫出一道優美的弧線，竟將$N" HIG "攻勢全部化解。\n" NOR,
});

int query_neili_improve(object me)
{
        int lvl;

        lvl = (int)me->query_skill("lunhui-sword", 1);
        return lvl * lvl / 100 * 15 * 38  / 200;
}

int query_jingli_improve(object me)
{
        int lvl;
        
        lvl = (int)me->query_skill("lunhui-sword", 1);
        
        if (me->query_skill_mapped("force") == "lunhui-sword")
                return lvl * 14 / 10;

        return 0;
}

mapping *action = ({
([      "action": HIW "$N" HIW "使出「天極道」，劍法華麗無比，幻化出滿天星光，突然間漫天劍式化為一劍，刺向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "skill_name" : "天極道",
        "damage_type": "刺傷"
]),
([      "action": HIM "$N手中$w" HIM "猶如蘭花乍現，發出嗡嗡的響聲，一式「人間道」使出，頓時幻象重生將$n" HIM "包圍" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "人間道",
        "damage_type": "割傷"
]),
([      "action": HIG "$N" HIG"一劍劃破長空，「餓鬼道」使出，劍光四射，飛向$n" HIG "，攻勢兇猛無比，令人生畏" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 450,    
        "skill_name" : "餓鬼道",
        "damage_type": "割傷"
]),
([      "action": HIR "$N" HIR "輕舞劍花，使出「地獄道」，一股寒氣自$w" HIR "而出，似野鬼，似離魂，呼嘯般湧向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,
        "lvl"   : 300,        
        "skill_name" : "地獄道",
        "damage_type": "割傷"
]),
([      "action": HIC "$N" HIC "催動內力，一式「修羅道」道，剎時劍氣狂奔，空氣令人窒息，劍氣已經襲向$n" HIC "$l" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,       
        "skill_name" : "修羅道",
        "damage_type": "刺傷"
]),
([      "action": HIY "$N" HIY "高舉$w" HIY "，劍芒吞吐不定，一式「畜生道」使出，劍氣夾雜著驚天地怒吼，猶狂風般襲向$n" NOR,
        "force" : 600,
        "attack": 650,
        "dodge" : 110,
        "parry" : 450,
        "damage": 550,        
        "skill_name" : "畜生道",
        "damage_type": "刺傷"
]),
([      "action": HIY "$N" HIY "面露微笑，挽出一個劍花，一式「" HIR "六道輪回" HIY "」使出，劍花花瓣頓時化作六色劍芒射向$n",
        "force" : 700,
        "attack": 650,
        "dodge" : 110,
        "parry" : 650,
        "damage": 650,
        "skill_name" : "六道輪回",
        "damage_type": "刺傷"
]),
});

int valid_force(string force)
{
        return 1;
}

int double_attack()
{
        return 1;
}

int valid_enable(string usage)
{
        return usage == "sword" || usage == "parry" || usage == "dodge" || usage == "parry" || usage == "force";
}

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

string main_skill()
{
        return "lunhui-sword";
}

mapping sub_skills = ([
        "tianji-dao"  : 500,
        "diyu-dao"    : 500,
        "egui-dao"    : 500,
        "chusheng-dao": 500,
        "renjian-dao" : 500,
        "xiuluodao"   : 500,
]);

int get_ready(object me)
{
        return 1;
}

int get_finish(object me)
{
        object ob;
        ob = environment(me);

        // 帶面具無法演練
        if( query_temp("apply/mask_flag", me) )
        {
                tell_object(me, "你必須先取下面具。\n");
                return 0;
        }

        if( !query("lunhui", ob) )
        {
                tell_object(me, "演練六道輪回劍必須在輪回司中，需要借助上古神器昊天塔之力。\n");
                return 0;
        }
        
        if( query("reborn/times", me) < 3 )
        {
                tell_object(me, "你轉世次數不夠，無法領悟輪回的精髓！\n");
                return 0;
        }

        if( query("int", me)<40 )
        {
                tell_object(me, "你演練完畢，只感思緒紊亂，看來依你的悟性，無"
                                "法將其合一。\n");
                return 0;
        }
        if( query("con", me)<40 )
        {
                tell_object(me, "你演練完畢，只覺全身真氣亂竄，眼冒金星，兩耳轟鳴，好"
                                "不容易才控制下來。\n");
                return 0;
        }
        if( query("str", me)<40 )
        {
                tell_object(me, "你演練完畢，只覺雙臂酸疼，全身發軟。\n");
                return 0;
        }
        
        if( query("dex", me)<40 )
        {
                tell_object(me, "你演練完畢，發現依你的身法暫時還無法將其融會貫通。\n");
                return 0;
        }

        if (random(100) != 1 && ! wizardp(me))
        {
                tell_object(me, "你覺得有所感悟，或許再演練一次就能融會貫通，練成六道輪回劍。\n");
                return 0;
        }

        if (me->query_skill("sword", 1) < 700)
        {
                tell_object(me, "你基本劍法火候不足，難以演練成六道輪回劍。\n");
                return 0;
        }
        if (me->query_skill("force", 1) < 700)
        {
                tell_object(me, "你基本內功火候不足，難以演練成六道輪回劍。\n");
                return 0;                
        }
        if (me->query_skill("martial-cognize", 1) < 700)        
        {
                tell_object(me, "你武學修養火候不足，難以演練成六道輪回劍。\n");
                return 0;                
        }
        if (me->query_skill("dodge", 1) < 700)        
        {
                tell_object(me, "你基本輕功火候不足，難以演練成六道輪回劍。\n");
                return 0;                
        }        
        if ((int)me->query_skill("buddhism", 1) < 200)
        {
                tell_object(me, "你禪宗心法修為不足，難以演練成六道輪回劍。\n");
                return 0;        
        }
        /*
        // 消耗輪回點
        if( query("scborn/cur_lunhui_point", me)<6 && !query("thborn/ok", me) )
        {
                tell_object(me, "你輪回點不足，無法演練成六道輪回劍。\n");
                return 0;
        }
        if( !query("thborn/ok", me) )
                addn("scborn/cur_lunhui_point", -6, me);
        */
        me->save();

        tell_object(me, HIW "一陣凡塵往事湧上心頭，你幾欲放聲長嘆。霎那間，你放眼回首，竟有一股莫名\n"
                        "的悲哀。宗師泰鬥那種高出不勝寒、登泰山而小天下之感猶然而生，你只覺得以\n往的"
                        "武學現在看來是多麼的渺小可笑。\n" NOR);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" + me->name() + "演練出"HIY"六道輪回劍"HIM"。\n");
        return 1;
}

mapping query_sub_skills()
{
        return sub_skills;
}

int valid_learn(object me)
{

        // 與12T沖突
        if( me->query_skill("yinyang-shiertian",1) && query("reborn/times", me) < 4 )
                return notify_fail("你感覺體內的陰陽九轉真氣跌宕起伏，似乎容納這種內功。\n");
                
        if( query("str", me)<40 )
                return notify_fail("你先天臂力不足。\n");

        if( query("int", me)<40 )
                return notify_fail("你先天悟性不足。\n");

        if( query("dex", me)<40 )
                return notify_fail("你先天身法不足。\n");
                
        if( query("con", me)<40 )
                return notify_fail("你先天根骨不足。\n");                        
                
        if( query("max_neili", me)<8000 )
                return notify_fail("你的內力修為不夠，難以修煉六道輪回劍。\n");

        if ((int)me->query_skill("force", 1) < 700)
                return notify_fail("你的內功火候太淺，難以修煉六道輪回劍。\n");

        if ((int)me->query_skill("sword", 1) < 700)
                return notify_fail("你的劍法根基不足，難以修煉六道輪回劍。\n");

        if ((int)me->query_skill("dodge", 1) < 700)
                return notify_fail("你的輕功根基不足，難以修煉六道輪回劍。\n");
    
        if ((int)me->query_skill("martial-cognize", 1) < 700)
                return notify_fail("你的武學修養不足，難以修煉六道輪回劍。\n");
                    
        if ((int)me->query_skill("buddhism", 1) < 200)
                return notify_fail("你的禪宗心法修為不足，難以修煉六道輪回劍。\n");
                                            
        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的六道輪回劍。\n");

        if ((int)me->query_skill("sword", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本劍法水平有限，無法領會更高深的六道輪回劍。\n");
                
        if ((int)me->query_skill("martial-cognize", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的武學修養水平有限，無法領會更高深的六道輪回劍。\n");                

        if ((int)me->query_skill("dodge", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本輕功水平有限，無法領會更高深的六道輪回劍。\n"); 

        if ((int)me->query_skill("force", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本內功水平有限，無法領會更高深的六道輪回劍。\n"); 
                                                
        if ((int)me->query_skill("parry", 1) < (int)me->query_skill("lunhui-sword", 1))
                return notify_fail("你的基本招架水平有限，無法領會更高深的六道輪回劍。\n"); 
                                                                
        return 1;
}

string query_skill_name(int level)
{
        int i;
        for (i = sizeof(action) - 1; i >= 0; i--)
                if (level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        return notify_fail("六道輪回劍博大精深，無法簡單的通過練習進步。\n");
}

int query_effect_dodge(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 70;
        if (lvl < 250) return 80;
        if (lvl < 350) return 120;
        return 150;
}

int query_effect_parry(object attacker, object me)
{
        int lvl;

        lvl = me->query_skill("lunhui-sword", 1);
        if (lvl < 200) return 200;
        if (lvl < 250) return 300;
        if (lvl < 350) return 400;
        return 500;
}


mixed hit_ob(object me, object victim, int damage_bonus)
{

        string *desc;
        object weapon;
        
        weapon=query_temp("weapon", me);
        
        if (! objectp(weapon))return damage_bonus;
        
        desc = ({
                HIY "$N" HIY "微笑一聲，輕描淡寫間手中" + weapon->name() + HIY "猶如一道閃電般射向$n" HIY "。\n" NOR,
                HIG "$N" HIG "運起六道真氣，以氣御劍，道道劍光化做雨點般地將$n" HIG "籠罩。\n" NOR,
                HIR "$N" HIR "祭起手中" + weapon->name() + HIR "，煞時天雲突變，狂風襲來，$n" HIR "只覺心中有說不出的難受。\n" NOR,
        });
        
        if (me->is_busy() 
           || random(4) >= 1
           || ! living(victim) 
           || damage_bonus < 120 
           || query("neili", me)<500
           || me->query_skill("lunhui-sword", 1) < 700) 
                return 0; 

        // 追加特效
        victim->receive_wound("qi", damage_bonus * 2, me);
        // 1200級後再追加50%傷害
        if (me->query_skill("lunhui-sword", 1) >= 1200)
                victim->receive_wound("qi", damage_bonus / 2, me);
        
        if (random(3) == 1)victim->start_busy(3 + random(3));
        
        if( random(10) == 1)addn("neili", -1*me->query_skill("lunhui-sword",1)*2, victim);
        
        return desc[random(sizeof(desc))];
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mapping result;
        int ap, dp, cost;

        if ((int)me->query_skill("lunhui-sword", 1) < 350
           || me->query_skill_mapped("parry") != "lunhui-sword"
           || query("neili", me)<200
           || ! living(me))
                return;

        
        cost = damage / 2;
        if (cost > 100) cost = 100;

        ap = ob->query_skill("force", 1) * 4 + ob->query_skill("martial-cognize", 1);
        dp = me->query_skill("lunhui-sword", 1) * 6 + me->query_skill("martial-cognize", 1);

        if( query("reborn/times", ob) < 4 )dp+=1000;
        
        if (dp + random(dp / 2) >= ap)
        {
                addn("neili", -cost, me);
                result = ([ "damage": -damage ]);

                switch (random(3))
                {
                case 0:
                        result += (["msg" : HIG "$n" HIW "微微一笑，竟化做一道劍光，消失了。\n" NOR]);
                        break;
                case 1:
                        result += (["msg" : HIM "$n" HIW "御劍如風，不退反進，竟將$N" HIW "這招化解。\n" NOR]);
                        break;
                default:
                        result += (["msg" : MAG "$n" HIW "輕舞數劍，身前數股旋風將其圍住，令任何招式都無從攻擊。\n" NOR]);
                        break;
                }
                return result;
        }
}
string perform_action_file(string action)
{
        return __DIR__"lunhui-sword/perform/" + action;
}

string exert_function_file(string action)
{
        return __DIR__"lunhui-sword/exert/" + action;
}

int difficult_level()
{
        return 25000;
}

void skill_improved(object me)  
{ 
        int lvl;
        
        lvl = me->query_skill("lunhui-sword", 1); 

        if( lvl >= 500 && 
            !query("can_perform/lunhui-sword/xiuluo", me) )  
        { 
                tell_object(me, HIC "你通曉了輪回劍「" HIR "修羅劍神" HIC "」的奧秘。\n" NOR);     
                set("can_perform/lunhui-sword/xiuluo", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        } 

        if( lvl >= 600 && 
            !query("can_perform/lunhui-sword/lan", me) )  
        { 
                tell_object(me, HIC "你通曉了輪回劍「" HIR "蘭劍舞" HIC "」的奧秘。\n" NOR);     
                set("can_perform/lunhui-sword/lan", 1, me); 
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
                me->improve_skill("martial-cognize", 1500000);   
        }
}
