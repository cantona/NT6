// 收拾
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

void show_result(object ob, string who, int p_skill,int p_id,int e_id);

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
	if(!(p_skill=CHAR_D->get_char(ob->query_primary_id(),"skills")["shoushi"]))
        {       write("你不會收拾之計。\n");
                return;}
	if( !p_id){
                write("只有身在軍中才能收拾。\n");
                return;
        }	
	// In the furture, We have to consider theplayer's ablility
	// add the exp of this jimou, reduce mp, etc.
	if ( !e_id || TROOP_D->get_troop_area(e_id)!=where)
		{ write("對方不在此戰場上。\n");
			return;
		}
	if (!TROOP_D->get_troops(e_id,"conds"))
		{write("對方未混亂。\n");
			return;
		}
	else if(!TROOP_D->get_troops(e_id,"conds")["confuse"])
		 {write("對方未混亂。\n");
                        return;
                }
	if (TROOP_D->get_troop_side(e_id) !=TROOP_D->get_troop_side(p_id))
                {write ("不可向敵方部隊施用此計。\n");
                        return;
                }
	x =TROOP_D->get_troop_position(p_id)[0];
	y = TROOP_D->get_troop_position(p_id)[1];

	x2 = TROOP_D->get_troop_position(e_id)[0];
                y2 = TROOP_D->get_troop_position(e_id)[1];

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 ){
			write("你離對方太遠無法施計。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"士兵歡聲雷動，原來是"+p_name+"對你的部隊使用收拾之計。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("shoushi"));
	ob->start_busy(10, "你正忙於收拾呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(),"shoushi");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "shoushi");	
	call_out("show_result", 5+random(5), ob, who, p_skill, p_id, e_id);
}
void show_result(object ob, string who, int p_skill, int p_id, int e_id)
{	
	int kill,kill1,mora,mora1;
        int e_skill;
        int rate, damage, p_num, e_num;

        e_skill=TROOP_D->get_troops(e_id,"conds")["confuse"]["duration"];
	e_skill= e_skill;
	p_skill = p_skill * 3;
        kill =random(p_skill);
        kill1 =random(e_skill);
        kill = kill*2 - kill1 *1.8;
        ob->stop_busy();	
	if(kill>20)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "士兵歡聲雷動，混亂解除。\n",
                        MSG_INDENT);
		mora = random (10) +10;
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策完全成功，混亂解除。\n",
                        MSG_INDENT);
		ob->simple_action(SG_SKILL_D->query_succ("shoushi"));
		map_delete(TROOP_D->get_troops(e_id, "conds"),"confuse");	
WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用收拾之計，令"+
TROOP_D->find_troop(e_id)->query_id()[1]+"解除混亂狀態。","b");
	} 
	else
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),     
        	"收拾失敗。\n",
                        MSG_INDENT);
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
		"收拾失敗。\n",
                        MSG_INDENT);
		mora = random(-8) - 3;
		mora1 = random(-8) - 3;
ob->simple_action(SG_SKILL_D->query_fail("shoushi"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策失敗，我軍蒙受損失。\n",
                        MSG_INDENT);
	  	damage= 10 + random (50);
        	WARAI_D->kill_troop(p_id,damage);
		WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
TROOP_D->find_troop(p_id)->query_id()[1]+"使用收拾之計失敗，被敵人乘機殲
滅"+chinese_number(damage)+"人。","b");
		WARAI_D->clear_empty_troop(({p_id}));
		
		}
	TROOP_D->add_morale(p_id,mora1);
	TROOP_D->add_morale(e_id,mora);
	return;
}
