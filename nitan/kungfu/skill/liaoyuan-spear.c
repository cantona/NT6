// /kungfu/skill/liaoyuan-spear.c
// liaoyuan-spear.c 燎原槍法
// wuyue(08,1,22)
// wuyue(08.1.23)
#include <ansi.h>
#include <combat.h>
inherit SKILL;

mapping *action = ({
([
"action":"$N躍在半空，一招「大鵬展翅」，手中$w已化成無數槍影，令$n眼花繚亂，不知所措，連連倒退",
         "force" : 180,
         "dodge" : 20,
         "parry" : 20,
        "damage": 20,
         "lvl" : 0,
         "skill_name" : "大鵬展翅",
         "damage_type":"刺傷"
]),
([
"action":"$N挺$w將$n的招式架住，順勢一招「走馬回槍」，$w上下左右飛快攪動，身隨槍走，向$n壓了下來",
         "force" : 200,
         "dodge" : 10,
         "parry" : 15,
        "damage": 100,
         "lvl" : 30,
         "skill_name" : "走馬回槍",
         "damage_type":"刺傷"
]),
([
"action":"$N使一招「迎門三不過」，手中$w連續刺向$n面門，哽嗓，前心",
         "force" : 220,
         "dodge" : 15,
         "parry" : 20,
        "damage": 40,
         "lvl" : 60,
         "skill_name" : "迎門三不過",
         "damage_type":"刺傷"
]),
([
"action":"$N一個跨步，使一招「高山流水」，手中$w勢若飛瀑刺向$n的$l",
         "force" : 240,
         "dodge" : 20,
         "parry" : 25,
        "damage": 60,
         "lvl" : 80,
         "skill_name" : "高山流水",
         "damage_type":"刺傷"
]),
([
"action":"$N一招「九蓮寶燈」，身形如電，繞着$n飛快奔跑，手中$w一招快似一招，剎那間向$n連打出三十六槍",
         "force" : 280,
         "dodge" : 30,
         "parry" : 30,
        "damage": 80,
         "lvl" : 100,
         "skill_name" : "九蓮寶燈",
         "damage_type":"刺傷"
]),
([
"action":
"$N一按槍把，一招「野火燎原」抖出五朵槍花。上下左右，虛虛實實刺向$n全身要害",
         "force" : 260,
         "dodge" : 30,
         "parry" : 40,
        "damage": 100,
         "lvl" : 120,
         "skill_name" : "野火燎原",
         "damage_type":"刺傷"
]),
([
"action":"$N大喝一聲，一招「飛龍在天」，$w脱手飛出，夾着勁風射向$n的前心，隨即搶到$n的身後，伸手又把$w抄在手中",
         "force" : 300,
         "dodge" : 20,
         "parry" : 30,
        "damage": 80,
         "lvl" : 130,
         "skill_name" : "飛龍在天",
         "damage_type":"刺傷"
]),
([
"action":"$N使一招「風掃梅花」，身體不停地旋轉，右手$w隨身轉動，風雷電掣般向$n的$l掃去",
         "force" : 300,
         "dodge" : 20,
         "parry" : 30,
        "damage": 80,
         "lvl" : 130,
         "skill_name" : "風掃梅花",
         "damage_type":"砸傷"
]),
([
"action":"$N回身擰腰，右手虛握，一招「撥雲瞻日」，$w中宮直進，中正平和地刺向$n的$l",
         "force" : 350,
         "dodge" : 20,
         "parry" : 30,
        "damage": 120,
         "lvl" : 130,
         "skill_name" : "撥雲瞻日",
         "damage_type":"刺傷"
]),
([
"action":"只見$N一個斜跨，使個「舉火燒天勢」，手中$w帶出一道寒氣，由下而上疾挑$n$l",
         "force" : 350,
         "dodge" : 20,
         "parry" : 30,
        "damage": 100,
         "lvl" : 150,
         "skill_name" : "舉火燒天勢",
         "damage_type":"刺傷"
]),
});

string *parry_msg = ({
"$N持槍斜引，長槍橫過，使$n竟無出招之處。\n",
"$N手中長槍斜指，往$n身前一搭，結果$n的力道被卸在一旁！",
"$N雙手交錯，持槍劃了兩個圓圈，罡氣護住全身，竟無半分空隙，將$n之來勢化解與無形。\n",
"只見$N使出四兩撥千斤之巧勁，長槍斜引，將$n的攻擊引在一旁！\n",
"$N以數十招槍法混成守勢，似有千百柄長槍護住全身，圓轉如意，竟無半分破綻。\n",
"$n身形繞向$N背後，$N身隨槍轉，反手圈轉輕易地化解！\n"
});

string *msg = ({
HIG"$N神情蕭索，一式「野火燎原」右手長槍揚手揮灑，虛實不定"NOR,
MAG"但見$N槍法吞吐開合、陰陽動靜，實已到了草木為兵的絕詣"NOR,
HIW"$N手中$w"HIW"雖使得極快，卻絲毫聽不到金刃劈風之聲，足見槍勁之柔韌已達於化境"NOR,
HIC"$N不疾不徐的漫步揚長而步，遇到$n招數，$N$w"HIC"一顫，便是一縷金光閃出"NOR,
HIC"$N凝望$n招式，出槍以蜿蜒之勢、身處莊穩之形，宛如旭日東昇，如金蛇萬道，閃爍不定"NOR,
HIB"$N槍法突變，招式凌厲狠辣，以極渾厚內力，出極精妙招數，青光盪漾"NOR,
CYN"$N$w隨手一招打出，以己之鈍，擋敵之無鋒"NOR,
HIC"$N猛然攻出招，招招都未曾使老，走勢猶如浪潮一般，緩緩湧向$n"NOR,
MAG"$N$w"MAG"在空中劃成大圈，右手戳出，竟似也發出嗤嗤微聲"NOR,
HIW"$N一槍刺到，青光閃閃，發出嗤嗤聲響，內力極強"NOR,
HIW"$N左手$w"HIW"不住的抖動，罩向$n上盤七大要穴，槍尖急顫，看不出攻向何處"NOR,
MAG"$N功勁一加運開，手中$w"MAG"槍勢綿綿不絕，絕無破綻"NOR,
CYN"$N手裏$w"CYN"使得心應手，熟極而流，招數精奇，輕翔靈動，變幻不測，突然抖腕直向$n的$l刺到"NOR,
HIW"$N以意馭槍，千變萬化，無窮無盡，每一招都看似平淡，實則蓄勢以待，深藏不露"NOR,
HIB"$N以意馭槍，綿綿不絕，看似柔軟無力，實則千變萬化，無窮無盡"NOR,
HIB"$N朗聲長嘯，槍法縱橫變化，奇幻無方，$w"HIB"在其內力運使之下青光閃閃，威不可擋"NOR,
HIC"$N心中竟無半點渣滓，以意運槍，$w"HIC"每發一招，便有一道青光射向$n"NOR,
HIR"$N槍法吞吐開合、陰陽動靜，將無招勝有招中最精要之處都發揮了出來，功勁一加運開，綿綿不絕"NOR,
HIR"$N左手$w"HIR"緩緩向前劃出，成一弧形。$n只覺一股森森寒氣，直逼過來"NOR,
CYN"$N左手$w"CYN"不住抖動，突然平刺，槍尖急顫，看不出攻向何處。$N這一招中籠罩了$n上盤七大要穴"NOR,
HIW"$N招數未曾使老，已然圈轉。突然之間，$n眼前出現了幾個白色光圈，大圈小圈，正圈斜圈，閃爍不已"NOR,
});

int valid_enable(string usage) { return  (usage == "spear") || (usage =="parry"); }

int valid_learn(object me)
{
        if (!me->query("sg/tzjj"))
             return notify_fail("你沒有得到上官幫主許可，怎麼能偷學燎原槍法。\n");
         if ((int)me->query("max_neili") < 1500)
                return notify_fail("你的內力不夠。\n");
         if ((int)me->query_skill("force", 1) < 160)
                return notify_fail("你的內功火候太淺。\n");
         if((int)me->query_skill("spear",1) <=120)
      		return notify_fail("你的基本槍法火候不足，難以領悟燎原槍法。\n");
         return 1;
}
 
string perform_action_file(string action)
{
        return __DIR__"liaoyuan-spear/" + action;
}
string query_skill_name(int level)
{
         int i;
         for(i = sizeof(action)-1; i >= 0; i--)
                 if(level >= action[i]["lvl"])
                         return action[i]["skill_name"];
}

int double_attack(object me)
{	
        return 1;
   	if ( me->query_skill("liaoyuan-spear", 1) >= 80
     	&& me->query_skill_mapped("spear") == "liaoyuan-spear"
     	&& me->query("zhou/hubo"))
             	return 1;
}

mapping query_action(object me, object weapon)
{
         int i, level, lvl;
         object target;
	string msg1;
         mapping pre;
         string *skill, a, b;
         
         level   = (int) me->query_skill("liaoyuan-spear",1);
         lvl = (int)me->query_skill("super-strike", 1);
    
        if (random(me->query_skill("spear", 1)) > 100 
        && random(me->query_skill("liaoyuan-spear", 1)) > 100 
        && me->query_skill("force") > 100
	&& random(10)>6
        && me->query("neili") > 30 ) {
                me->add("neili", -20);
                return ([
 			"action": HIG"$N渾身看似破綻百出，$n卻覺得無處下手，不經意間$N手中"+weapon->query("name")+""HIG"虛刺幾下，$n一不留神就被$N一擊命中。"NOR,
                  	"force": level+level/2+level/3,
                  	"parry": level+level/4,
                  	"dodge": level+level/4,
                  	"damage": level+level/2,
                  	"damage_type": "刺傷"
                ]);
        }
    
            if(me->query_temp("canyun"))
			{
				switch(me->query_temp("canyun"))
				{
				case 2: msg1 = HIY"$N出招穩凝如山，似乎其中破綻百出，手忙腳亂，其實似守實攻，大巧若拙，每一處破綻中都隱伏着厲害無比的陷阱。"NOR; break;
				case 1: msg1 = HIR"$N眼見對方已陷入重圍，再也不能全身而退，當下持槍回擊，陡然圈轉，呼的一響，往$n$l上擊了下去。"NOR; break;
				default: msg1 = HIW"$N突然大喝一聲，縱身而上，手中$w"HIW"猶如狂風驟雨，使出「風捲殘雲」，漫天槍影帶着氣浪有如怒海狂滔一般！"NOR;break;
				}
				me->add_temp("canyun", -1);      
				return ([
                        "action":msg1, 
                        "force" : level+level/3,
                        "dodge":level+level/3 ,
  "damage":level ,
                        "parry": level/2,
                        "damage_type" : "刺傷",
              ]);
            }
    
        if (me->query_temp("slbw")) { 
  me->delete_temp("slbw");             
                return ([  
                        "action" : HIC"但見$N硬接了$n這一招，執槍緊接着向後一擺，一招「神龍擺尾」出其不意地點在了$n的$l上！"NOR,
                        "force":level+level/2,
                        "dodge": level/2,
  "damage":level+level/2 ,
                        "parry": level/2,
                        "damage_type" : "刺傷",
                        ]);
                }

 if( level > 350 ){   
        	if( weapon ){
        		switch(weapon->query("material")){
    				case "wood":
    				case "bamboo": 
    				case "paper":
        				weapon->set_temp("no_weapon_cut", 1); break;
        			default: break;
 }
}
        
        if( level > 450){
  return ([
                        "action":msg[random(sizeof(msg))],
   "damage":level + level/6,
                        "damage_type":"刺傷",
                        "dodge": level/2,
                	"parry":   level/2,
                        "force":level+random(level/2)
                ]);
        }
        
        if( level > 350
	&& random(10)>6){
  return ([
                        "action":msg[random(sizeof(msg))],
                        "damage":level + level/16,
                        "damage_type":"刺傷",
                        "dodge": level/5,
                	"parry":   level/5,
                        "force":level+random(level/5)
                ]);
        }
 }         
         if ( level >= 200 && lvl >= 200 && random(level) > lvl / 2
         && objectp(target = me->select_opponent())
         && objectp(weapon = me->query_temp("weapon"))
         && me->query_skill_mapped("strike") == "super-strike" 
         && me->query_skill_prepared("strike") == "super-strike" 
         && me->query("neili") > 300 && me->query("jingli") > 100 ) {
         	pre = me->query_skill_prepare();
        	skill = keys(pre);     
        	for (i=0; i<sizeof(skill); i++){
                	if(skill[i]=="strike") continue; 
                	a = skill[i];
                	b = pre[skill[i]];
                	me->prepare_skill(skill[i]);
        	}
        	
                weapon->unequip();
                COMBAT_D->do_attack(me, target, me->query_temp("weapon"), 2);
                weapon->wield();
                me->prepare_skill(a,b);
                me->add("neili", -15);
                me->add("jingli", -10);
         }
        


         for(i = sizeof(action); i > 0; i--)
                 if(level >= action[i-1]["lvl"])
                         return action[NewRandom(i, 20, level/5)];
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
    	object weapon, weapon1;
    	int i;    
    	weapon = me->query_temp("weapon");
    	weapon1= victim->query_temp("weapon");

	if( !objectp(weapon) ) return;
	i = me->query_skill("liaoyuan-spear", 1);
	
    	if(weapon1 && me->query("jiali")
       	&& me->query("max_neili") > 1200 && me->query("neili") > 1000 && random(10) >= 7
       	&& random(me->query_str()) > 30 
       	&& me->query_skill_mapped("parry") == "liaoyuan-spear"
       	&& random(me->query("combat_exp")) > victim->query("combat_exp")/4){
      		message_vision(HIM"$N持槍斜引，"+weapon->name()+HIM"平搭在$n"+weapon1->name()+HIM"背脊上，勁力傳出，"+weapon1->name()+HIM"登時一沉！\n"NOR, me,victim);
      		if(random(me->query("str")) > victim->query("str")/3){           
           		me->add("neili", -50);
           		message_vision(HIR"$N招式漸見澀滯，只覺得手中"+weapon1->name()+HIR"不斷的在增加重量，一個把持不定，脱手飛出！\n"NOR, victim);
           		weapon1->unequip();
           		weapon1->move(environment(victim));
           	}
      		else {
           		message_vision(HIY"$N一招使出，真力運得不足，被"+weapon->name()+HIY"帶着連轉幾個圈子，手中"+weapon1->name()+HIY"一震，險些脱手！\n"NOR, victim);
           		victim->add_busy(3);
           	}
    	}
    	
    	else if( i > 350 ){
    		if( i < 350 ) return i/5;
    		switch(weapon->query("material")){
    			case "wood":
    			case "bamboo": 
    			case "paper":
    					if( random(i) > 250 
    					&& !victim->query_temp("lost_attack") 
   && random(me->query_str()+me->query_con()) > random(victim->query_int()*2) 
	&& random(10)>6){
    						victim->add_temp("lost_attack", 1+random(3));
    						message_vision(HIC"$P越鬥越害怕，被$p帶得招式漸見澀滯！\n"NOR, victim, me);
    						i *= 2;
    					}
    					
    					if( i > 450 ) i *= 2;
    				 	i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    					break;
    			default: 	
    					if( i > 450 ) {
    						if( random(i) > 250 
    						&& !victim->query_temp("lost_attack") 
   && random(me->query_str()+me->query_con()
	&& random(10)>6) > random(victim->query_int()*2) ){
    							victim->add_temp("lost_attack", 1+random(3));
    							message_vision(HIC"$P越鬥越害怕，被$p帶得招式漸見澀滯！\n"NOR, victim, me);
    							i += random(i);
    						}
    						i *= 2;
    				 		i += me->query_skill("force") * 2 + (me->query("jiali") * (10+random(10)));
    						break;
    					}
}
}

        if(random(me->query_skill("liaoyuan-spear", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {      
            victim->apply_condition("hot_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("hot_poison"));
        }
}


int ob_hit(object ob, object me, int damage)
{
        string msg;
        int i, neili,p,j,skill, neili1;
        skill = me->query_skill("liaoyuan-spear", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if(!living(ob)) return damage;
        if(neili < 300) return damage;
        if(living(me) &&
        userp(me) &&
        random(me->query_str()) > ob->query_str()/4 &&
        random(me->query("combat_exp")) > ob->query("combat_exp")/10 &&
        me->query_skill("liaoyuan-spear", 1) >= 180 && 
        me->query("neili") > 600 &&
        !me->query_temp("slbw_hit") &&
        !ob->query("env/invisibility"))
        {
                me->set_temp("slbw", 1);
              i = me->query("jiali");
                neili = me->query("neili");
  me->set("jiali", me->query_skill("force") + 100);
        me->add_temp("apply/attack", me->query_skill("liaoyuan-spear", 1));
                me->add_temp("apply/strength", i/2);
            
                COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);
                
                if(me->query("neili") < neili) me->set("neili", neili-100);
                me->set("jiali", i);
                me->add_temp("apply/attack", -me->query_skill("liaoyuan-spear", 1));
                me->add_temp("apply/strength", -i/2);
        }else{       
           msg = parry_msg[random(sizeof(parry_msg))];
             if(neili >= random(neili1)+damage){
              msg += "結果基本上卸掉了$n的力道。\n";              
              j = -(damage+skill);
              }
           else{
              j = damage/2+random(damage/2); 
              if(j<damage/2) msg += "結果卸掉了一些$n的力道。\n";
              else msg += "結果卸掉了$n一半的力道。\n";
              j = -j;
              }
           }           
           message_vision(msg, me, ob);
           return j;
          
     
}

int practice_skill(object me)
{
         object weapon;
         if((int)me->query_skill("spear",1) <=120)
      		return notify_fail("你的基本槍法火候不足，難以領悟燎原槍法。\n");
        if (!me->query("sg/tzjj"))
             return notify_fail("你沒有得到上官幫主許可，怎麼能偷學燎原槍法。\n");
         if (!objectp(weapon = me->query_temp("weapon"))
                  || (string)weapon->query("skill_type") != "spear")
                return notify_fail("你使用的武器不對。\n");
         if ((int)me->query("jingli") < 70)
                return notify_fail("你的體力不夠練燎原槍法。\n");
         if ((int)me->query("neili") < 40)
                return notify_fail("你的內力不夠練燎原槍法。\n");
                
 me->receive_damage("jingli", 30);           
         if((int)me->query_skill("liaoyuan-spear",1)> 200)
 me->add("neili",-10);

         return 1;
}

int help(object me)
{
	write(HIC"\n燎原槍法："NOR"\n");
	write(@HELP
	燎原槍法為三國時五虎將之趙雲所創。此槍法乃趙雲集百家之常，另
	闢捷徑，常使人防不勝防！趙雲爭戰數十年後，遇見各路槍法高手，不斷總
	結，終於在晚年創出了此槍法，可以稱的上天下第一槍法！不過後來不知流
	路何處，竟被上官劍南晚年在被囚山洞中所得！
	
HELP
	);
	return 1;
}

