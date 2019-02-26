// 牽制,效果：令對方士氣降低
#include <mudlib.h>
#include <daemons.h>
#include <ansi.h>

// #define _DEBUG_ID   "xiaobai"

void show_result(object ob, string who, int p_id, int e_id);
string e_name, p_name;

void main(object ob, string who)
{
	int p_id, e_id;
	int x,y,x2,y2;
	object env;
	string where;
	
	env = environment( ob );
	p_id=TROOP_D->get_char_troop(this_body()->query_primary_id());
	e_id=TROOP_D->get_char_troop(who);
	e_name=CHAR_D->get_char(who,"name");
	p_name=CHAR_D->get_char(ob->query_primary_id(),"name");
	where = TROOP_D->get_troop_area(p_id);
	if( !p_id){
                write("只有身在軍中才能牽制敵方士氣。\n");
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

                if( (x-x2)*(x-x2)+(y-y2)*(y-y2) > 9 ){
			write("你離敵人太遠無法施計。\n");
			return;}
                tell(deep_inventory(TROOP_D->find_troop(e_id)),
	"士兵一陣喧譁，原來是"+p_name+"對你的部隊使用牽制之計。\n",
                        MSG_INDENT);
                // In future, we have to consider effects of the
                // ablility of general, zhenxing, dixing, etc.
                // Now the damage depends only on the No of bowman
	ob->simple_action(SG_SKILL_D->query_use("jiaoma"));
	ob->start_busy(10, "你正忙於牽制敵方士氣呢。");
	load_object("/daemons/cast_d.c")->reg_player(ob->query_primary_id(),"jiaoma");
        ob->award_exp(ob->query_sk_level("sk_zhimou")/2+random(20), "jiaoma");
	call_out("show_result", 5+random(5), ob, who, p_id, e_id);
}
void show_result(object ob, string who, int p_id, int e_id)
{	
	int mora,mora1;

// edc  08/05/2001
// change jiaoma logic, disconnect the relation between reputation and cast result
	int myJiaoma, itJiaoma=0, oldMorale;
	mixed sol;
	string *ss;
	string strMyId = ob->query_primary_id();

	myJiaoma = CHAR_D->get_char( strMyId, "skills" )["jiaoma"];
	if ( CHAR_D->get_char(who, "status") == "NPC" )
		itJiaoma = random(CHAR_D->get_char(who, "sk_wuli"));
	else
		itJiaoma = CHAR_D->get_skill(who,"jiaoma");
		
	mora = ( myJiaoma - itJiaoma / 4 ) / 4 + random(10) - 5;  // range: -12 -- 30

	// 敵軍士氣已經很低的時候, 效果降低, 死豬不怕開水燙的意思
	if ( mora > 0)
	{
		sol=TROOP_D->get_troops(e_id, "soldier");
		if(!sizeof(sol)) return;
		ss=keys(sol);
		foreach(string s in ss)
		{
			oldMorale = TROOP_D->get_soldier(e_id, s, "morale");
		}

        if ( oldMorale < 120)
            mora /= 3;
        else if ( oldMorale < 60 )
            mora /= 5;

	}
//EDCBUG(sprintf("MORALE DROP : %d \n", mora));
//EDCBUG(sprintf("the troop: %O \n", sol));
    SGSYS( sprintf("%s對%s使用 jiaoma , 效果：從%d減少了%d\n", strMyId, who, oldMorale, mora ) );
#ifdef _DEBUG_ID
    TELL_BUG( _DEBUG_ID, sprintf("%s對%s使用 jiaoma , 效果：從%d減少了%d\n", strMyId, who, oldMorale, mora ) );
#endif  // _DEBUG_ID

	if( mora > 24 )
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                	"士兵一片混亂，士氣狂跌。\n",
                        MSG_INDENT);
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"計策完全成功，敵人士氣猛降。\n",
                        MSG_INDENT);
	} 
	else if( mora > 10 )
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵一片頹唐，士氣大降。\n",
                        MSG_INDENT);	
		mora1 = random (3) + 1;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"計策大成功，敵方士氣大降。\n",
                        MSG_INDENT);	
	}
	else if( mora > 0)
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵面露茫然之色，士氣降低。\n",
                        MSG_INDENT);
		mora1 = 1;
		ob->simple_action(SG_SKILL_D->query_succ("jiaoma"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策成功，敵人士氣降低。\n",
                        MSG_INDENT);
	}	
	else 
	{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        		"士兵識破敵人計策，士氣上升。\n",
                        MSG_INDENT);
		ob->simple_action(SG_SKILL_D->query_fail("fenfa"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                	"計策失敗，敵人士氣上升，己方士氣下降。\n",
                        MSG_INDENT);

	}
/*
	int rep=0, rep1=0;

	rep =random(CHAR_D->get_char(ob->query_primary_id(),"reputation"));
	rep1 =random(CHAR_D->get_char(who,"reputation"));
	rep+=ob->query_sk_level("jiaoma")*500*(random(5)+5)/5;
	if(CHAR_D->get_char(who,"skills"))
	rep1+=CHAR_D->get_char(who,"skills")["jiaoma"]*500*(random(5)+5)/5;
	rep = rep*2 - rep1 *3;
	rep-= (25+random(25))*500*(random(5)+5)/5; 
	ob->stop_busy();
	if( rep>100000)
	{	tell(deep_inventory(TROOP_D->find_troop(e_id)),
                "士兵一片混亂，士氣狂跌。\n",
                        MSG_INDENT);
		mora = random (-20) -10 - rep/50000;
		mora1 = random (6) +2;
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策完全成功，敵人士氣猛降。\n",
                        MSG_INDENT);
	} 
	else
	{     if(rep>10000)
		{
	tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵一片頹唐，士氣大降。\n",
                        MSG_INDENT);	
		mora = random (-10) - 5- rep/10000;
		mora1 = random (3) + 1;
	tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策大成功，敵方士氣大降。\n",
                        MSG_INDENT);	
		}
	      else if( rep>1000)
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵面露茫然之色，士氣降低。\n",
                        MSG_INDENT);
		mora = random(-5) - 1;
		mora1 = 1;
		ob->simple_action(SG_SKILL_D->query_succ("jiaoma"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策成功，敵人士氣降低。\n",
                        MSG_INDENT);
		}	
	      else 
		{
		tell(deep_inventory(TROOP_D->find_troop(e_id)),
        	"士兵識破敵人計策，士氣上升。\n",
                        MSG_INDENT);
		mora = random(8) + 3;
mora1 = random(-10)-5;
		ob->simple_action(SG_SKILL_D->query_fail("fenfa"));
		tell(deep_inventory(TROOP_D->find_troop(p_id)),
                "計策失敗，敵人士氣上升，己方士氣下降。\n",
                        MSG_INDENT);
		}
	}
// edc 08/05/2001  set the maxium moral descresing value = -50	
	if (mora < -50) mora = -50;
////

*/
////
	WARAI_D->war_inf(TROOP_D->get_troops(p_id,"task_id"),
	TROOP_D->find_troop(p_id)->query_id()[1]+"使用叫罵之計。","b");
	TROOP_D->add_morale(p_id,mora1);
	if(p_id!=e_id){
		TROOP_D->add_morale(e_id,-mora);
	}
	return;
}
