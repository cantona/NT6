// Flagd.c 搶旗戰主控制程序

#include <ansi.h>
inherit F_DBASE; 

#define MIN_TIME          60
#define ROUND_TIME        7200
#define RESET_TIME        40
#define START_TIME        5
#define END_TIME          1500
//#define END_TIME          300
#define START_TIME_COUNT  3
#define END_TIME_COUNT    5
#define REWARD_POT        3500
#define REWARD_EXP        10000
#define REWARD_EXPRI      1000
#define BLUE_START        "/d/flagwar/blue_entry" 
#define RED_START         "/d/flagwar/red_entry"
#define BLUE_RESET        "/d/flagwar/blue_reset" 
#define RED_RESET         "/d/flagwar/red_reset"
#define FLAG_OB           "/d/flagwar/obj/flag"
#define CENTER_FLAG       "/d/flagwar/center_flag"
#define WEST_FLAG         "/d/flagwar/west_flag"
#define EAST_FLAG         "/d/flagwar/east_flag"


int clean_up() { return 1; }
nosave int startnow,can_accept, reward_money, rsc, bsc, rfin, bfin, start_time;
nosave object *all_player_ob;
nosave string *all_player;
nosave mapping red, blue;
nosave int check_event_id, round_event_id;
void leave_player(string id);
void init_player(object me);
void auto_check();
void give_bouns();
int add_score(object me, int reward);
int set_score(string id, string party, int reward);
void remove_flag_war();
void restore_player(object me);
void drop_flag(object me, object ob);
void end_flag_war();
void put_flag_in_room(string t);
int sort_user(object ob1, object ob2);

mapping party_str = (["blue":HIB"藍隊"NOR, "red":HIR"紅隊"NOR]);
int query_flagwar_time() {
	if(can_accept) return -1;
	if(!round_event_id || !SCHEDULE_D->query_event(round_event_id)) return -2;
	return (SCHEDULE_D->query_event(round_event_id)[3] - SCHEDULE_D->query_event(round_event_id)[2]);
}
int query_flagwar() {
	return startnow;
}
mixed query_flagwar_data(string t) {
	switch(t) {
		case "all_player":
			return all_player;
		break;
		case "all_player_ob":
			return all_player_ob;
		break;		
		case "red":
			return red;
		break;
		case "blue":
			return blue;
		break;
		case "bsc":
			return bsc;
		break;
		case "rsc":
			return rsc;
		break;
		case "can_accept":
			return can_accept;
		break;
		
    default:
    return 0;		
	}
}
void clear_all_data() {
	all_player = ({ });
	all_player_ob = ({ });
	red = ([ ]);
	blue = ([ ]);
	startnow = 0;
	can_accept = 0;
	reward_money = 0;
	bsc = 0;
	rsc = 0;
	bfin = 0;
	rfin = 0;
}
void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "搶旗戰精靈");
        CHANNEL_D->do_channel(this_object(), "sys", "搶旗戰已經啟動。");
        clear_all_data();
        round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
}
void remove()
{
	remove_flag_war();
}
void message_flag(string str) {
	 if(str)
	 message("channel:rumor", HIG "【搶旗情報】活動主持人："+str+"\n" NOR, users());
}
void message_flag_tell(string str) {
	 if(str)
	 message("vision", HIG "【搶旗戰場】戰場裁判官："+str+"\n" NOR, all_player_ob);
}
void add_flag_round() {
	string round;
	round = explode(read_file("/www/flag_round"), "\n")[0];
	if(!round) round = "1";
	round = count_add(round, 1);
	write_file("/www/flag_round", round, 1);
}
string query_flag_round() {
	string round;
	round = explode(read_file("/www/flag_round"), "\n")[0];
	if(!round) round = "1";
	return round;
}
void start_flag_war() {
	if(objectp(WAR_D->query_marshal())) {
		message_flag("第 "+query_flag_round()+" 場搶旗戰將延至 10 分鐘後重新開始。");
		round_event_id = SCHEDULE_D->set_event(600, 0, this_object(), "start_flag_war");
		return;
	}
  clear_all_data();
	message_flag("第 "+query_flag_round()+" 場搶旗戰將在 "+START_TIME+" 分鐘後開始，請使用 flag join 報名。");
	can_accept = 1;
	start_time = time();
	if(round_event_id) SCHEDULE_D->delete_event(round_event_id);
	SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count", START_TIME);
}
void start_flag_war_count(int num) {
	    object me, be, re;
	    string *temp_all_player = ({});
      if(num <= 1) {
      		// check player have click html?

      	if(sizeof(all_player) < 5) {
      		message_flag("由於人數過少本場搶旗戰取消。");
      		foreach(string id in all_player) {
      			if(!me = find_player(id)) continue;
      			me->add("balance", 500000);
      			tell_object(me, HIY"由於人數過少本場搶旗戰取消，退還報名費用。\n"NOR);
      		}
          clear_all_data();
          add_flag_round();
          round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
      	} else {
      		startnow = 1;
      		can_accept = 0;
          // 關閉起點出口
          if(be = load_object(BLUE_START)) be->delete("exits");
          if(re = load_object(RED_START)) re->delete("exits");

      		// 這裏開始分配隊伍      		
      		foreach(string id in all_player) {
 	        if(!me = find_player(id)) {
 	         leave_player(id);
 	         continue;	
 	        }
      		temp_all_player += ({ me });
      		}
      		temp_all_player = sort_array(temp_all_player, (: sort_user :));
      		foreach(object mes in temp_all_player) {
 	         if(!mes) {
 	         leave_player(mes->query("id"));
 	         continue;	
 	        }
 	         all_player_ob += ({ mes });
 	         if(sizeof(red) >= sizeof(blue)) {
 	         	blue[mes->query("id")] = 0;
 	          mes->set_temp("flag_war/party", "blue");
 	          mes->set_temp("title", HIB"搶旗藍隊"NOR);
 	         } else {
 	         	red[mes->query("id")] = 0;
 	         	mes->set_temp("flag_war/party", "red");
 	         	mes->set_temp("title", HIR"搶旗紅隊"NOR);
 	         }
 	         init_player(mes);
      		}
          message_flag("搶旗戰開始，本場紅隊有 "+sizeof(red)+" 人，藍隊有 "+sizeof(blue)+" 人，勝利獎金："+MONEY_D->money_str(reward_money)+"。");
          SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count_in", START_TIME_COUNT);
          SCHEDULE_D->set_event(END_TIME, 0, this_object(), "end_flag_war");
          check_event_id = SCHEDULE_D->set_event(1, 1, this_object(), "auto_check");
          temp_all_player = ({});
      	}
      } else {
      	num--;
      	message_flag("第 "+query_flag_round()+" 場搶旗戰將在 "+num+" 分鐘後開始，請使用 flag join 報名。");
      	SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count", num);
      }
}
void start_flag_war_count_in(int num) {
	object be, re;
	if(num <= 1) {
    if(be = load_object(BLUE_START)) be->open_exit();
    if(re = load_object(RED_START)) re->open_exit();
   	message_flag_tell("搶旗戰已經開放出口了，請快點出發吧。");
   	put_flag_in_room("center");
    SCHEDULE_D->set_event(5+random(10), 0, this_object(), "put_flag_in_room", "west");
    SCHEDULE_D->set_event(5+random(10), 0, this_object(), "put_flag_in_room", "east");
    
	} else {
   num--;
   message_flag_tell("搶旗戰將在 "+num+" 分鐘後開放出口，請做好準備。");
   SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "start_flag_war_count_in", num);		
	}
}
int add_player(object me, int money) {
	    if(!me || !money || startnow || !can_accept) return 0;
	    if(member_array(me->query("id"), all_player) != -1) return 0;
	    all_player += ({ me->query("id") });
	    reward_money += money;
	    message_flag(me->query_idname()+"報名參加搶旗戰。");
	    return 1;
}
void auto_check() {
	   string room;
	   if(!startnow || !sizeof(all_player_ob)) {
	   	if(check_event_id) SCHEDULE_D->delete_event(check_event_id);
	   	return;
	   }
     if(!sizeof(red) || !sizeof(blue)) {
     	end_flag_war();
	   	if(check_event_id) SCHEDULE_D->delete_event(check_event_id);     	
    }
	   foreach(object pl in all_player_ob) {
        if(!pl) continue;
        
        // 檢驗位置
        if(room = base_name(environment(pl))) {
        if (!sscanf(room, "/d/flagwar/%*s")) {
         leave_player(pl->query("id"));  	   	  	
        }
      }
	  }
}
void leave_player(string id) {
	    object me, room;
	    if(!id) return;
	    if(find_player(id)) if(member_array(find_player(id), all_player_ob) != -1) all_player_ob -= ({ find_player(id) });
	    if(member_array(id, all_player) != -1) all_player -= ({ id });
      if(member_array(id, keys(red)) != -1) map_delete(red, id);
      if(member_array(id, keys(blue)) != -1) map_delete(blue, id);
      if(me = find_player(id)) {
      if(startnow) {
      	message_flag(me->query_idname()+"在中途逃離搶旗戰了。");
      	restore_player(me);
      	if(!me->is_net_dead()) {
      	tell_object(me, "你一口氣逃出了戰場，來到揚州中央廣場。\n");   	
      	me->move("/d/city/guangchang");
      	message("vision", "只見" + me->name() + "慌里慌張的跑了過來。\n", environment(me), ({ me }));
        }
      } else {
      	me->add("balance", 490000);
      	reward_money -= 500000;
      	message_flag(me->query_idname()+"取消報名搶旗戰，退還報名費"+MONEY_D->money_str(490000)+"。");
      }
    }
}
void init_player(object me)
{
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "check_die" :));
        me->set_override("unconcious", (: call_other, __FILE__, "check_die" :));
        me->move("/d/flagwar/"+me->query_temp("flag_war/party")+"_entry");
        tell_object(me, HIY "活動主持人將你帶到了" + environment(me)->short() + HIY "。\n");
        message("vision", HIY"只見活動主持人將" + me->name() + "帶到了" + environment(me)->short() + HIY "。\n", environment(me), ({ me }));
}
int check_quit(object me)
{
        leave_player(me->query("id"));  
        return 1;
}
void send_rune(object me)
{
	string *runes = ({"/clone/enchase/skull1","/clone/enchase/skull2","/clone/enchase/rune01","/clone/enchase/rune02","/clone/enchase/rune03","/clone/enchase/rune04","/clone/enchase/rune05","/clone/gift/tianshi-charm"});
	string *gems = ({"/clone/enchase/CYNjewel", "/clone/enchase/BLKjewel", "/clone/enchase/GRNjewel", "/clone/enchase/MAGjewel", "/clone/enchase/REDjewel", "/clone/enchase/WHTjewel", "/clone/enchase/YELjewel",});
	object rune;
	if(!me) return;
	if(random(3) >= 2) return;
	rune = new(runes[random(sizeof(runes))]);
  rune->move(me);
  tell_object(me, HIG"你獲得了一個"+rune->name()+"。\n"NOR);
	rune = new(gems[random(sizeof(gems))]);
  rune->move(me);
  tell_object(me, HIG"你獲得了一個"+rune->name()+"。\n"NOR);  
  if(random(300) >= 295) {
	rune = new(runes[random(sizeof(runes))]);
  rune->move(me);
  tell_object(me, HIG"你獲得了一個"+rune->name()+"。\n"NOR);
  }
  if(random(300) >= 295) {
	rune = new(gems[random(sizeof(gems))]);
  rune->move(me);
  tell_object(me, HIG"你獲得了一個"+rune->name()+"。\n"NOR);
  }  
}
void random_item(object me)
{
	object item;
	string *items = ({"/d/flagwar/obj/item1","/d/flagwar/obj/item2","/d/flagwar/obj/item3","/d/flagwar/obj/item4","/d/flagwar/obj/item4","/d/flagwar/obj/item5","/d/flagwar/obj/item6"});
	item = new(items[random(sizeof(items))]);
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"獲得搶旗戰專用特殊物品"+item->name()+"。");
	item->move(me);
}
int check_die(object me)
{
	      mapping my;
	      object ob, flag;
	      my = me->query_entire_dbase();
	      if(objectp(flag = present("fwar flag", me)))
        if(flag->move(environment(me))) drop_flag(me, flag);
	      if(objectp(flag = present("fwar count seal", me))) {
        message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在臨死前引發"+flag->name());
        foreach(object ppl in all_inventory(environment(me))) {
         if(ppl == me) continue;
         ppl->start_busy(20);
        }
        destruct(flag);
        }
        
        if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
        me->delete_temp("flag_war/stab_now");
	      if(!objectp(ob = me->query_last_damage_from())) {
	      message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"莫名其妙被殺，"+party_str[me->query_temp("flag_war/party")]+HIG+"扣 3 分。");

        my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = my["max_qi"];
        my["jing"] = my["max_jing"];
	      if(me->query_temp("flag_war/party") == "red") {
	      	rsc -= 3;
	        red[me->query("id")] -= 3;
	        me->move(RED_RESET);
	      } else {
	      	bsc -= 3;
	        blue[me->query("id")] -= 3;
	        me->move(BLUE_RESET);
	      }
	      if(!living(me)) me->revive();
	      me->start_busy(20);
	      random_item(me);
	      if(random(6) >= 3) random_item(me);
	      if(random(6) >= 3) random_item(me);
	      return 1;
	      } else {
        message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"被"+ob->query_idname()+HIG+"無情的擊殺，"+party_str[me->query_temp("flag_war/party")]+HIG+"扣 3 分。");
	      my["eff_qi"] = my["max_qi"];
        my["eff_jing"] = my["max_jing"];
        my["qi"] = my["max_jing"];
        my["jing"] = my["max_jing"];
        ob->remove_killer(me);
        if(me->query_temp("flag_war/party") == "red") {
	      	rsc -= 3;
	      	red[me->query("id")] -= 3;
	        if(ob->query_temp("flag_war/party") == "blue") {
	        bsc += 3;
	        blue[ob->query("id")] += 3;
	        }
	        me->move(RED_RESET);
	      } else {
	      	bsc -= 3;
	      	blue[me->query("id")] -= 3;
	      	if(ob->query_temp("flag_war/party") == "red") {
	      	rsc += 3;
	        red[ob->query("id")] += 3;
	        }
	        me->move(BLUE_RESET);
	      }
	      if(!living(me)) me->revive();
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->start_busy(20);
        random_item(me);
        if(random(6) >= 3) random_item(me);
        if(random(6) >= 3) random_item(me);
        me->set_override("quit", (: call_other, __FILE__, "check_quit" :));
        me->set_override("die", (: call_other, __FILE__, "check_die" :));
        me->set_override("unconcious", (: call_other, __FILE__, "check_die" :));        
	      }
        return 1;
}
void get_flag(object me, object ob)
{
	mapping party_str = (["blue":HIB"藍隊"NOR, "red":HIR"紅隊"NOR]);
	if(!me || !ob) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"奪得了"+ob->name()+HIG+"。");
	me->set_temp("flag_war/move_busy", 1);
	me->set_temp("title", me->query_temp("title")+" "HIM"扛旗者"NOR);
}
void drop_flag(object me, object ob)
{
	
	if(!me || !ob) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"遺失了"+ob->name()+HIG+"。");
	me->delete_temp("flag_war/move_busy");
	if(me->query_temp("flag_war/party") == "blue") me->set_temp("title", HIB"搶旗藍隊"NOR);
	else me->set_temp("title", HIR"搶旗紅隊"NOR);
}

void end_flag_war()
{
	if(!sizeof(red)) message_flag_tell("由於"+party_str["red"]+HIG+"已經沒有人了，本場搶旗戰將在 "+END_TIME_COUNT+" 分鐘後提早結束。");
	else if(!sizeof(blue)) message_flag_tell("由於"+party_str["blue"]+HIG+"已經沒有人了，本場搶旗戰將在 "+END_TIME_COUNT+" 分鐘後提早結束。");
  message_flag_tell("本場搶旗戰將在 "+END_TIME_COUNT+" 分鐘後結束。");
  SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "end_flag_war_count", END_TIME_COUNT);		
}

void end_flag_war_count(int num) {
	object be, re;
	if(num <= 1) {
	 startnow = 0;
	 message_flag("本場搶旗戰結束，正在統計結果。");
	 give_bouns();
   //SCHEDULE_D->set_event(5, 0, this_object(), "give_bouns"); // 給獎勵
	} else {
   num--;
   message_flag_tell("本場搶旗戰將在 "+num+" 分鐘後結束。");
   SCHEDULE_D->set_event(MIN_TIME, 0, this_object(), "end_flag_war_count", num);		
	}
}

void give_bouns() {
	int exp, pot, expri, allsc, sc, m, allppl;
	int base_exp, base_pot, base_expri, flag_time;
	object ob;
	if(!all_player) return;

	// 獎勵
	allppl = sizeof(all_player);
	if(allppl > 50) allppl = 50;
	base_exp = REWARD_EXP*allppl;
	base_pot = REWARD_POT*allppl;
	base_expri = REWARD_EXPRI*allppl;
	flag_time = ACTION_D->query_action("flagwar_reward"); 
  if(flag_time) {
  	base_exp *= flag_time;	
  	base_pot *= flag_time;	
  	base_expri *= flag_time;
  }		
//	if(base_exp >= 400000) base_exp = 400000;
//	if(base_pot >= 250000) base_pot = 250000;
//	if(base_expri >= 100000) base_expri = 100000;
	// 總分
	allsc = bsc+rsc;
	if(allsc <= 0) allsc = 1;
	if(reward_money <= 0) reward_money = 0;
	else reward_money *= 0.9;
	message_flag("本場搶旗戰結果為紅隊 "+rsc+" 分，藍隊 "+bsc+" 分。");
	if(rsc == bsc) {
		message_flag("雙方戰況慘烈，不分軒輊，以平手收場，發放參加獎。");
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		
		foreach(object pl in all_player_ob) {
			if(!objectp(pl)) continue;
			if(!pl->query_temp("flag_war")) continue;
			pl->add("combat_exp", exp);
			pl->add("potential", pot);
			pl->add("experience", expri);
			pl->add("action_point", 5);	
		  tell_object(pl, HIC"透過參加搶旗戰你獲得了"+chinese_number(exp)+"點經驗，"+chinese_number(pot)+"點潛能和"+chinese_number(expri)+"點體會。\n"NOR);
		  restore_player(pl);
      	tell_object(pl, "你來到了揚州中央廣場。\n");
      	pl->move("/d/city/guangchang");
      	message("vision", "只見" + pl->name() + "跑了過來。\n", environment(pl), ({ pl }));		  
		}
	} else if(rsc > bsc) {
		message_flag("本場搶旗戰紅隊勝利，依積分發放獎勵。");
		foreach(string id in keys(red)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
			sc = red[id];
			if(sc <= 0) sc = 1;
			exp = base_exp*sc/rsc;
			pot = base_pot*sc/rsc;
			expri = base_expri*sc/rsc;
			m = reward_money*sc/rsc;
			ob->add("combat_exp", exp);
			ob->add("potential", pot);
			ob->add("experience", expri);
			ob->add("balance", m);
			ob->add("action_point", 15);
			send_rune(ob);
		  tell_object(ob, HIC"透過參加搶旗戰你獲得了"+chinese_number(exp)+"點經驗，"+chinese_number(pot)+"點潛能和"+chinese_number(expri)+"點體會及"+MONEY_D->money_str(m)+"。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你來到了揚州中央廣場。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只見" + ob->name() + "跑了過來。\n", environment(ob), ({ ob }));
		}
		foreach(string id in keys(blue)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		ob->add("combat_exp", exp);
  	ob->add("potential", pot);
		ob->add("experience", expri);
		ob->add("action_point", 10);
		send_rune(ob);
		  tell_object(ob, HIC"透過參加搶旗戰你獲得了"+chinese_number(exp)+"點經驗，"+chinese_number(pot)+"點潛能和"+chinese_number(expri)+"點體會。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你來到了揚州中央廣場。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只見" + ob->name() + "跑了過來。\n", environment(ob), ({ ob }));			
		}		
	} else {
		message_flag("本場搶旗戰藍隊勝利，依積分發放獎勵。");
		foreach(string id in keys(blue)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
			sc = blue[id];
			if(sc <= 0) sc = 1;
			exp = base_exp*sc/bsc;
			pot = base_pot*sc/bsc;
			expri = base_expri*sc/bsc;
			m = reward_money*sc/bsc;
			ob->add("combat_exp", exp);
			ob->add("potential", pot);
			ob->add("experience", expri);
			ob->add("balance", m);
			ob->add("action_point", 15);
			send_rune(ob);
		  tell_object(ob, HIC"透過參加搶旗戰你獲得了"+chinese_number(exp)+"點經驗，"+chinese_number(pot)+"點潛能和"+chinese_number(expri)+"點體會及"+MONEY_D->money_str(m)+"。\n"NOR);
		  restore_player(ob);
      	tell_object(ob, "你來到了揚州中央廣場。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只見" + ob->name() + "跑了過來。\n", environment(ob), ({ ob }));		  
		}
		foreach(string id in keys(red)) {
			if(!objectp(ob = find_player(id))) continue;
			if(!ob->query_temp("flag_war")) continue;
		exp = REWARD_EXP / 4;
		pot = REWARD_POT / 4;
		expri = REWARD_EXPRI / 4;
		ob->add("combat_exp", exp);
  	ob->add("potential", pot);
		ob->add("experience", expri);
		ob->add("action_point", 10);
		send_rune(ob);
		  tell_object(ob, HIC"透過參加搶旗戰你獲得了"+chinese_number(exp)+"點經驗，"+chinese_number(pot)+"點潛能和"+chinese_number(expri)+"點體會。\n"NOR);				
		  restore_player(ob);
      	tell_object(ob, "你來到了揚州中央廣場。\n");
      	ob->move("/d/city/guangchang");
      	message("vision", "只見" + ob->name() + "跑了過來。\n", environment(ob), ({ ob }));			
		}			
	}
	add_flag_round();
	remove_flag_war();
  clear_all_data();
}
void restore_player(object me) {
	      
	      if(!me) return;
        foreach(object inv in all_inventory(me)) 
       	if(inv->query("flag_war_item")) destruct(inv);   	
                   
        if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
      	me->delete_temp("flag_war");
      	me->delete_temp("title");
        me->delete_override("quit");
        me->delete_override("die");
        me->delete_override("unconcious");
        me->remove_all_enemy(1);
        me->remove_all_killer();
        me->receive_damage("qi", 0);
        me->set("eff_qi", me->query("max_qi"));
        me->set("eff_jing", me->query("max_jing"));
        me->set("qi", me->query("max_qi"));
        me->set("jing", me->query("max_jing"));     	
	      if(!living(me)) me->revive();
}
void remove_flag_war() {
	      object ro;
	      if(check_event_id) SCHEDULE_D->delete_event(check_event_id);
	      if(round_event_id) SCHEDULE_D->delete_event(round_event_id);
        foreach(string f in get_dir("/d/flagwar/")) {
        	if(objectp(ro = find_object("/d/flagwar/"+f))) destruct(ro);
        }
	      round_event_id = SCHEDULE_D->set_event(ROUND_TIME, 0, this_object(), "start_flag_war");
}
void stab_flag(object me, object ob) {
	int stab_event_id;
	if(!me || !ob || !startnow) return;
	if(me->query_temp("flag_war/stab_now")) return;
	message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在"+environment(me)->short()+HIG+"準備將"+ob->name()+HIG+"插上旗台。");
	if(!me->query_temp("flag_war/move_busy")) stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", 1, me, ob);
	else stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", 5+random(5), me, ob);
	
	message_vision("$N準備將$n插上旗台。\n" , me, ob);
	me->set_temp("flag_war/stab_now", 1);
	me->set_temp("flag_war/stab_event_id", stab_event_id);
	me->start_busy(5);
}
void stab_flag_count(int num, object me, object ob) {
  int reward, pa, stab_event_id;
  string *msgs = ({"$N努力的將$n插上旗台，卻不知怎麼的插不進去。","$N用力的將$n搬上旗台，但是$N太累了偷懶休息。","$N默默的放空發着呆，不知道在想些什麼。","$N不斷的忙碌着，但卻不知道在忙些什麼。"});
	if(!me || !ob || !num || !startnow) return;
	if(me->is_fighting() || !environment(me)->query("stab_flag")) {
		message_vision(HIY"$N裝設旗子的動作被打斷了。\n"NOR, me);
		if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
		me->delete_temp("flag_war/stab_now");
		me->start_busy(5);
    return;
	}
  if(num <= 1) {
  reward = 50;
  pa = me->query_temp("flag_war/stab_count");
  if(pa >= 2) reward = reward/pa;
  if(reward < 5) reward = 5;
  message_flag_tell(party_str[me->query_temp("flag_war/party")]+HIG+"的"+me->query_idname()+HIG+"在"+environment(me)->short()+HIG+"將"+ob->name()+HIG+"插上旗台了。");
  me->add_temp("flag_war/stab_count", 1);
  me->delete_temp("flag_war/stab_now");
  if(me->query_temp("flag_war/stab_event_id")) SCHEDULE_D->delete_event(me->query_temp("flag_war/stab_event_id"));
  me->delete_temp("flag_war/stab_event_id");
	if(me->query_temp("flag_war/party") == "blue") {
		bfin++;
		me->set_temp("title", HIB"搶旗藍隊"NOR);
	} else {
		rfin++;
		me->set_temp("title", HIR"搶旗紅隊"NOR);
  }
  me->delete_temp("flag_war/move_busy");
  add_score(me, reward);
  destruct(ob);
  SCHEDULE_D->set_event(RESET_TIME+random(RESET_TIME), 0, this_object(), "put_flag_in_room", "random");
  } else {
  num--;
	stab_event_id = SCHEDULE_D->set_event(1, 0, this_object(), "stab_flag_count", num, me,ob);
	me->set_temp("flag_war/stab_event_id", stab_event_id);
	me->start_busy(5);
	message_vision(msgs[random(sizeof(msgs))] +"\n" , me, ob);
  }
}
int add_score(object me, int reward)
{
	if(!me || !reward) return 0;
	if(!me->query_temp("flag_war/party")) return 0;
	if(set_score(me->query("id"), me->query_temp("flag_war/party"), reward)) {
	message_flag_tell(me->query_idname()+HIG+"為"+party_str[me->query_temp("flag_war/party")]+HIG+"奪得 "+reward+" 分。");
  } else {
  	tell_object(me, "分數增加出錯，請使用 sos post 回報。\n");
    return 0;
  }
  return 1;
}
int set_score(string id, string party, int reward)
{
	if(!id || !party || !reward) return 0;
	if(member_array(id, keys(red)) != -1) {
		red[id] += reward;
	  rsc += reward;
	  return 1;
	} else {
		blue[id] += reward;
		bsc += reward;
		return 1;
	}
	return 0;
}

string query_party_score(string party)
{
	int scs, scs2;
	string result;
	mapping partys;
	object pp;
	result = "";
	if(party == "blue") {
		scs = bsc;
		scs2 = bfin;
		partys = blue;
	} else {
		scs = rsc;
		scs2 = rfin;
		partys = red;
	}
	result += sprintf(" "+party_str[party]+"： 隊伍人數 %d 人、目前積分 %d 分、插旗成功\ %d 次。\n", sizeof(partys), scs, scs2);
	foreach(string ppid, int ppnum in partys) {
		if(!objectp(pp = find_player(ppid))) continue;
		if(pp->query_temp("flag_war/party") != party) continue;
		result += sprintf("  "+"%-12s %-30s 積分：%d 分\n", pp->query_temp("title"), ANSI_D->remove_ansi(pp->query_idname()), ppnum);		
	}
	return result;
}

string query_party_score_total()
{
	return sprintf("總參加人數： %d 人、總獎金：%s、進行時間：%s\n", sizeof(all_player), MONEY_D->money_str(reward_money), time_period(time() - start_time));
}

void put_flag_in_room(string t)
{
	  object flag, room;
	  string *all_flag_room;
	  if(!t) return;
		flag = new(FLAG_OB);
		switch(t) {
			case "west":
       flag->move(load_object(WEST_FLAG));
       message_flag_tell(flag->name()+HIG+"出現在"+environment(flag)->short()+"。");
			break;
			case "east":
			 flag->move(load_object(EAST_FLAG));
			 message_flag_tell(flag->name()+HIG+"出現在"+environment(flag)->short()+"。");
			break;
			case "random":
			 all_flag_room = ({WEST_FLAG,EAST_FLAG,CENTER_FLAG});
			 room = load_object(all_flag_room[random(sizeof(all_flag_room))]);
			 flag->move(room);
			 message_flag_tell(flag->name()+HIG+"出現在"+environment(flag)->short()+"。");
			break;
			default:
			 flag->move(load_object(CENTER_FLAG));
			 message_flag_tell(flag->name()+HIG+"出現在"+environment(flag)->short()+"。");
			break;
		}
}

int sort_user(object ob1, object ob2)
{
    return (ob2->query("level") - ob1->query("level"));
}
