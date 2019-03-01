
// shexing-diaoshou.c 蛇形刁手
#include <ansi.h>

inherit SKILL;  
string *order = ({""HIY"", ""HIG"", ""RED"", ""MAG"", ""YEL"", ""HIC"", ""HIW"", ""HIR"",""HIB"", ""CYN"",""WHT"",""HIM"",""BLU""});

mapping *action = ({
([	"action" : "$N一式"+(order[random(13)])+"「靈蛇出洞」"NOR"，右手虛晃，左手揚起，突然拍向$n的背後二穴",
	"force" : 390,
        "dodge" : 50,
"damage": 340,
	"lvl" : 0,
	"skill_name" : "靈蛇出洞",
	"damage_type" : "瘀傷"
]),
([	"action" : "$N側身一晃，一式"+(order[random(13)])+"「虎頭蛇尾」"NOR"，左手拿向$n的肩頭，右拳打向$n的胸口",
	"force" : 320,
        "dodge" : 50,
"damage": 340,
	"lvl" : 10,
	"skill_name" : "虎頭蛇尾",
        "damage_type" : "瘀傷"
]),
([	"action" : "$N一式"+(order[random(13)])+"「畫蛇添足」"NOR"，右手環攏成爪，一出手就向扣$n的嚥喉要害",
	"force" : 230,
        "dodge" : 20,
	"damage": 385,
	"lvl" : 20,
	"skill_name" : "畫蛇添足",
        "damage_type" : "瘀傷"
]),
([	"action" : "$N左手虛招，右掌直立，一式"+(order[random(13)])+"「杯弓蛇影」"NOR"，錯步飄出，疾拍$n的面門",
	"force" : 260,
        "dodge" : 20,
	"damage": 280,
	"lvl" : 30,
	"skill_name" : "杯弓蛇影",
        "damage_type" : "瘀傷"
]),
([	"action" : "$N使一式"+(order[random(13)])+"「蛇行鼠竄」"NOR"，左拳上格，右手探底突出，抓向$n的襠部",
	"force" : 300,
        "dodge" : 30,
	"damage": 295,
	"lvl" : 38,
	"skill_name" : "蛇行鼠竄",
        "damage_type" : "瘀傷"
]),
([	"action" : "$N一式"+(order[random(13)])+"「蛇磐青竹」"NOR"，十指伸縮，虛虛實實地襲向$n的全身要穴",
	"force" : 310,
        "dodge" : 40,
	"damage": 225,
	"lvl" : 51,
	"skill_name" : "蛇磐青竹",
        "damage_type" : "內傷"
]),
([	"action" : "$N雙手抱拳，一式"+(order[random(13)])+"「萬蛇洶湧」"NOR"，掌影翻飛，同時向$n施出九九八十一招",
	"force" : 380,
        "dodge" : 40,
	"damage": 230,
	"lvl" : 56,
	"skill_name" : "萬蛇洶湧",
        "damage_type" : "內傷"
]),
([	"action" : "$N一式"+(order[random(13)])+"「白蛇吐信」"NOR"，拳招若隱若現，若有若無，急急地拍向$n的丹田",
	"force" : 460,
        "dodge" : 40,
	"damage": 340,
	"lvl" : 60,
	"skill_name" : "白蛇吐信",
        "damage_type" : "內傷"
]),
([      "action" : "$N左指揮出，一式"+(order[random(13)])+"「青蛇挺身」"NOR"，削向$n的掌緣",
        "force" : 80,
        "damage" : 280,
        "dodge" : 25,
        "lvl" : 0,
        "skill_name" : "青蛇挺身",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N全身之力聚于一指，一式"+(order[random(13)])+"「銀蛇吐信」"NOR"，指向$n的胸前",
        "force" : 100,
        "damage" : 280,
        "dodge" : 25,
        "lvl" : 15,
        "damage" : 25,
        "skill_name" : "銀蛇吐信",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N左掌貼于神道穴，右手一式"+(order[random(13)])+"「金蛇擺尾」"NOR"，向$n的$l劃過",
        "force" : 120,
        "damage" : 280,
        "dodge" : 28,
        "lvl" : 25,
        "damage" : 55,
        "skill_name" : "金蛇擺尾",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙目怒視，一式"+(order[random(13)])+"「蝮蛇捕食」"NOR"，雙指拂向$n的額、頸、肩、臂、胸、背",
        "force" : 150,
        "dodge" : 5,
        "damage" : 280,
        "damage": 265,
        "lvl" : 45,
        "skill_name" : "蝮蛇捕食",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N一式"+(order[random(13)])+"「待機而行」"NOR"，左掌掌心向外，右指蓄勢點向$n的$l",
        "force" : 180,
        "dodge" : 15,
        "damage" : 280,
        "damage": 280,
        "lvl" : 60,
        "skill_name" : "待機而行",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N右手伸出，十指叉開，一式"+(order[random(13)])+"「猛蛇出洞」"NOR"，小指拂向$n的太淵穴",
        "force" : 200,
        "dodge" : 20,
        "damage": 2100,
        "lvl" : 70,
        "skill_name" : "猛蛇出洞",
        "damage_type" : "瘀傷"
]),
([      "action" : "$N雙迸出無數道勁氣，一式"+(order[random(13)])+"「千蛇纏身」"NOR"射向$n的全身",
        "force" : 220,
        "dodge" : 25,
        "damage": 220,
        "lvl" : 80,
        "skill_name" : "千蛇纏身",
        "damage_type" : "瘀傷"
]),

});

int valid_enable(string usage) { return usage=="hand" || usage=="parry"|| usage=="unarmed"; }

int valid_learn(object me)
{
	if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
		return notify_fail("練蛇形刁手必須空手。\n");
	if ((int)me->query_skill("hamagong", 1) < 20)
		return notify_fail("你的蛤蟆功不夠 \n");
	if ((int)me->query("max_neili") < 100)
		return notify_fail("你的內力太弱，無法練蛇形刁手。\n");
	return 1;
}
int valid_combine(string combo) { return combo=="lingshe-quan" || combo == "shentuo-zhang"; }
string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                if(level >= action[i]["lvl"])
                        return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level,ob_lvl,attack;
		object ob;
		
		ob = me->select_opponent();
		level = (int)me->query_skill("shexing-diaoshou", 1)+1;
		
		attack=level/100;
		
if (!ob) {
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
if (!me) {
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}



		if(level>200
			&&random(level)>level/3
			&&(random(me->query_dex())>20)
			&&living(ob)
//			&&me!= ob
			&&me->query("neili")>800
                        && !me->is_busy() 
                        && !me->query_temp("noauto")
		&& !me->query_temp("dsauto"))
		{
				if(attack>4) attack=4;
				attack=random(attack);
				if(attack<=1) attack=1;
				if(attack>4) attack=4;
message_vision(HIY "緊接著，$N口中發出“嘶嘶”的聲音，雙手半曲，三指上豎成蛇狀，陪合著瀟遙步法，有如急風暴雨般攻出了"+
			   chinese_number(attack+1)+"招。\n" NOR, me);
					for(i=0;i<attack;i++)
					{
						me->add("neili", -(50+random(50)));
						
						if(!ob)
						{
						break;
						}
//						if(me=ob)
//						{
//						break;
//						}


						if(!me)
						{
						break;
						}

						if(!living(ob))
						{
						break;
						}
						if(ob && me)
						{
						me->set_temp("dsauto",1);
						COMBAT_D->do_attack(me, ob, me->query_temp("weapon"), 1);  
						me->delete_temp("dsauto");
                                                }
					}
		}
else		if(level>200
			&&random(level)>level*2/5
			&&(random(me->query_dex())>25)
			&&living(ob)
			&&me->query("neili")>500
			&&random(5)>2
&& !me->query_temp("noauto")
			)
	{
			message_vision(YEL "$N揉身而上，自左向右輕輕回旋一周，$n被$N的身行所迷惑，頓時放棄攻擊，改為自守。\n" NOR, me,ob);

if (ob && me &&
ob!=me)
{
  if( !ob->is_busy() )
{
			ob->start_busy(3);
}
			me->add("neili", -20);
}
		}

		



        
        for(i = sizeof(action); i > 0; i--)
                if(level > action[i-1]["lvl"])
                        return action[NewRandom(i, 20, level/5)];
}
int practice_skill(object me)
{
	if ((int)me->query("qi") < 30)
		return notify_fail("你的體力太低了。\n");
	if ((int)me->query("neili") < 20)
		return notify_fail("你的內力不夠練蛇形刁手。\n");
	me->receive_damage("qi", 25);
	me->add("neili", -5);
	return 1;
}

string perform_action_file(string action)
{
    return __DIR__"shexing-diaoshou/" + action;
}



mixed hit_ob(object me, object victim, int damage_bonus)
{
        int lvl;
        int flvl;
	int level, jiali, time,level2,damage,damage2;
	object weapon;
object target;
target=victim;
        level = (int) me->query_skill("hamagong",1);
        level2= (int) me->query_skill("hamagong",1);

damage2= (int) victim->query("neili",1)/8;
if (damage2>= 3800) damage2 = 3800;
	
if (random(8)==0 && level>=300 && me->query_skill_mapped("force") == "hamagong")
{
	target->apply_condition("snake_poison",5);
	target->apply_condition("chanchu_poison",5);
	target->apply_condition("qx_snake_poison",3);
if (!target->is_busy()) target->start_busy(2);
	
 return HIR "$N倒轉經脈，身形一變，一口毒氣對著$n吐出!$n頭一昏，不知所措 ！\n";
}
	if( damage_bonus < 100 ) return 0;



if (me->query_temp("hmg_dzjm") && random(4)>2 )
{
        victim->receive_damage("qi", damage_bonus/2);
        victim->receive_wound("qi", damage_bonus/2);
 return HIR "$N倒轉經脈對著$n張口一咬!$n傷口一涼，鮮血噴出！\n";
}
	if( damage_bonus/2 > victim->query_str() || random(8)==0 ) {
if(me->query_skill("hamagong", 1)>100)
{
if (me->query_skill_mapped("force") == "hamagong"
&& !me->query_temp("weapon"))
{
		victim->receive_wound("qi", (damage_bonus ) / 2 );
		return HIM " "+ victim->name()+"喘息未定，又覺一股勁風撲面而來,吐出了一大口鮮血！\n" NOR;
}
}
	}
}

