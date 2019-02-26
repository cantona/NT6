//慈航鞭,
//取自普明禪師<牧牛圖頌>
//cool@SJ,990420

#include <ansi.h>

inherit SKILL;

string *body_name = ({ 
"左手腕","左胳膊","脖子","頭部","腰部","左腿","小腿","左腳腳腕","右手腕","右胳膊","右腿","右腳腳腕",}); 

mapping *action = ({
([ "action": "$N雙手合什，內力灌注, 一式「未牧」，腰間$w似有靈性，筆直的刺向$n的$l",
   "skill_name" : "未牧",
   "damage_type":  "刺傷",
]),
([ "action": "$N沉肩滑步，手中$w一抖，一式「初調」，迅捷無比地分打左右兩側，$n頓時左右支絀，慌了手腳",
   "skill_name" : "初調",
   "damage_type":  "拉傷"
]),
([ "action": "$N將內力注入$w，驀地使出一式「受制」，$w矯夭飛舞，直如神龍破空一般抽向$n",
   "skill_name" : "受制",
   "damage_type":  "拉傷"
]),

([ "action": "$N一聲清嘯，手中$w一招「回首」，劃出漫天鞭影鋪天蓋地地向$n捲來，勢道猛烈之極",
   "skill_name" : "回首",
   "damage_type":  "拉傷"
]),
([ "action": "$N急速旋繞手中$w，一式「馴服」，揮出無數旋轉氣流向$n逼去 ",
   "skill_name" : "馴服",
   "damage_type":  "拉傷"
]),
([ "action": "$N身體凌空飛起，右手大力揮出$w，一式「無礙」，一股排山倒海的鞭風直擊向$n",
   "skill_name" : "無礙",
   "damage_type":  "拉傷"
]),
([ "action": "$N面露微笑跨前一步，右手$w輕揚，使出一式「任運」，鞭勢平和中正，不帶絲毫霸氣",
   "skill_name" : "任運",
   "damage_type":  "拉傷"
]),
([ "action": "$N向前急進，雙手握住$w，緩緩使出一式「相望」，鞭勢沉穩, 一股勁風破空而起",
   "skill_name" : "相望",
   "damage_type":  "拉傷"
]),
([ "action": "$N狂舞手中$w，一式「獨照」，鞭若蛟龍, 盤旋飛舞",
    "skill_name" : "獨照",
   "damage_type":  "拉傷"
]),
([ "action": "$N身體螺旋飛舞，手中$w突然揮出，使出一式「雙泯」，鞭勢猶如雨中閃電,氣勢驚人",
   "skill_name" : "雙泯",
   "damage_type":  "拉傷"
]),
});

int valid_enable(string usage) { return (usage == "whip") || (usage == "parry"); }

int valid_learn(object me)
{
       object weapon;

       if( query("max_neili", me)<800 )
               return notify_fail("你的內力不足，沒有辦法練習鞭法, 多練些內力再來吧。\n");


       if( !objectp(weapon=query_temp("weapon", me) )
         || query("skill_type", weapon) != "whip" )
               return notify_fail("你必須先找一條鞭子才能練鞭法。\n");
       return 1;

}

string query_skill_name(int level)
{
        int i;
        for(i = sizeof(action)-1; i >= 0; i--)
                return action[i]["skill_name"];
}

mapping query_action(object me, object weapon)
{
        int i, level,a,b,c,d,e,f,j;
        string msg;
        level   = (int) me->query_skill("shenfeng-bian",1);

        a=query("neili", me);
// 注意，取後天屬性時要注意某些心法可以增加臨時屬性。   
        b = me->query_str();
        c = me->query_dex();
        d = me->query_con();
        e = me->query_skill("whip", 1);
        f = me->query_skill("hunyuan-yiqi",1);

        if( query("neili", me)>query("max_neili", me) )
        a=query("max_neili", me)+(query("neili", me)-query("max_neili", me))/10;
        a = random(a/2)+a/3;   
        if ( a > 3000) a = 3000;        
        if ( a < 800) a = 800;
        j = (random(e + f)/4 + 1) * (random(b/10)+1)+10;
        if ( j > 200 ) j = 200;

        weapon=query_temp("weapon", me);
        if( query_temp("chb", me)){
          switch(query_temp("chb", me)){
             case 3: msg = MAG"但見$N身形朝前一衝， 手中"+ weapon->name()+MAG"抽向$n的小腹" NOR; break;
             case 2: msg =HIY"緊跟着$N把內力運在"+ weapon->name()+ "，"+ weapon->name()+HIY"如判官筆般點向$n的前心" NOR;break;
             case 1: msg = HIW"最後$N向上高高一躍，發了瘋般揮舞"+ weapon->name()+HIW "向着$n發起攻擊" NOR; break;
             default: msg = HIW"最後$N向上高高一躍，發了瘋般揮舞"+ weapon->name()+HIW"向着$n發起攻擊" NOR; break;
          }
          addn_temp("chb", -1, me);
              return ([
                "action":msg,
                "damage":random(e + f/2)/ 2 * random(b/10)+10, 
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
                "dodge": random(c)+random(me->query_skill("dodge", 1)/10)-random(40),
                "force": random(a/20) + (level),
                "parry": d-random(40)+random(me->query_skill("parry", 1)/5),
                "skill_name" : action[NewRandom(i, 20, level/5)]["skill_name"],
              ]);
        }
        for(i = sizeof(action); i > 0; i--) {
              return ([
                "action":action[NewRandom(i, 20, level/5)]["action"],
                "damage": j, 
                "damage_type": action[NewRandom(i, 20, level/5)]["damage_type"],
                "dodge": random(c)+random(me->query_skill("dodge", 1)/10)-random(40),
                "force": random(a/20) + (level),
                "parry": d-random(40)+random(me->query_skill("parry", 1)/5),
                "skill_name" : action[NewRandom(i, 20, level/5)]["skill_name"],
              ]);
        }
}

int practice_skill(object me)
{
       object weapon;

       if( !objectp(weapon=query_temp("weapon", me) )
        || query("skill_type", weapon) != "whip" )
           return notify_fail("你使用的武器不對。\n");
      if ((int)me->query_skill("hunyuan-yiqi",1) < 100)
               return notify_fail("你混天一氣不夠,無法修練神風鞭。\n");

       if( query("jingli", me)<50 )
               return notify_fail("你的體力不夠練神風鞭法。\n");

       if( query("neili", me)<50 )
               return notify_fail("你的內力不夠練神風鞭法。\n");

         addn("jingli", -35, me);
       addn("neili", -10, me);
       return 1;
}

mixed hit_ob(object me, object victim, int damage_bonus, int factor)
{
        object weap,weap1;
        string name;
        int i;
        name = body_name[random(sizeof(body_name))];
        i = me->query_skill("whip")/60+1;
        weap=query_temp("weapon", victim);
        weap1=query_temp("weapon", me);
        if( random(me->query_skill("shenfeng-bian", 1)) > 60

           && (query("neili", me)>100)){
           if( query_temp("weapon", victim)){
             if (random(5) > 2){
               message_vision(HIY "只見$N急速揮舞" + weap1->name() + HIY"，轉出無數個大小圈子，以陰柔之勁纏住對方的" + weap->name() +"！\n" NOR, me );      
               victim->start_busy(1);
               if (random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/3 ){       
                 message_vision(HIY "$N氣運手臂用力一拽，" + weap->name()
                                + HIY"卻無法從"+weap1->name()+HIY"的纏繞中脱開，情急之下只好放棄了手中的兵刃。\n" NOR, victim );
                 weap->move(environment(me));
                 victim->reset_action();
               }
               else {
                 message_vision(HIY "$N暗運巧勁，" + weap->name()
                                + HIY"順着方向快速旋轉數下，解開了"+weap1->name()+HIY"的纏繞。\n" NOR, victim );
                 addn("neili", -50, victim);
               }
               addn("neili", -30, me);
             }
           }
           else {
             if ((random(me->query_skill("parry", 1)) > victim->query_skill("parry", 1)/3 )
              && (!random(4))) {
               victim->start_busy(random(i)+ 1);
               addn("neili", -80, me);
               victim->receive_damage("qi", me->query_skill("kurong-changong",1)/2+damage_bonus/2);
//             victim->receive_wound("qi", me->query_skill("kurong-changong",1)/4+damage_bonus/4);       
//             if (!victim->query_condition("no_perform"))
//               victim->apply_condition("no_perform",i*random(2+random(2)));
               message_vision(HIY "只見$N的鞭式靈動異常," + weap1->name() + HIY"轉出無數個大小圈子，以陰柔之勁纏住了對方的" + name +"！\n" NOR, me);
               message_vision(HIR "$N身形一緩,似乎受了點傷。\n" NOR, victim );    
             }
           }             
           return 1;
        }
}

string perform_action_file(string action)
{
               return __DIR__"shenfeng-bian/" + action;

}
