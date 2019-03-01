// 落石
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>
void show_result(object ob, string who, int p_skill, int p_id, int e_id);
string e_name, p_name;
void main(object ob, string who)
{
	int p_skill, p_id, e_id;
	int x,y,x2,y2;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if(!(p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["luoshi"]) )
	{	write("你不會落石之計。\n");
		return;}
	if( !p_id){
                write("只有身在軍中才能使用落石之計。\n");
                return;
        }	
	// In the furture, We have to consider theplayer's ablility
	// add the exp of this jimou, reduce mp, etc.
	if ( !e_id || TROOP_D->get_troop_area(e_id)!=where)
		{ write("對方不在此戰場上。\n");
			return;
		}
	if (TROOP_D->get_troop_side(e_id) ==TROOP_D->get_troop_side(p_id))
                {write ("不可向己方部隊施用此計。\n");
                        return;
                }	
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];
	if (MAP_D->get_map_cell(where,y2,x2,"m") != "∧")
		{
		write("對方不在山區，無法施計。\n");
		return;}
                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 4 ){
			write("你離敵人太遠無法施計。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"一陣奔雷般的響聲傳來，無數大石向部隊砸了下來。，原來是"+p_name+"
對你的部隊使用落石之計。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("luoshi"));
	ob->start_busy(10, "你正忙於施計呢。\n");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(),"luoshi");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "luoshi");
	call_out("show_result", 10+random(5), ob, who, p_skill, p_id, e_id);
}
void show_result(object ob, string who, int p_skill, int p_id, int e_id)
{	
	int kill,kill1,mora,mora1;
	int e_skill;
	int damage, p_num, e_num;
	float rate;
		
	if (!(CHAR_D->get_char(who,"skills")))
	e_skill=0;
	else {
	e_skill=CHAR_D->get_char(who,"skills")["luoshi"];}
if(!objectp(find_user(who)))
e_skill = CHAR_D->get_skill(who,"sk_zhimou");
	if(CHAR_D->get_skill(who,"chenzhuo"))
e_skill = e_skill + 1.5*CHAR_D->get_skill(who,"chenzhuo");

kill = p_skill;
kill1 = e_skill;
	kill = kill*2 - kill1 *1.2;
kill = random(kill);
	ob->stop_busy();
	if( kill>50)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "亂石砸下，士兵鬼哭狼嚎，死者無數。\n",
                        MSG_INDENT);
		mora = random (-20) -10;
		mora1 = random (6) +2;
		rate = 2;
		ob->simple_action(SG_SKILL_D->query_succ("luoshi"));
		} 
	else
	{     if(kill>20)
		{
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"亂石砸下，士兵多有損傷。\n",
                        MSG_INDENT);	
		mora = random (-10) - 5;
		mora1 = random (3) + 1;
		rate = 1.1;
		ob->simple_action(SG_SKILL_D->query_succ("luoshi"));
		}
	      else if( kill>5)
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"亂石砸下，士兵有些損傷。\n",
                        MSG_INDENT);
		mora = random(-5) - 1;
		mora1 = 1;
		rate = 0.4;
		ob->simple_action(SG_SKILL_D->query_succ("luoshi"));
		}	
	      else 
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"亂石砸下，但士兵們在指揮下小心翼翼的躲過了亂石。\n",
                        MSG_INDENT);
		mora = random(8) + 3;
		mora1 = random(-8) - 3;
		rate = 0;
		ob->simple_action(SG_SKILL_D->query_fail("luoshi"));
		}
	}
	p_num=TROOP_D->get_soldier_total_number(p_id);
	e_num=TROOP_D->get_soldier_total_number(e_id);
	TROOP_D->add_morale(p_id,mora1);
	TROOP_D->add_morale(e_id,mora);
	if (p_num > (e_num*5))
	{damage = rate * kill * 2* p_num / (e_num*2.5);}
	else 
	{if (p_num < e_num)
	damage = rate *kill * p_num * 4/e_num;
	else 
	damage = rate * kill * 2 * p_num / e_num *1.2; 
	}
	if(damage){
	 WARAI_D->kill_troop(e_id,damage);
                WARAI_D->clear_empty_troop(({e_id}));
         WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用落石之計，使"+
TROOP_D->find_troop(e_id)->query_id()[1]+"損失"+chinese_number(damage)+
"人”。","b"); 
	};	

return;
}
