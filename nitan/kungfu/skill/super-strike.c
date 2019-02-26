// super-strike 鐵掌掌法
// 2006-2-26
inherit SKILL;
#include <ansi.h>

string *parry_msg = ({
"$N雙掌一翻，將$n的來勢盡數化去，$n急勁就似鑽入了一片粘稠之物中間一般。\n",
"$N右肩斜閃，左手手指憑空劃了幾個圈子，以四兩微力，撥動$n千斤巨力。\n",
"$N眼見$n攻到，當即使出一招「天羅地網」，雙掌密不透風。\n",
"不料$N雙手一圈，一股雄渾無比的力道組成了一個旋渦，只帶得$n在原地急轉七八下。\n",
"$N連消帶打，雙手成圓形擊出，登時便套得$n跌跌撞撞，身不由主的立足不穩。\n",
"$N使出一招「穿雲手」，左手高，右手低，一股罡氣已將$n震開。\n",
"$N吸一口氣，體內真氣流轉，右掌揮出，一拒一迎，將$n的力道盡行碰了回去。\n",
"$N雙掌一翻，使出一招「穿雲手」，雙掌柔到了極處，空明若虛，將$n的急勁盡數化去。\n",
"就在這電光石火的一瞬之間，$N身子一弓，$n的勁力登時落空。\n",
});

string  *msgc = ({
"$N下半身右腳撇步上前，雙手化掌，向前雙抄上擊$n的$l",
"$N身體向前衝出，雙手先抱回腰際後，再向前以雙撐掌直推而出",
"$N全身原步右轉，右手向右刁出，左手順勢護肩，抓向$n的$l",
"$N一式[拍案齊掌」，全身微向下坐，產生後拉之勢，收左手，右手化掌向前直壓而出",
"$N向前一招「雙龍探爪」，雙手變掌為爪，先右後左，連續向$n的$l擊出",
"$N右手化掌，「採手衝捶」向前圈採而出，又順勢拉回右手，將左拳向$n擊出",
"$N右掌一拂而起，一招「推窗望月」，左掌自側面連消帶打，登時將$n的力道帶斜，右掌一揮，拍向$p$l",
"$N使一招「分水擒龍」，右臂突伸抓向$n，左掌陡然沿着伸長的右臂，飛快的一削而出，斬向$n的$l",
"$N突然使一式「白雲幻舞」，雙臂如旋風一般一陣狂舞，颳起一陣旋轉的氣浪，掌勢一推，壓向$n",
"$N一招「掌中乾坤」，一掌拍出以後，猛地側過身來，右臂自左肋下疾翻而出，拇，中兩指扣圈猛彈$n的$l",
"$N一招「落日趕月」，伸掌一拍一收，一拍無絲毫力道，一收之間，一股陰柔無比的力道才陡然發出",
"$N一招「天羅地網」，左掌大圈而出，右掌小圈而出，兩股奇異的力道一會之下，巨大的內勁壓向$n的$l",
"$N一招「五指幻山」，猛一吐氣，單掌有如推門，另一掌卻是迅疾無比的一推即收，雙勁合一，去勢如虎",
"$N大喝一聲，雙掌交錯，若有若無，飄渺間一招「金玉滿堂」，掌風急速拍向$n的$l",
"$N一招「斜步插花」微向右轉，成獨立步站定，同時右手化掌向$n探抓",
"$N左手由右掌上方直穿而出，這招「左穿雲手」直插$n的$l",
"$N右手由左掌上方直穿而出，一招「右穿雲手」插向$n的$l",
"$N成丁字步，「落步盤花」 左拳極力向上反穿而出，接著收回右掌，向下擊落",
"$N出一招「翻身平掌」，全身向左轉正，左手化刁手，右手以橫切掌向$n直切而出",
"$N一招「走馬活挾」，左右手同時以穿雲手向$n穿出，連環三式",
"$N一式「回馬橫擂」，左腿向前踢出雙飛腿，同時左手回勾，右手前穿拍向$n",
"$N左手圈封而回護住右肩，一招「翻天劈地」右手以鑽拳向$n穿打而出",
"$N右腿向前以小掃腿向前掃出，雙手握拳「泰山壓頂」直壓向$n的$l",
"$N出「回步雙切」，身體後仰，雙手同時向前雙抄而上，打向$n的$l",
"$N身體右傾，一招「反身插花」，左掌不動，右掌向右下方反切$n$l",
"$N一式「翻天雙風」，雙手以雙抄掌向前反切而出，於面前硬碰，發出聲音",
"$N左刁手不動，右掌收回胸前續勁，「順勢推山」以立掌向$n直推而出",
"$N收回雙手，以十字手封住胸前，「拗步聽風」接着雙掌向$n平撐而出",
"$N一式「走回馬槍」，雙手右甩，左手護肩，右手極力下甩又直挑而上"
});

string *super_msg = ({
"$N身行暴起，一式「蟄雷為動」，雙掌橫橫切出，掌緣才遞出，嗚嗚呼嘯之聲狂作，鐵掌之名，由此而出",
"$N突然大吼一聲，身行疾飛而起，雙掌翻飛，巨靈般的掌力猛向$n直撲而下，空氣中暴出“嗚”的一聲刺耳尖嘯！",
"$N凝力雙掌，順勢朝前推去，竟然出現一隻巨大的手掌，直轟$n$l",
"$N雙掌順勢一擺，一道罡氣破空而出",
});
int valid_enable(string usage)
{
        return usage== "strike" || usage == "parry";
}

mapping query_action(object me, object weapon)
{
        int level;
        string msg;
        level = (int)me->query_skill("super-strike",1);
        
        if(me->query_temp("tz/heyi")){
           	switch(me->query_temp("tz/heyi")){
            		case 2: msg = HIG"緊接着$N身體一轉，到了$n身旁，左掌順力拍出，這一招看似平和，實是內涵罡氣，威力無比！"NOR;break;
            		case 1: msg = CYN"$N突然腳下一晃，欺進$n，右掌一翻，運起鐵掌罡氣，單掌向$p頂門直拍而下！"NOR; break;
           	}  
           	me->add_temp("tz/heyi", -1);
           	return ([
                        "action":msg, 
                        "force" :level + me->query("jiali"),
                        "dodge": random(30)+random(30),
                        "damage": level/2,
                        "parry": 20+random(20),
                        "damage_type" : "內傷",
        	]);
        }
    	
    	if( level > 350
        && me->query_skill_prepared("strike") == "super-strike" 
        && me->query_skill_mapped("strike") == "super-strike"
	&& random(7)>4
)
    		return ([  
                	"action" : WHT +super_msg[random(sizeof(super_msg))]+NOR,
                	"force" :  level * 2,
                	"dodge":   level,
                	"parry":   level,
                	"weapon": "罡氣",
     "damage": level * 2,
        	"damage_type" :random(2)==1?"內傷":"震傷",
        	]);
        if (!weapon)
       	 	return ([
                	"action":CYN +msgc[random(sizeof(msgc))]+NOR,
                	"damage_type":"內傷",
       "damage": random(level/3),
         	"dodge":random(me->query_dex() * 2),
                	"force":me->query_skill("force") + me->query_str() * 2 + me->query("jiali") * 2,
 "parry": random(me->query_con() * 2),
"weapon" : "罡氣",
       	]);
}

int practice_skill(object me)
{
        if (!me->query("sg/tzjj"))
             return notify_fail("你沒有得到上官幫主許可，怎麼能偷學鐵掌掌法。\n");        
        if (!me->query_skill("force", 1))
                if((int)me->query_skill("force", 1) < 100)
                        return notify_fail("你的內功火候不夠，無法練鐵掌掌法。\n");
        if ((int)me->query("jingli") < 70)
                return notify_fail("你的體力太低了。\n");
        if ((int)me->query("neili") < 30)
                return notify_fail("你的內力不夠練鐵掌掌法。\n");                         
        me->receive_damage("jingli", 40);
        me->receive_damage("neili", 10+random(10));
        return 1;
}

int valid_learn(object me)
{
        if (me->query_temp("weapon") || me->query_temp("secondary_weapon"))
                return notify_fail("練鐵掌掌法必須空手。\n");
        if (!me->query("sg/tzjj"))
             return notify_fail("你沒有得到上官幫主許可，怎麼能偷學鐵掌掌法。\n");
        if ((int)me->query_skill("force", 1) < 20)
                return notify_fail("你的內功火候不夠，無法學鐵掌掌法。\n");
        if ((int)me->query("max_neili") < 3000)
                return notify_fail("你的內力太弱，無法練鐵掌掌法。\n");
        return 1;
}


int ob_hit(object ob, object me, int damage)
{
        string msg;
        int i, neili,p,j,skill, neili1;
        skill = me->query_skill("super-strike", 1);
        neili = me->query("neili");
        neili1 = ob->query("neili");

        if(!living(ob)) return damage;
        if(neili < 300) return damage; 
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
           message_vision(msg, me, ob);
           return j;
          
     
}
mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{                
        if(random(me->query_skill("super-strike", 1)) > 100 &&
            me->query_skill("poison", 1) > 60) {                
            victim->apply_condition("tz_poison", random(6) + 
                    (me->query_skill("poison", 1)/10) +
                    victim->query_condition("tz_poison"));
        }
}

string perform_action_file(string action)
{
        return __DIR__"super-strike/" + action;
}
