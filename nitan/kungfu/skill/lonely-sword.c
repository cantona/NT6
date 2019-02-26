// lonely-sword.c 獨孤九劍

#include <ansi.h>
#include <combat.h>

inherit SKILL;
string type() { return "martial"; }
string martialtype() { return "skill"; }
int action_po(object me, object victim, object weapon, int damage);//
int action_busy(object me, object victim, object weapon, int damage);
int action_damage(object me, object victim, object weapon, int damage);//
int action_parry(object me, object victim, object weapon, int damage);
int action_dodge(object me, object victim, object weapon, int damage);


string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

string *parry_msg = ({
        "卻見$n踏前一步，劍式斜指你的右臂，想要使$P閃身而退。\n",
        "$n以攻為守，以進為退，凝神運氣向$P猛攻快打地揮出方位大異的泰山"+(order[random(13)])+"「快活三」"NOR"三劍。\n",
        "$n劍法突變，劍勢伸縮不定，奔騰矯夭，逆使嵩山劍法的"+(order[random(13)])+"「天外玉龍」"NOR"企圖迫使$P變招。\n",
        "$n突然一劍點向$P的$l，雖一劍卻暗藏無數後着，$P手足無措，攻勢不由自主停了下來！\n",
        "$n不閃不避，舉劍閃電般使出"+(order[random(13)])+"「疊翠浮青」"NOR"反削$P的$l，想擋過你此招。\n",
        "$n突然使出青城派松風劍法的"+(order[random(13)])+"「鴻飛冥冥」"NOR"，可是方位卻有所偏差，長劍對着$P一絞，企\n圖突破$P的攻勢！\n",
        "$n挺劍一招象是"+(order[random(13)])+"「白雲出岫」"NOR"回刺$P的$l，企圖將$P的攻勢化解。\n",
        "只見$n不退反進，身如飄風，詭異地一式"+(order[random(13)])+"「天柱雲氣」"NOR"，動向無定不可捉摸地擋住了$P的\n進攻。\n",
        "$n不退反進，使出恆山劍招"+(order[random(13)])+"「綿裏藏針」"NOR"，森森劍氣充溢四周！架開了$P的這招\n",
});
mapping *action = ({
([      "action" : "但見$N挺身而上，$w一旋，一招彷彿泰山劍法的「" HIC "來鶴清"
                   "泉" NOR "」直刺$n的$l",
        "force" : 290,
        "attack": 145,
        "dodge" :-95,
        "parry" :-105,
        "damage": 160,
        "damage_type" : "刺傷"
]),
([      "action" : "$N奇詭地向$n揮出「" CYN "泉鳴芙蓉" NOR "」、「" MAG "鶴翔"
                   "紫蓋" NOR "」、「" HIG "石廩書聲" NOR "」、「" HIW "天柱"
                   "雲氣" NOR "」及「" HIY "雁回祝融" NOR "」衡\n山五神劍",
        "force" : 410,
        "attack": 135,
        "dodge" :-135,
        "parry" :-175,
        "damage": 270,
        "damage_type" : "刺傷"
]),
([
        "action" : "$N劍隨身轉，續而刺出十九劍，竟然是華山「" HIW "玉女十九劍"
                   NOR "」，但奇的是這十九劍便如一招，手法之快，\n直是匪夷所"
                   "思",
        "force" : 310,
        "attack": 115,
        "dodge" :-75,
        "parry" :-105,
        "damage": 205,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍勢忽緩而不疏，劍意有餘而不盡，化恆山劍法為一劍，向$n慢"
                   "慢推去",
        "force" : 280,
        "attack": 125,
        "dodge" :-55,
        "parry" :-125,
        "damage": 160,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍意突煥氣象森嚴，便似千軍萬馬奔馳而來，長槍大戟，黃沙千"
                   "裏，盡括嵩山劍勢擊向$n",
        "force" : 340,
        "attack": 160,
        "dodge" :-65,
        "parry" :-95,
        "damage": 220,
        "damage_type" : "刺傷"
]),
([      "action" : "卻見$N身隨劍走，左邊一拐，右邊一彎，劍招也是越轉越加狠辣，"
                   "竟化「" HIY "泰山十八盤" NOR "」為一劍攻\n向$n",
        "force" : 250,
        "attack": 135,
        "dodge" :-85,
        "parry" :-105,
        "damage": 210,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍招突變，使出衡山的「" HIB "一劍落九雁" NOR "」，削向$n"
                   "的$l，怎知劍到中途，突然轉向，大出$n\n意料之外",
        "force" : 240,
        "attack": 105,
        "dodge" :-125,
        "parry" :-175,
        "damage": 180,
        "damage_type" : "刺傷"
]),
([      "action" : "$N吐氣開聲，一招似是「" CYN "獨劈華山" NOR "」，手中$w向下"
                   "斬落，直劈向$n的$l",
        "force" : 345,
        "attack": 125,
        "dodge" :-115,
        "parry" :-145,
        "damage": 210,
        "damage_type" : "刺傷"
]),
([      "action" : "$N手中$w越轉越快，使的居然是衡山的「" HIW "百變千幻雲霧十"
                   "三式" NOR "」，劍式有如雲卷霧湧，旁觀\n者不由得目為之眩",
        "force" : 350,
        "attack": 145,
        "dodge" :-165,
        "parry" :-185,
        "damage": 250,
        "damage_type" : "刺傷"
]),
([      "action" : "$N含笑抱劍，氣勢莊嚴，$w輕揮，盡融「" HIR "達摩劍" NOR "」"
                   "為一式，閒舒地刺向$n",
        "force" : 330,
        "attack": 135,
        "dodge" :-95,
        "parry" :-125,
        "damage": 260,
        "damage_type" : "刺傷"
]),
([      "action" : "$N舉起$w運使「" CYN "太極劍" NOR "」劍意，劃出大大小小無"
                   "數個圓圈，無窮無盡源源不絕地纏向$n",
        "force" : 230,
        "attack": 105,
        "dodge" :-285,
        "parry" :-375,
        "damage": 140,
        "damage_type" : "刺傷"
]),
([      "action" : "$N神聲凝重，$w上劈下切左右橫掃，挾雷霆萬鈞之勢逼往$n，「"
                   HIR "伏摩劍" NOR "」的劍意表露無遺",
        "force" : 330,
        "attack": 185,
        "dodge" :-135,
        "parry" :-155,
        "damage": 280,
        "damage_type" : "刺傷"
]),
([      "action" : "卻見$N突然虛步提腰，使出酷似武當「" HIG "蜻蜓點水" NOR
                   "」的一招",
        "force" : 180,
        "attack": 95,
        "dodge" :-285,
        "parry" :-375,
        "damage": 130,
        "damage_type" : "刺傷"
]),
([      "action" : "$N運劍如風，劍光霍霍中反攻$n的$l，嘗試逼$n自守，劍招似是"
                   "「" HIR "伏魔劍" NOR "」的「" HIR "龍吞式" NOR "」",
        "force" : 270,
        "attack": 155,
        "dodge" :-135,
        "parry" :-165,
        "damage": 260,
        "damage_type" : "刺傷"
]),
([      "action" : "$N突然運劍如狂，一手關外的「" HIY "亂披風劍法" NOR "」，"
                   "猛然向$n周身亂刺亂削",
        "force" : 330,
        "attack": 145,
        "dodge" :-175,
        "parry" :-255,
        "damage": 220,
        "damage_type" : "刺傷"
]),
([      "action" : "$N滿場遊走，東刺一劍，西刺一劍，令$n莫明其妙，分不出$N劍法"
                   "的虛實",
        "force" : 310,
        "attack": 165,
        "dodge" :-115,
        "parry" :-135,
        "damage": 270,
        "damage_type" : "刺傷"
]),
([      "action" : "$N抱劍旋身，轉到$n身後，雜亂無章地向$n刺出一劍，不知使的是"
                   "什麼劍法",
        "force" : 330,
        "attack": 135,
        "dodge" :-175,
        "parry" :-215,
        "damage": 225,
        "damage_type" : "刺傷"
]),
([      "action" : "$N突然一劍點向$n的$l，雖一劍卻暗藏無數後着，$n手足無措，不"
                   "知如何是好",
        "force" : 360,
        "attack": 160,
        "dodge" :-150,
        "parry" :-285,
        "damage": 210,
        "damage_type" : "刺傷"
]),
([      "action" : "$N劍挾刀勢，大開大闔地亂砍一通，但招招皆擊在$n攻勢的破綻，"
                   "迫得$n不得不守",
        "force" : 510,
        "attack": 225,
        "dodge" :-135,
        "parry" :-175,
        "damage": 190,
        "damage_type" : "刺傷"
]),
([      "action" : "$N反手橫劍刺向$n的$l，這似有招似無招的一劍，威力竟然奇大，"
                   "$n難以看清劍招來勢",
        "force" : 334,
        "attack": 135,
        "dodge" :-155,
        "parry" :-185,
        "damage": 280,
        "damage_type" : "刺傷"
]),
([      "action" : "$N舉劍狂揮，迅速無比地點向$n的$l，卻令人看不出其所用是什麼"
                   "招式",
        "force" : 380,
        "attack": 125,
        "dodge" :-145,
        "parry" :-215,
        "damage": 230,
        "damage_type" : "刺傷"
]),
([      "action" : "$N臉上突現笑容，似乎已看破$n的武功招式，胸有成竹地一劍刺向"
                   "$n的$l",
        "force" : 390,
        "attack": 155,
        "dodge" :-185,
        "parry" :-275,
        "damage": 230,
        "damage_type" : "刺傷"
]),
});

mapping *action2 = ({
([      "action" : "$N隨手一劍指向$n，落點正是$n的破綻所在，端的是神妙無倫，不"
                   "可思議",
        "force" : 370,
        "attack": 135,
        "dodge" :-185,
        "parry" :-300,
        "damage": 238,
        "post_action" : (: action_busy :),
        "damage_type" : "刺傷"
]),
([
        "action" : "$N將$w隨手一擺，但見$n自己向$w撞將上來，神劍之威，當真人所"
                   "難測",
        "force" : 410,
        "attack": 155,
        "dodge" :-300,
        "parry" :-300,
        "damage": 280,
        "post_action" : (: action_damage :),
        "damage_type" : "刺傷"
]),
([      "action" : HIW "但見$N手中$w" HIW "破空長吟，平平一劍刺向$n，毫無招式可言",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_parry :),
        "damage_type" : "刺傷"
]),
([      "action" : HIW "$N揉身欺近，輕描淡寫間隨意刺出一劍，簡單之極，無招無式",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_dodge :),
        "damage_type" : "刺傷"
]),
([      "action" : HIW "$N身法飄逸，神態怡然，劍意藏於胸中，手中$w" HIW "隨意揮灑而出，獨孤"
                   "九劍已到了收發自如的境界",
        "force" : 600,
        "attack": 300,
        "dodge" :-300,
        "parry" :-300,
        "damage": 460,
        "post_action" : (: action_po :),
        "damage_type" : "刺傷"
]),
});

int valid_enable(string usage) { return usage=="sword" || usage=="parry"; }

string query_parry_msg(string limb)
{
        return parry_msg[random(sizeof(parry_msg))];
}

int valid_learn(object me)
{
        object ob;

        if( !(ob=query_temp("weapon", me) )
        ||  query("skill_type", ob) != "sword" )
                return notify_fail("你必須先找一把劍才能練劍法。\n");

        if( query("int", me)<34 )
                return notify_fail("你的天資不足，無法理解獨孤九劍的劍意。\n");

        if( query("character", me) == "心狠手辣" )
                return notify_fail("你一心想殺盡敵人，沒能理解獨孤九劍的的真正含義。\n");

        if( query("character", me) == "陰險奸詐" )
                return notify_fail("你一心想怎麼學好劍法去害人，結果沒能理解獨孤九劍。\n");

        if( query("character", me) == "光明磊落" )
                return notify_fail("你心中暗道：什麼獨孤九劍，亂七八糟的，沒有半點氣勢。\n");

        if( me->query_skill("sword", 1) < me->query_skill("lonely-sword", 1) )
                return notify_fail("你的基本劍法造詣有限，無法理解更高深的獨孤九劍。\n");

        return 1;
}
int practice_skill(object me)
{
        return notify_fail("獨孤九劍只能通過「總訣式」來演練。\n");
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
        int lvl;
        lvl = (int) me->query_skill("lonely-sword", 1);
        if( objectp(weapon) && query("id", weapon) == "xuantie jian" )
        {
                if( me->query_str() >= 60 && me->query_int() >= 36
                &&  random(lvl) > 120
                &&  me->query_skill("force")>150 && query("neili", me) > 400 )
                {
                        addn("neili", -100, me);
                        return ([
                                "action": HIR "$N臉色凝重虔誠，緩緩舉起玄鐵重劍，突然躍起身劍合一，"
                                          "馭劍化為一道黑氣向$n衝刺而去" NOR,
                                "damage": 900,
                                "attack": 300,
                                "dodge" :-300,
                                "parry" :-300,
                                "damage_type" : "刺傷"
                        ]);
                }
        }

        if( query("lonely-sword/nothing", me) )
               return action2[random(sizeof(action2))];

        else   return action[random(sizeof(action))];
}


int action_damage(object me, object victim, object weapon, int damage)
{
        string msg;
        string*limbs=query("limbs", victim);
        int dam;
        int skill= me->query_skill("lonely-sword", 1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage == RESULT_DODGE && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/2 ) //躲過
        {
                addn("neili", -50, me);
                message_combatd("\n$N一聲長嘯:"HIW"「劍旋離身，劍嘯震山河」"NOR", 瞬間劍芒大作,朝$n激射而至！\n",me,victim);
                dam=skill*2+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi", dam);
                msg = COMBAT_D->damage_msg(dam, "刺傷"); //此次傷害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg, me, victim);
                COMBAT_D->report_status(victim);
                return 1;
        } else 
        if( damage > 0 && !victim->is_busy()
        &&  skill > 100
        &&  query("neili", me)>100
        &&  random(skill) > victim->query_skill("force",1)/4)   //打中對方
        {
                addn("neili", -50, me);
                message_combatd("\n$N突然悟出"HIW"「練精化氣, 練氣化神, 練神還虛」"NOR"之真理, 手中長劍突然消失, 朝$n飛至！\n",me,victim);
                dam=skill+query_temp("apply/damage", me);
                dam-=query_temp("apply/armor", victim);
                if (dam < 0 ) dam = 0;
                victim->receive_damage("qi",dam);
                msg = COMBAT_D->damage_msg(skill*2, "刺傷"); //此次傷害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
        }
        return 1;
}

int action_po(object me, object victim, object weapon, int damage)
{
        // 破對方武功、內功  為終極效果
        int skill= me->query_skill("lonely-sword", 1);
        string v_force = victim->query_skill_mapped("force");
        int jiali;
        if( !me->is_fighting(victim) ) return 0;
        if( damage > 0 )// 打中對方 破內功 或者破內力
        {
                if( v_force && skill > 250
                &&  random(skill/2) > random(victim->query_skill("force"))
                &&  random(skill) > 200
                &&  victim->query_map_skill("force")
                &&  objectp(weapon=query_temp("weapon", me) )
                &&  random(3)==1 )
                {
                        addn("neili", -100, me);
                        victim->map_skill("force");
                        message_combatd(HIC "$N一劍得手，劍招源源而出，劍尖直刺$n丹田！\n",me,victim);
                        message_combatd(RED "$n只覺混身如遭電擊，真氣勁力紊亂難控，已然不能施展"+to_chinese(v_force)+"！\n" NOR,me,victim);
                        return 1;
                } else 
                if( random(me->query_skill("lonely-sword",1)) > 100 &&
                    random(me->query_skill("sword",1))>100 &&
                    me->query_skill("force",1) > 120 &&  
                    !victim->is_busy() ) {
                        addn("neili", -50, me);
                        if( query("neili", victim)>600 )
                                addn("neili", -500, victim);
                        else
                                set("neili", 0, victim);
                        message_combatd(HIC "\n$N一劍得手，劍招源源而出，欲將$n團團困住！\n",me,victim);
                        message_combatd(HIM "$n急運內力，使出渾身解數，方才脱出劍圈！\n"NOR , me, victim);
                        return 1;
                }
        }
        else if( damage == RESULT_DODGE && !victim->is_busy()) //躲過  震懾對方
        {
                addn("neili", -50, me);
                message_combatd(HIY "$n只覺$N劍中暗藏無數玄機，稍一膽怯，不敢攻上前去！\n"NOR,me,victim);
                victim->start_busy(1+random(skill/50));
                return 1;
        }
        else if ( damage == RESULT_PARRY ) //對手招架住 可順勢再創對手
        {
                jiali=query("jiali", me);
                if (!jiali) jiali=10;
                if( random(skill)>140 )
                {
                        addn("neili", -50, me);
                        message_combatd(HIC "$N相交一招，已然看破$n武功套路，胸有成竹地刺出一劍!\n",me,victim);
                        victim->receive_wound("qi", (random(jiali)*2+100));
                        message_combatd(HIM"$N劍氣縱橫! 一道劍氣劃過了$n的胸口。結果鮮血狂噴!\n"NOR,me,victim);
                        COMBAT_D->report_status(victim,1);
                }
                return 1;
        }
        return 1;

}

int action_busy(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        if( !me->is_fighting(victim) ) return 0;
        if( damage <= 0 && !victim->is_busy()
        &&  skill > 100
        &&  objectp(weapon=query_temp("weapon", me) )
        &&  query("neili", me)>100
        &&  random(query("combat_exp", me))>query("combat_exp", victim)/3)//威力極小,如果沒有上兩個則包括躲過和招架
        {
                addn("neili", -50, me);
                message_combatd("$N頓然領悟了"HIW"「劍在神先, 綿綿不絕」"NOR"之真意, 劍尖瞬間爆出無數大大小小,\n正反斜直各種各樣的圓圈, 將$n團團困住。\n",me,victim);
                victim->start_busy(2+random(skill/50));
                return 1;
        } else 
        if( damage > 0  && !victim->is_busy()
        &&  skill > 100
        &&  random(skill) > victim->query_skill("force",1)/3)
        {
                addn("neili", -30, me);
                message_combatd(CYN"$N以意馭劍，畫出數個"RED"圓圈"CYN"，左右兼顧，將$n纏在正中！\n" NOR,me,victim);
                victim->start_busy(1+random(skill/50));
        }
        return 1;
}

int action_dodge(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( random(me->query_skill("lonely-sword",1)) >= 200 &&
            random(me->query_skill("sword",1))>180 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("dodge") ) {
                addn("neili", -50, me);
                victim->map_skill("dodge");
                if( !victim->is_busy() )
                        victim->start_busy(random(3)+1);

                msg = HIC "\n$N突然舉劍一刺，劍招隨便無章，卻莫明奇妙地突破了$n的攻勢，大出$n意料！\n" ;
                msg += HIR"$n大吃一驚，竟然忘了閃避！\n"NOR;
                message_combatd(msg,me,victim);
                return 1;
        }
        else if( damage <= 0 && random(skill) > random(victim->query_skill("dodge",1)/3))
        {
                addn("neili", -50, me);
                message_combatd("\n卻見$N飄身而上，半空中舉劍上挑，劍光已封住了$n身週數尺之地，攻得精巧無比！\n",me,victim);
                victim->receive_damage("qi",skill/2);
                msg = COMBAT_D->damage_msg(skill/2, "刺傷");
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg=replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
                return 1;
       }
       return 1;
}

int action_parry(object me, object victim, object weapon, int damage)
{
        int skill=me->query_skill("lonely-sword",1);
        string msg;
        string*limbs=query("limbs", victim);
        if( !me->is_fighting(victim)) return 0;
        if( damage == RESULT_DODGE &&
            random(me->query_skill("lonely-sword",1)) > 140 &&
            random(me->query_skill("sword",1))>140 &&
            me->query_skill("force",1) >= 200 &&
            objectp(weapon=query_temp("weapon", me)) &&
            victim->query_map_skill("parry") ) {
                addn("neili", -50, me);
                victim->map_skill("parry");
                if( !victim->is_busy() )
                        victim->start_busy(random(2)+1);

                msg = HIC "\n$N舉劍反攻，後發先至地刺向$n，不僅把$n招術封死，更進一步發出攻擊！\n" NOR;
                msg += HIY"$n難以看清劍招來勢,竟然忘了招架！\n"NOR;
                message_combatd(msg,me,victim);
        }
        else if (damage <= 0 && random(skill) > random(victim->query_skill("parry",1)/3))
        {
                addn("neili", -50, me);
                msg = "\n$N一個箭步縱到$n身前，手腕微顫，揮劍斜撩，橫削$n$l，劍法極盡靈動輕捷\n";
                victim->receive_damage("qi",skill/2);
                msg += COMBAT_D->damage_msg(skill/2, "刺傷"); //此次傷害
                msg = replace_string(msg, "$l", limbs[random(sizeof(limbs))]);
                msg = replace_string(msg,"$w",query("name", weapon));
                message_combatd(msg,me,victim);
                COMBAT_D->report_status(victim);
       }
}

int double_attack() { return 1; }

int query_effect_parry(object attacker, object me)
{
        object weapon;
        int lvl;

        if( !objectp(weapon=query_temp("weapon", me)) ||
            query("skill_type", weapon) != "sword" )
                return 0;

        lvl = me->query_skill("lonely-sword", 1);
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
        lvl = me->query_skill("lonely-sword", 1);

        if (lvl >= 20
         && !query("can_perform/lonely-sword/jue", me))
        {
                tell_object(me, HIC "你通曉了獨孤九劍「" HIW "總決式" HIC "」的奧祕。\n" NOR);
                set("can_perform/lonely-sword/jue", 1, me);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
                me->improve_skill("martial-cognize", 1500000);
        }

        if (lvl > 120
         && query("can_perform/lonely-sword/qi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/qi",random(i))<100 )
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
         && query("can_perform/lonely-sword/po", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/po",random(i))<100 )
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
         && query("can_perform/lonely-sword/yi", me) <= 100 )
        {
                if( me->add("can_perform/lonely-sword/yi",random(i))<100 )
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

        if( query("lonely-sword/nothing", me) )
                return 300;

        else   return 200;
}

mixed valid_damage(object ob, object me, int damage, object weapon)
{
        mixed result;
        int ap, dp, mp;
        object m_weapon;

        if ((int) me->query_skill("lonely-sword", 1) < 120
         || !(m_weapon=query_temp("weapon", me) )
        ||  ! living(me)
         || query("skill_type", m_weapon) != "sword" )
                return;

        mp = ob->query_skill("count", 1);
        ap = ob->query_skill("parry") + mp;
        dp = me->query_skill("parry", 1) / 2 +
        me->query_skill("lonely-sword", 1);

        // 無招
        if( query("lonely-sword/nothing", me) )
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
                        ob->start_busy(2 + random(2));
                        return result;
                }

        }

        if (ap / 3 + random(ap) < dp)
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

        lvl = me->query_skill("lonely-sword", 1);

        if( query("neili", me)<300
        ||  me->query_skill_mapped("sword") != "lonely-sword"
         || !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "sword"
         || !query("lonely-sword/nothing", me) )
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
                message_combatd(HIC "\n$N" HIC "隨意揮灑手中的" + weapon->name() +
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
                    ! random(2) &&
                    !query_temp("lonely-sword/lian", me) )
                {
                        weapon=query_temp("weapon", me);
                        message_combatd(HIY "\n$N" HIY "胸藏劍意，手中" + weapon->name() + HIY
                                     "隨意揮灑而出，速度之快，方位之準，\n顯是獨孤九劍已達到"
                                     "收發自如的境界。\n" NOR,
                                     me, victim);

                        addn("neili", -270, me);

                        set_temp("lonely-sword/lian", 1, me);
                        for (i = 0; i < 5; i++)
                        {
                                if (! me->is_fighting(victim))
                                        break;

                                if (! victim->is_busy() && random(2) == 1)
                                        victim->start_busy(1);

                                COMBAT_D->do_attack(me, victim, weapon, 0);
                        }
                        delete_temp("lonely-sword/lian", me);

                }
                break;
        }
}

int learn_bonus() { return 0; }
int practice_bonus() { return 0; }
int success() { return 5; }
int power_point(object me) { return 1.0; }

int valid_effect(object me, object weapon, string name, int skill)
{
}
string perform_action_file(string action)
{
        return __DIR__"lonely-sword/" + action;
}

int help(object me)
{
        write(HIC"\n獨孤九劍："NOR"\n");
        write(@HELP

    “獨孤九劍，有進無退！”
    創制這套劍法的獨孤求敗前輩，名字叫做‘求敗’，他畢生想
求一敗而不可得，這劍法施展出來，天下無敵，當年他仗劍江湖，
無敵於天下，連找一個對手來逼得他回守一招都不可得，委實令人
可驚可佩。
    無招勝有招，敵強我更強。獨孤九劍不含招式，有招既無招，
無招亦有招。獨孤九劍要旨在於「悟」，不可拘泥不化，講究料敵
機先，出奇制勝。通曉了九劍劍意，則無所施而不可。
    獨孤九劍，自“總訣式”、“破劍式”、“破刀式”以至“破
槍式”、“破鞭式”、“破索式”、“破掌式”、“破箭式”而到
第九劍“破氣式”。九劍的第一招“總訣式”，有種種變化，用以
體演總訣，便於修習。第二招“破劍式”，用以破解普天下各門各
派的劍法。第三招“破刀式”，用以破解單刀、雙刀、柳葉刀、鬼
頭刀、大砍刀、斬馬刀種種刀法。第四招“破槍式”，包括破解長
槍、大戟、蛇矛、齊眉棍、狼牙棒、白蠟杆、禪杖、方便鏟種種長
兵刃之法。第五招“破鞭式”，用以破解鋼鞭、鐵鐗、點穴橛、拐
子、蛾眉刺、匕首、板斧、鐵牌、八角槌、鐵椎等等短兵刃，第六
招“破索式”，破解的是長索、軟鞭、三節棍、鏈子槍、鐵鏈、漁
網、飛錘流星等等軟兵刃。第七招“破掌式”，破的是拳腳指掌上
的功夫，將長拳短打、擒拿點穴、魔爪虎爪、鐵沙神掌，諸般拳腳
功夫盡數包括內在。第八招“破箭式”這個“箭”字，則總羅諸般
暗器，練這一劍時，須得先學聽風辨器之術，不但要能以一柄長劍
擊開敵人發射來的種種暗器，還須借力反打，以敵人射來的暗器反
射傷敵。第九劍“破氣式”，是為對付身具上乘內功的敵人而用，
神而明之，存乎一心。

        學習要求：
                只能向風清揚學習
                紫霞神功100級
                內力600
HELP
        );
        return 1;
}
