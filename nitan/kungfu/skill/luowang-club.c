// This program is a part of NITAN MudLIB
// luowang-club.c 緊那羅王棍

#include <ansi.h> 
#include <combat.h>

inherit SKILL; 

mapping *action = ({ 
([      "action" :
       "$N手中的棍梢由下往上一撩,緊接着一招[順風打旗],那棍尾直 往$n的$l打去",     
       "force"  : 350, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 230, 
       "damage_type": "淤傷" 
]), 
([      "action" :"$N單腿點地，向上拔出丈餘，$w飛舞幻出無數幻影將
$n罩住，口中大喝一聲[雪花蓋頂]，只聽棍帶風聲嗚嗚作響向$n的$1劈去",     
       "force"  : 380, 
       "attack" : 200, 
       "dodge"  : -5, 
       "parry"  : -80, 
       "damage" : 250, 
       "damage_type": "淤傷" 
]), 
([      "action" : "$N把$w一架，擋住了$n的去路，$N手中的$w一振，帶起了萬丈金光，
　　　從這片光芒中衝出一道清煙，直向$n的$1奔去，正是一招［撥雲見日］",
       "force"  : 400, 
       "attack" : 200, 
       "dodge"  : -40, 
       "parry"  : -105, 
       "damage" : 280, 
       "damage_type": "刺傷" 
]), 
([      "action" :       "$N手中的$w一振，以棍行刀式，大開大闔,       
       $w化做六道黑影向$n的$1集中劈去",      
       "force"  : 420, 
       "attack" : 180, 
       "dodge"  : -15, 
       "parry"  : -80, 
       "damage" : 280, 
       "damage_type": "淤傷" 
]), 
([      "action" : "$N身體向後一轉,大喝:[烏龍擺尾],$w化做數道幻影掃向$n的腰部", 
       "force"  : 420, 
       "attack" : 190, 
       "dodge"  : -10, 
       "parry"  : -100, 
       "damage" : 290, 
       "damage_type": "震傷"
]), 
([     "action" : "$N身行一展,化為[燕子穿林]式,手中的$w快如閃電地刺向$n的的$l",
       "force"  : 450,
       "attack" : 150,
       "dodge"  : -20,
       "parry"  : -120,
       "damage" : 310,
       "damage_type": "刺傷"
]), 
([     "action" : "$N身體往後一頓,換以握槍的手法,一式[蛟龍出水],手中的$w往$n的$l刺去",
       "force"  : 520, 
       "force" : 460, 
       "attack" : 160, 
       "dodge"  : -40, 
       "parry"  : -100, 
       "damage" : 90, 
       "damage_type": "刺傷" 
]), 
([      "action" : "$N手中的$w舞了個棍花，單腿獨立，$w向後一帶，口中大喝一聲
　　　　[獨劈華山]，只聽$w帶一聲呼嘯向$n的$1劈去",
       "force"  : 490, 
       "attack" : 220, 
       "dodge"  : -10, 
       "parry"  : -75, 
       "damage" : 320, 
       "damage_type": "淤傷" 
]), 
([      "action" : "$N腰一擺，雙腿順勢盤腿坐下，手中$w一抖，一式［犀牛望月],
       手中的$w勢如長虹，由下往$n的$1刺去",    
       "force"  : 500, 
       "attack" : 150, 
       "dodge"  : -30, 
       "parry"  : -110, 
       "damage" : 340, 
       "damage_type": "刺傷" 
]), 
([      "action" : "$N手中的$w左右攔掃，一把把$n圈住,緊接着，$N用$w把$n一挑       
        長嘯一聲:[羅漢搏虎],棍梢徑直向$n的$1劈去",           
       "dodge"  : -25, 
       "force"  : 500, 
       "attack" : 170, 
       "dodge"  : -70, 
       "parry"  : -55, 
       "damage" : 350, 
       "damage_type": "淤傷" 
]), 
([      "action" : "$N使出一招[天馬行空],手中的$w輕盈自如地揮灑，向$n的$1點擊過去",
       "force" : 510, 
       "attack" : 185, 
       "dodge"  : -30, 
       "parry"  : -100, 
       "damage" : 410, 
       "damage_type": "淤傷" 
]), 
([      "action" :        "$N一聲長吟，$w向外一撥身體順勢急轉，突然急停向
        $n的身前躍去，口中長嘯「鳳凰展翅」棍梢橫掃$n的$l",    
       "force"  : 510, 
       "attack" : 180, 
       "dodge"  : -50, 
       "parry"  : -110, 
       "damage" : 410, 
       "damage_type": "淤傷" 
]), 
([       "action" : "$N雙目精光暴長，神情怒不可遏，一式[橫掃千軍]帶動
       無數道黑影,$w直擊$n的$l不待$n做出反應，$w竟然毫無章法似的向$n全身
       亂劈過去,速度極快$n只覺眼前盡是棍影而不見人",     
       "force"  : 560, 
       "attack" : 170, 
       "dodge"  : -65, 
       "parry"  : -120, 
       "damage" : 500, 
       "damage_type": "淤傷" 
]), 
}); 

string main_skill() { return "luowang-club"; } 

mapping sub_skills = ([ 
       "shunfeng-daqi"         : 120,        // 1 
       "xuehua-gaiding"        : 120,        // 2 
       "boyun-jianri"          : 120,        // 3
       "liuding-kaishan"       : 120,        // 4
       "wulong-baiwei"         : 120,        // 5
       "yanzi-chuanlin"        : 120,        // 6
       "jiaolong-chushui"      : 120,        // 7
       "dupi-huashan"          : 120,        // 8
       "xiniu-wangyue"         : 120,        // 9
       "luohan-bohu"           : 120,        // 10
       "tianma-xingkong"       : 120,        // 11
       "fenghuang-zhanchi"     : 120,        // 12
       "hengsao-qianjun"       : 120,        // 13
]); 

int get_ready(object me) 
{ 
       return 1; 
} 

int get_finish(object me) 
{ 
       if( query("str", me)<25 || me->query_str()<45 )
       { 
               tell_object(me, "你演練完畢，整個身體幾乎完全虛脱了，軟綿綿的提不起一點勁。\n"); 
               return 0; 
       } 

       if( query("con", me)<25 || me->query_con()<45 )
       { 
               tell_object(me, "你演練完畢，就覺得眼前金星亂冒，太陽穴突突的跳。\n"); 
               return 0; 
       } 

       if ((int)me->query_skill("force") < 200) 
       { 
               tell_object(me, "你演練完畢，幾乎虛脱，自己的內功水平看來還有待提高。\n"); 
               return 0; 
       } 

       if( query("max_neili", me)<1500 )
       { 
               tell_object(me, "你演練完畢，丹田提不起半點力來，看來應該繼續鍛鍊內力。\n"); 
               return 0; 
       } 

       if (random(10) < 5) 
       { 
               tell_object(me, "你對緊那羅王棍的奧妙頗有領悟，或許再演練一次就能夠融會貫通。\n"); 
               return 0; 
       } 

       tell_object(me, HIY "你一氣呵成，將緊那羅王棍從頭到尾演練了一變，心中頓悟，通\n" 
                           "曉了的緊那羅王棍奧妙精髓，融會貫通了棍法的精微之處，\n" 
                           "再也不是拆開使用那麼那麼簡單。\n" NOR); 
       return 1; 
} 

mapping query_sub_skills() 
{ 
       return sub_skills; 
} 

int valid_enable(string usage) { return usage=="club" ||  usage=="parry"; }   

int valid_learn(object me) 
{  
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("你手中無棍怎麼學習啊。\n");
       if( query("str", me)<25 && 
           query("con", me)<25 )
               return notify_fail("就你這身子骨還練緊那羅王棍？小心身體吃不消啊。\n"); 
       if( query("int", me)<20 )
               return notify_fail("算了吧，你先天悟性不好，怎麼能理解呢。\n"); 
       if ((int)me->query_skill("force") < 200) 
               return notify_fail("你的內功火候不夠，無法學習緊那羅王棍。\n"); 
       if ((int)me->query_skill("hunyuan-yiqi") < 200) 
               return notify_fail("你的混元一氣功火候不夠，無法學習緊那羅王棍。\n");
       if((int)me->query_skill("zui-gun") < 200) 
               return notify_fail("你的醉棍火候不夠，無法學習緊那羅王棍。\n"); 
       if ((int)me->query_skill("buddhism") < 200) 
               return notify_fail("你的禪宗心法火候不夠，無法學習於禪宗息息相關緊那羅王棍。\n"); 
       if( query("max_neili", me)<2000 )
               return notify_fail("你的內力這麼差，怎能融會貫通緊那羅王棍？\n"); 

       if ((int)me->query_skill("club", 1) < 200) 
               return notify_fail("你的基本棍法火候不夠，無法學習緊那羅王棍。\n"); 
       if ((int)me->query_skill("club", 1) < (int)me->query_skill("luowang-club", 1)) 
       return
   notify_fail("你的基本棍法水平有限，無法領會更高深的緊那羅王棍。\n"); 

       return 1; 
} 

mapping query_action(object me, object weapon) 
{ 
       mapping a_action;
       int level;

       level = (int)me->query_skill("luowang-club", 1);
       a_action = action[random(sizeof(action))]; 
       a_action["dodge"] -= level / 10;
       a_action["parry"] -= level / 10;
       a_action["attack"] += level / 10;
       a_action["force"] += level / 10;
       a_action["damage"] += level / 10;
       if( query_temp("action_flag", me) )
                set_temp("action_msg", "緊跟着", me);
       return a_action;
} 

int practice_skill(object me) 
{ 
        object weapon;
        if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "club" )
                return notify_fail("你手中無棍怎麼練啊。\n");
     if( query("qi", me)<150 )
               return notify_fail("你的體力太低了。\n"); 
       if( query("neili", me)<100 )
               return notify_fail("你的內力不夠練緊那羅王棍。\n"); 

       me->receive_damage("qi", 120); 
       addn("neili", -50, me);
       return 1; 
} 

mixed hit_ob(object me, object victim, int damage_bonus) 
{ 
        if (random(10) >= 1)
       { 
               victim->receive_wound("qi", damage_bonus); 
               victim->receive_wound("jing", damage_bonus); 
               return HIR "隨着一聲沉悶的哼聲傳來，$n的口中咳出了幾口鮮血！\n" NOR; 
       } 
} 

string perform_action_file(string action) 
{ 
       return __DIR__"luowang-club/" + action; 
} 

void skill_improved(object me) 
{ 
       int i; 
       string *sub_skillnames; 

       sub_skillnames = keys(sub_skills); 
       for (i = 0; i < sizeof(sub_skillnames); i++) 
               me->delete_skill(sub_skillnames); 
} 
void do_interlink(object me, object victim)
{
        int skill, i, j;
        object *enemy;
        object weapon;
    
        skill = me->query_skill("luowang-club", 1);
        if( skill>120 && !objectp(weapon=query_temp("weapon", me)) )
        {
                enemy=me->query_enemy();
                if (! sizeof(enemy)) return;
                for (i=0;i<sizeof(enemy);i++)
                {
                        for (j=0;j<(skill/(60*sizeof(enemy)));j++)
                        if( (me->is_fighting(enemy[i]) || enemy[i]->is_fighting(me)) && query("qi", enemy[i])>0 )
                        {
                                if (environment(me) == environment(enemy[i]))
                                {
                                        addn_temp("str", skill/10, me);
                                        addn_temp("dex", skill/10, me);
                                        COMBAT_D->do_attack(me,enemy[i],query_temp("weapon", me),TYPE_REGULAR);
                                }
                        } else break;
                }
                delete_temp("str", me);
                delete_temp("dex", me);
        }
}

