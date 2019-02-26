// This program is a part of NITAN MudLIB
// dugu-jiujian.c 獨孤九劍

#include <ansi.h>
#include <combat.h>

inherit SKILL;

string *parry_msg = ({ 
        "卻見$n踏前一步，劍式斜指你的右臂，想要使$P閃身而退。\n", 
        "$n以攻為守，以進為退，凝神運氣向$P猛攻快打地揮出方位大異的泰山「快活三」三劍。\n", 
        "$n劍法突變，劍勢伸縮不定，奔騰矯夭，逆使嵩山劍法的「天外玉龍」企圖迫使$P變招。\n", 
        "$n突然一劍點向$P的$l，雖一劍卻暗藏無數後着，$P手足無措，攻勢不由自主停了下來。\n" 
        "$n不閃不避，舉劍閃電般使出「疊翠浮青」反削$P的$l，想擋過你此招。\n", 
        "$n突然使出青城派松風劍法的「鴻飛冥冥」，長劍對着$P一絞，企圖突破$P的攻勢。\n" 
        "$n挺劍一招象是「白雲出岫」回刺$P的$l，企圖將$P的攻勢化解。\n", 
        "只見$n不退反進，身如飄風，一式「天柱雲氣」動向無定，擋住了$P的\n進攻。\n", 
        "$n不退反進，使出恆山劍招「綿裏藏針」，森森劍氣充溢四周！架開了$P的這招\n", 
}); 

mapping *action = ({
([      "action": HIW "但見$N挺身而上，$w" + HIW "一旋，一招彷彿泰山劍法的「來鶴清泉」直刺$n的$l" NOR,
        "attack": 70,
        "dodge" : 60,
        "parry" : 70,
        "damage": 120,
        "lvl" : 0,
        "damage_type" : "刺傷"
]),
([      "action": YEL "$N奇詭地向$n揮出「泉鳴芙蓉」、「鶴翔紫蓋」、「石廩書聲」、「天柱雲氣」及「雁回祝融」衡山五神劍" NOR,
        "attack": 71,
        "parry" : 72,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 10,
        "damage_type" : "刺傷"
]),
([
        "action": GRN "$N劍隨身轉，續而刺出十九劍，竟然是華山「玉女十九劍」，\n但奇的是這十九劍便如一招，手法之快，直是匪夷所思" NOR,
        "attack": 72,
        "dodge" : 64,
        "parry" : 78,
        "damage": 150,
        "lvl" : 20,
        "damage_type" : "刺傷"
]),
([      "action": BLU "$N劍勢忽緩而不疏，劍意有餘而不盡，化恆山劍法為一劍，向$n慢慢推去" NOR,
        "parry" : 73,
        "attack": 73,
        "dodge" : 65,
        "damage": 125,
        "lvl" : 30,
        "damage_type" : "刺傷"
]),
([      "action": HIR "$N劍意突煥氣象森嚴，便似千軍萬馬奔馳而來，長槍大戟，黃沙千里，盡括嵩山劍勢擊向$n的$l" NOR,
        "parry" : 74,
        "attack": 74,
        "dodge" : 68,
        "damage": 130,
        "lvl" : 40,
        "damage_type" : "刺傷"
]),
([      "action": CYN "卻見$N身隨劍走，左邊一拐，右邊一彎，劍招也是越轉越加狠辣，竟化「泰山十八盤」為一劍攻向$n" NOR,
        "attack": 75,
        "parry" : 75,
        "dodge" : 60,
        "damage": 120,
        "lvl" : 50,
        "damage_type" : "刺傷"
]),
([      "action": HIY "$N劍招突變，使出衡山的「一劍落九雁」，削向$n的$l" + HIY "，\n怎知劍到中途，突然轉向，大出$n意料之外" NOR,
        "attack": 76,
        "parry" : 76,
        "dodge" : 64,
        "damage": 120,
        "lvl" : 60,
        "damage_type" : "刺傷"
]),
([      "action": MAG "$N吐氣開聲，一招似是「獨劈華山」，手中$w" + MAG "向下斬落，直劈向$n的$l" NOR,
        "attack": 77,
        "dodge" : 67,
        "parry" : 77,
        "damage": 140,
        "lvl" : 70,
        "damage_type" : "刺傷"
]),
([      "action": HIB "$N手中$w" + HIB "越轉越快，使的居然是衡山的「百變千幻雲霧十三式」，\n劍式有如雲卷霧湧，旁觀者不由得目為之眩" NOR,
        "attack": 78,
        "dodge" : 60,
        "parry" : 78,
        "damage": 140,
        "lvl" : 80,
        "damage_type" : "刺傷"
]),
([      "action": HIM "$N滿場遊走，東刺一劍，西刺一劍，令$n莫明其妙，分不出$N劍法的虛實" NOR,
        "attack": 79,
        "dodge" : 65,
        "parry" : 79,
        "damage": 160,
        "lvl" : 90,
        "damage_type" : "刺傷"
]),
([      "action": HIC "$N抱劍旋身，轉到$n身後，雜亂無章地向$n刺出一劍，不知使的是什麼劍法" NOR,
        "attack": 80,
        "parry" : 80,
        "dodge" : 65,
        "damage": 160,
        "lvl" : 100,
        "damage_type" : "刺傷"
]),
([      "action": HIW "$N突然一劍點向$n的$l，雖一劍卻暗藏無數後着，$n手足無措，不知如何是好" NOR,
        "attack": 81,
        "parry" : 81,
        "dodge" : 66,
        "damage": 170,
        "lvl" : 110,
        "damage_type" : "刺傷"
]),
([      "action": RED "$N劍挾刀勢，大開大闔地亂砍一通，但招招皆擊在$n攻勢的破綻，迫得$n不得不守" NOR,
        "attack": 82,
        "dodge" : 71,
        "parry" : 82,
        "damage": 175,
        "lvl" : 120,
        "damage_type" : "刺傷"
]),
([      "action": YEL "$N反手橫劍刺向$n的$l，這似有招似無招的一劍，威力竟然奇大，$n難以看清劍招來勢" NOR,
        "attack": 83,
        "dodge" : 70,
        "parry" : 83,
        "damage": 180,
        "lvl" : 130,
        "damage_type" : "刺傷"
]),
([      "action": HIR "$N舉劍狂揮，迅速無比地點向$n的$l，卻令人看不出其所用是什麼招式" NOR,
        "attack": 84,
        "parry" : 84,
        "dodge" : 60,
        "damage": 170,
        "lvl" : 140,
        "damage_type" : "刺傷"
]),
([      "action": HIM "$N隨手一劍指向$n，落點正是$n的破綻所在，端的是神妙無倫，不可思議" NOR,
        "attack": 85,
        "parry" : 85,
        "dodge" : 64,
        "damage": 180,
        "lvl" : 150,
        "damage_type" : "刺傷"
]),
([      "action": CYN "$N臉上突現笑容，似乎已看破$n的武功招式，胸有成竹地一劍刺向$n的$l" NOR,
        "attack": 86,
        "dodge" : 60,
        "parry" : 86,
        "damage": 180,
        "lvl" : 160,
        "damage_type" : "刺傷"
]),
([
        "action": RED "$N將$w"+ RED "隨手一擺，但見$n自己向$w"+ RED "撞將上來，神劍之威，實人所難測" NOR,
        "attack": 90,
        "dodge" : 70,
        "parry" : 90,
        "damage": 200,
        "lvl" : 170,
        "damage_type" : "刺傷"
])
});

mapping *action2 = ({ 
([      "action" : HIW "但見$N手中$w破空長吟，平平一劍刺向$n，毫無招式可言" NOR, 
        "force" : 300,
        "attack": 120, 
        "dodge" : 120, 
        "parry" : 120, 
        "damage": 180, 
        "damage_type" : "刺傷" 
]), 
([      "action" : HIW "$N揉身欺近，輕描淡寫間隨意刺出一劍，簡單之極，無招無式" NOR,
        "force" : 300, 
        "attack": 130, 
        "dodge" : 130, 
        "parry" : 130, 
        "damage": 190, 
        "damage_type" : "刺傷" 
]), 
([      "action" : HIW "$N身法飄逸，神態怡然，劍意藏於胸中，手中$w隨意揮灑而出，獨孤" 
                       "九劍已到了收發自如的境界" NOR, 
        "force" : 300,
        "attack": 140, 
        "dodge" : 140, 
        "parry" : 140, 
        "damage": 200, 
        "damage_type" : "刺傷" 
]), 
}); 

int double_attack() { return 1; }

int valid_enable(string usage) 
{ 
        return usage == "sword" || usage == "parry";
}

int valid_learn(object me) 
{ 
        object ob; 
        
        if( !(ob=query_temp("weapon", me) )
         || query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n"); 
        
        if( query("int", me)<34 )
                return notify_fail("你的天資不足，無法理解獨孤九劍的劍意。\n"); 
        
        // if (me->query("dugu-jiujian/nothing") && 
        if (
            query("con", me)<26 )
                return notify_fail("你先天根骨不足，無法理解獨孤九劍的劍意。\n"); 
            
        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想殺盡敵人，沒能理解獨孤九劍的的真正含義。\n"); 
        
        if( query("character", me) == "陰險奸詐" )
                return notify_fail("你一心想怎麼學好劍法去害人，結果沒能理解獨孤九劍。\n"); 
        
        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什麼獨孤九劍，亂七八糟的，沒有半點氣勢。\n"); 
        
        if (me->query_skill("sword", 1) < 100) 
                return notify_fail("你的基本劍法造詣太淺，無法理解獨孤九劍。\n"); 
        
        if (me->query_skill("sword", 1) < me->query_skill("dugu-jiujian", 1)) 
        return notify_fail("你的基本劍法造詣有限，無法理解更高深的獨孤九劍。\n"); 
        
        return 1; 
} 

mapping query_action(object me, object weapon)
{
        int i, level;
        level   = (int) me->query_skill("dugu-jiujian", 1);
        
        if( query("dugu-jiujian/nothing", me) )
                return action2[random(sizeof(action2))];       
                  
        if( objectp(weapon) && query("id", weapon) == "xuantiejian" )
        {
                if (me->query_str() >= 60 && me->query_int() >= 36 
                &&  random(level) > 120 
                 && me->query_skill("force")>150 && query("neili", me)>400 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": HIR "$N臉色凝重虔誠，緩緩舉起玄鐵重劍，突然躍起身劍合一，"
                                          "馭劍化為一道黑氣向$n衝刺而去" NOR,
                                "damage": 400,
                                "attack": 100,
                                "dodge" : 80,
                                "parry" : 80,
                                "damage_type" : "刺傷"
                        ]);
                }
        }
        for (i = sizeof(action); i > 0; i--)
                if (level > action[i - 1]["lvl"])
                        return action[NewRandom(i, 5, level / 5)];
}

int practice_skill(object me)
{
        return notify_fail("獨孤九劍只能通過「"+RED+"總訣式"+NOR+"」來演練。\n");
}

string perform_action_file(string action)
{
        return __DIR__"dugu-jiujian/" + action;
}

int query_effect_parry(object attacker, object me) 
{ 
        object weapon; 
        int lvl; 
        
        if( !objectp(weapon=query_temp("weapon", me)) || 
            query("skill_type", weapon) != "sword" )
                return 0; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        if (lvl < 90)  return 0; 
        if (lvl < 100) return 50; 
        if (lvl < 125) return 55; 
        if (lvl < 150) return 60; 
        if (lvl < 175) return 65; 
        if (lvl < 200) return 70; 
        if (lvl < 225) return 75; 
        if (lvl < 250) return 80; 
        if (lvl < 275) return 90; 
        if (lvl < 325) return 100; 
        if (lvl < 350) return 110; 
        return 120; 
} 

void skill_improved(object me) 
{ 
        int lvl, i; 
        
        i=query("int", me)/3;
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if (lvl > 120 
         && query("can_perform/dugu/qi", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/qi",random(i))<100 )
                { 
                        tell_object(me, HIC "你對獨孤九劍「" HIW "破氣式" 
                                        HIC "」有了新的領悟。\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "你通曉了獨孤九劍「" HIW "破" 
                                        "氣式" HIC "」的奧祕。\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        } 
        
        if (lvl > 150 
         && query("can_perform/dugu/po", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/po",random(i))<100 )
                { 
                        tell_object(me, HIC "你對獨孤九劍「" HIR "總破式" 
                                        HIC "」有了新的領悟。\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "你通曉了獨孤九劍「" HIR "總" 
                                        "破式" HIC "」的奧祕。\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        } 
        
        if (lvl > 200 
         && query("can_perform/dugu/yi", me) <= 100 )
        { 
                if( me->add("can_perform/dugu/yi",random(i))<100 )
                { 
                        tell_object(me, HIC "你對獨孤九劍「" HIR "劍意" 
                                        HIC "」有了新的領悟。\n" NOR); 
                } else 
                { 
                        tell_object(me, HIC "你通曉了獨孤九劍「" HIR "劍" 
                                        "意" HIC "」的奧祕。\n" NOR); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                        me->improve_skill("martial-cognize", 1500000); 
                } 
        }         
} 
        
int difficult_level() 
{ 
        object me = this_object(); 
        
        if( query("dugu-jiujian/nothing", me) )
                return 300; 
        
        else   return 200; 
} 
  
mixed valid_damage(object ob, object me, int damage, object weapon) 
{ 
        mixed result; 
        int ap, dp, mp; 
        object m_weapon; 
        
        if ((int) me->query_skill("dugu-jiujian", 1) < 120 
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me) 
         || query("skill_type", m_weapon) != "sword" )
                return; 
        
        mp = ob->query_skill("count", 1); 
        ap = ob->query_skill("parry") + mp; 
        dp = me->query_skill("parry", 1) / 2 + 
        me->query_skill("dugu-jiujian", 1); 
          
        // 無招 
        if( query("dugu-jiujian/nothing", me) )
        { 
                if (me->query_skill("sword") * 2 / 3 + random(me->query_skill("sword")) >
                    ob->query_skill("parry")) 
                { 
                        result = ([ "damage": -damage ]); 
        
                        result += (["msg" : HIC "$n" HIC "突然舉劍一刺，劍招隨意無章，"
                                            "卻莫明奇妙地突破了$N的攻勢，大出$N意料。\n"
                                            "$n一轉劍勢，劍招源源而出，對$N發動攻勢！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
        
                        if (! ob->is_busy())
                        ob->start_busy(1 + random(2)); 
                        return result;
                } 
              
        } 
        
        if (ap / 2 + random(ap) < dp) 
        { 
                result = ([ "damage": -damage ]); 

                switch (random(6))
                {
                case 0:
                        result += (["msg" : HIC "$n" HIC "突然舉劍一刺，劍招隨意無章，"
                                            "卻莫明奇妙地突破了$N的攻勢，大出$N意料。\n"
                                            "$n一轉劍勢，劍招源源而出，對$N發動攻勢！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 1:
                        result += (["msg" : HIC "$n" HIC "舉劍反攻，後發先至地刺向$N，不僅把"
                                            "$N招術封死，更進一步發出攻擊！\n" NOR]);
                        COMBAT_D->do_attack(me,ob,query_temp("weapon", me));
                        break;
                case 2:
                        result += (["msg" : HIC "$n" HIC "提劍回刺，落點正是$N的破綻，"
                                            "$N不得不撤招嚴守，身形一晃間已退出丈許！\n" NOR]);
                        break;
                case 3: 
                        result += (["msg" : HIC "卻見$n" HIC "踏前一步，劍式斜指$P" HIC 
                                            "右臂，招式迅捷無比，使得$N" HIC "閃身而退" 
                                            "。\n" NOR]); 
                        break; 
                case 4: 
                        result += (["msg" : HIC "$n" HIC "突然一劍點向$N" HIC "，雖一劍" 
                                            "卻暗藏無數後着，$N" HIC "頓時手足無措，攻" 
                                            "勢不由自主停了下來。\n" NOR]); 
                        break; 
                default: 
                        result += (["msg" : HIC "$n" HIC "眼見避無可避，只好提劍亂刺一通，"
                                            "居然出乎意料地將$N的攻擊接去。\n" NOR]);
                        break;
                }       

                return result; 
        } else 
        if (mp >= 100) 
        { 
                switch (random(3)) 
                { 
                case 0: 
                        result = HIY "$n" HIY "一抖手中的" + m_weapon->name() + 
                                 HIY "，中攻直進一劍挺進，可是$N" HIY "反招更快" 
                                 "，進襲$n" HIY "！\n" NOR; 
                        break; 
        
                case 1: 
                        result = HIY "$n" HIY "手中" + m_weapon->name() + "輕挑" 
                                 "，" HIY "正指向$N" HIY "攻勢中的破綻，可是$N" 
                                 HIY "身形一變，破綻立刻不成為破綻。\n" NOR; 
                        break; 
        
                default: 
                        result = HIY "$n" HIY "手中" + m_weapon->name() + HIY 
                                 "續變換數種劍招，然而$N" HIY "理也不理，再次攻" 
                                 "出，絲毫不受$n" HIY "的迷惑。\n"  NOR; 
                        break; 
                } 
                COMBAT_D->set_bhinfo(result); 
        } 
} 
            
mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        mixed result;
        int lvl; 
        object weapon, weapon2; 
        int i, ap, dpp, dpd, dpf; 
        string type, msg, msg1; 
        
        lvl = me->query_skill("dugu-jiujian", 1); 
        
        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "dugu-jiujian" 
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("dugu-jiujian/nothing", me) )
                return 0; 
          
        ap = me->query_skill("sword"); 
        dpp = victim->query_skill("parry"); 
        dpd = victim->query_skill("dodge"); 
        dpf = victim->query_skill("force"); 
        
        switch(random(3)) 
        { 
        case 1: 
                if (ap * 3 / 4 + random(ap) > dpp) 
                { 
                        addn("neili", -100, me);
                        result = ([ "damage" : damage_bonus / 2 ]); 
                     
                        msg1 = random(2) ? HIR "$N" HIR "一劍攻出，劍氣橫飛，" + weapon->name() + HIR 
                                           "時若游龍穿空，時若驚鴻渡雲，卻不知這普通的" 
                                           "一劍之中竟藴藏着如此威力。\n" NOR: 
                                           HIR "$N" HIR "手中" + weapon->name() + HIR "猶" 
                                           "如生了眼睛一般，一劍隨意揮出，竟直刺向$n" HIR  
                                           "小腹，看似平淡，但方位、力道卻拿捏得恰倒好處。\n" NOR; 
                        result += ([ "msg" : msg1 ]);
                        return result;
                } 
                break; 
        
        case 2:        
                message_vision(HIC "\n$N" HIC "隨意揮灑手中的" + weapon->name() + 
                               HIC "，招招從出其不意的方位直指$n" HIC "招式中的" 
                               "破綻！\n" NOR, me, victim); 
        
                if (! me->is_busy()) 
                { 
                        weapon=query_temp("weapon", me);
                        weapon2=query_temp("weapon", victim);
                        if( weapon2)type=query("skill_type", weapon2);
        
        
                        if (ap * 3 / 4 + random(ap) >= dpf && weapon2 
                        &&  type != "pin") 
                        { 
                                msg = HIW "$n" HIW "覺得眼前眼花繚亂，手中" 
                                      "的" + weapon2->name() + HIW "一時竟" 
                                      "然拿捏不住，脱手而出！\n" NOR; 
                                weapon2->move(environment(me));       
                                addn("neili", -100, me);
                        } else 
                        { 
                                msg = HIY "$n" HIY "略得空隙喘息，一時間卻" 
                                      "也無力反擊。\n" NOR; 
                                addn("neili", -40, me);
                        } 
                }else  
                if (ap * 4 / 5 + random(ap) > dpd) 
                { 
                        msg = HIY "$n" HIY "連忙抵擋，一時間不禁手忙腳亂，" 
                              "無暇反擊。\n" NOR; 
        
                        if (! victim->is_busy())
                        victim->start_busy(1 + random(lvl / 30)); 
                } 
                else 
                { 
                        msg = HIC "$N" HIC "隨意揮灑着手中的" + weapon->name() + 
                              HIC "刺向$n" HIC "，不過$n" HIC "防守的異常嚴密，$N" 
                              HIC "一時竟然無法找到破綻。\n" NOR; 
                        if (! victim->is_busy())
                        victim->start_busy(1); 
                } 
                message_combatd(msg, me, victim); 
                break; 
        
        default : 
                if (ap * 2 / 3 + random(ap) > dpd &&  
                    ! me->is_busy() && 
                    !query_temp("dugu-jiujian/lian", me) )
                { 
                        weapon=query_temp("weapon", me);
                        message_sort(HIY "\n$N" HIY "胸藏劍意，手中" + weapon->name() + HIY  
                                     "隨意揮灑而出，速度之快，方位之準，顯是獨孤九劍已達到" 
                                     "收發自如的境界。\n" NOR, 
                                     me, victim); 
        
                        addn("neili", -270, me);
           
                        set_temp("dugu-jiujian/lian", 1, me);
                        for (i = 0; i < 5; i++) 
                        { 
                                if (! me->is_fighting(victim)) 
                                        break; 
                  
                                if (! victim->is_busy() && random(2) == 1) 
                                        victim->start_busy(1); 
        
                                COMBAT_D->do_attack(me, victim, weapon, 0); 
                        } 
                        delete_temp("dugu-jiujian/lian", me);
            
                } 
                break;                         
        } 
} 