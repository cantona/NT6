//tangfeng@SJ 2004
//類似擂台的功能
//胡斐和苗人鳳比武的場地

#include <ansi.h>
inherit ROOM;

void create()
{
	set("short", "練武場");
	set("long", @LONG
這裡是一個破舊的練武場。上千年的踩踏已使得這些石板如同鏡子般平
整光滑。正中央放著一塊大牌子(paizi)。
LONG
	);
  set("no_death", 1);
  set("no_get_from", 1);
  set("no_sleep_room", 1);

  set("item_desc", ([
  "paizi" : "\n準備好了後請打 OK 。如果要放棄比賽，請打 LEAVE 。\n\n",
  ]));
  setup();
}
void init()
{
	object me,ob;
	me = this_player();
	message_vision("$N急急忙忙地走進了練武場。\n", me);
	if (!userp(me)) return;
  add_action("do_leave", "leave");
	if (!me->query_temp("quest/雪山飛狐/武功/fight_id")) return;
	if (!(ob=present(me->query_temp("quest/雪山飛狐/武功/fight_id"),this_object()))) return;
	message_vision(HIG"\n$N對$n點了點頭。\n"NOR,ob,me);
	this_object()->set_temp("biwu",1);
	add_action("do_ok", "ok");
	add_action("do_action", ({"dazuo", "tuna", "lian", "learn", "du", "steal", "hit",
                                  "kill", "fight", "study", "practice", "exercise", "halt", "ask","whisper",
	                          "quit", "save", "throw", "rumor", "tell", "mm", "reply",
	                          "chat", "rumor", "party", "shout", "suicide", "yield"}));
}

int do_action(string arg)
{
	if(!wizardp(this_player())){
		write("練武場上只能比武，請不要做不相關的事！\n");
		return 1;
	}
	else return 0;
}

int do_ok()
{
	object ob, me = this_player();
	if (!me->query_temp("quest/雪山飛狐/武功/fight_id")) return 0;
	if (!(ob=present(me->query_temp("quest/雪山飛狐/武功/fight_id"),this_object()))) return 0;
	if (!ob->query_temp("biwu")) return 0;
        if (this_object()->query_temp("biwu")==2) return 0;
        if (!this_object()->query_temp("biwu")) return 0;
	this_object()->set_temp("biwu",2);
	message_vision(HIR"\n$N做了個鞠："+RANK_D->query_self(ob)+"已經準備好了，願接受任何挑戰！\n"NOR, ob);
	message_vision(HIR"\n$N做了個鞠："+RANK_D->query_self(me)+"已經準備好了，願接受任何挑戰！\n"NOR, me);
  me->kill_ob(ob);
  ob->kill_ob(me);
  remove_call_out("check");
  call_out("check",1,me);
	return 1;
}
void check(object me)
{
	object room,obj,ob;
	if(!me || !living(me)||!present(me,this_object())||me->query("qi")<=1||me->query("jing")<=1||!me->query_temp("quest/雪山飛狐/武功/fight_id"))
	{
		remove_call_out("check");

		//npc動向
		if((ob=present("hu fei",this_object())))
		{
	  	 message_vision(HIW"\n$N一臉高傲的神態：竟然沒人敢來挑戰，看來"+RANK_D->query_self(ob)+"真是天下無敵了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/huanghe/fendi")))
            room = load_object("/d/huanghe/fendi");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("hu fei",room))
       	 {
       	 	message_vision(HIY"$N急急忙忙地離開了練武場。\n"NOR, ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地來到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
    }
		if((ob=present("miao renfeng",this_object())))
		{
	  	 message_vision(HIW"\n$N一臉高傲的神態：竟然沒人敢來挑戰，看來"+RANK_D->query_self(ob)+"真是天下無敵了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/lanzhou/zhenting")))
            room = load_object("/d/lanzhou/zhenting");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("miao renfeng",room))
       	 {
       	 	message_vision(HIC"$N急急忙忙地離開了練武場。\n"NOR, ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地來到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
    }
    //失敗後的去所
    if(userp(me))
    {
    	if(present(me,this_object()))
    	{
       	me->remove_all_killer();
		    me->revive();
    		me->reincarnate();

	  	  message_vision(HIW"\n突然一道神光籠罩著$N，$N的精氣神竟然全部恢復了！\n"NOR, me);
     	 	message_vision(HIY"$N急急忙忙地離開了練武場。\n"NOR, me);
        if(me->query_temp("quest/雪山飛狐/武功/fight_id")=="miao renfeng") me->move("/d/lanzhou/zhenting");
        else me->move("/d/huanghe/fendi");
    		tell_object(me,HIR"\n比賽失敗！下次努力！\n"NOR);
  log_file("quest/FEIHU", sprintf("%s(%s) 較量失敗。經驗：%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
    		message_vision("$N急急忙忙地來到了"+environment(me)->query("short")+"。\n", me);
    	}
    	else	tell_object(me,HIR"\n比賽如此不專心，怎能不失敗？下次努力吧！\n"NOR);
    }
   	me->delete_temp("quest/雪山飛狐/武功/fight_id");
    this_object()->delete_temp("biwu");
	  return;
	}
	if (!(ob=present(me->query_temp("quest/雪山飛狐/武功/fight_id"),this_object())))
	{
		  remove_call_out("check");
      me->add("combat_exp",500+me->query_skill("force")*3/2);
      tell_object(me,HIC"\n經過一番苦鬥，你發現自己的武功大有激進。你獲得"+(500+me->query_skill("force")*3/2)+"點經驗。\n"NOR);

            tell_room(environment(me),HIC"\n"+me->query("name")+"經過一番打鬥，似乎武功大有長進。\n"NOR, ({ me }));
      me->set("quest/雪山飛狐/武功/time",time());
	  me->set("quest/雪山飛狐/武功/fight_exp",me->query("combat_exp"));
      me->remove_all_killer();
	  me->revive();
    	me->reincarnate();
	  	message_vision(HIW"\n突然一道神光籠罩著$N，$N的精氣神竟然全部恢復了！\n\n"NOR, me);
     	message_vision(HIR"$N急急忙忙地離開了練武場。\n"NOR, me);
	  	if(me->query_temp("quest/雪山飛狐/武功/fight_id")=="hu fei")
	  	{
			if(!me->query("quest/雪山飛狐/武功/win_hu")) me->set("quest/雪山飛狐/武功/win_hu",1);
			else me->add("quest/雪山飛狐/武功/win_hu",1);
			log_file("quest/FEIHU", sprintf("%s(%s) 和胡斐較量獲勝。獲得經驗獎勵：%d。經驗：%d。\n", me->name(1),me->query("id"),(500+me->query_skill("force")*3/2),me->query("combat_exp")) );
	  		if (!(room = find_object("/d/huanghe/fendi")))
                   room = load_object("/d/huanghe/fendi");
        obj=new("/d/huanghe/npc/hu-fei");
        if(!present("hu fei",room)) obj->move(room);
        me->move(room);
      }
	  	else if(me->query_temp("quest/雪山飛狐/武功/fight_id")=="miao renfeng")
	  	{
			if(!me->query("quest/雪山飛狐/武功/win_miao")) me->set("quest/雪山飛狐/武功/win_miao",1);
			else me->add("quest/雪山飛狐/武功/win_miao",1);
  log_file("quest/FEIHU", sprintf("%s(%s) 和苗人風較量獲勝。獲得經驗獎勵：%d。經驗：%d。\n", me->name(1),me->query("id"),(500+me->query_skill("force")*3/2),me->query("combat_exp")) );
	  		if (!(room = find_object("/d/lanzhou/zhenting")))
                   room = load_object("/d/lanzhou/zhenting");
        obj=new("/d/lanzhou/npc/miaorenfeng");
        if(!present("miao renfeng",room)) obj->move(room);
        me->move(room);
      }
      else me->move("/d/xiangyang/damen");
    	message_vision("$N急急忙忙地來到了"+environment(me)->query("short")+"。\n", me);
    	me->delete_temp("quest/雪山飛狐/武功/fight_id");
      this_object()->delete_temp("biwu");
    	return;
	}
  call_out("check",1,me);
}

int do_leave()
{
	object ob,room,me = this_player();
  if(this_object()->query_temp("biwu")==2)
  {
  	tell_object(me,HIR"\n你正在比賽之中，無法退出比賽。\n"NOR);
  	return 1;
  }
  me->set("quest/雪山飛狐/武功/time",time());
  me->remove_all_killer();
	me->reincarnate();
	message_vision(HIW"\n$N深嘆了一口氣，退出比武場！\n\n"NOR, me);
	remove_call_out("check");
	if((ob=present("hu fei",this_object())))
	{
	  	 message_vision(HIW"\n$N一臉高傲的神態：竟然沒人敢來挑戰，看來"+RANK_D->query_self(ob)+"真是天下無敵了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/huanghe/fendi")))
            room = load_object("/d/huanghe/fendi");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("hu fei",room))
       	 {
       	 	message_vision("$N急急忙忙地離開了練武場。\n", ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地來到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
  }
  if((ob=present("miao renfeng",this_object())))
	{
	  	 message_vision(HIW"\n$N一臉高傲的神態：竟然沒人敢來挑戰，看來"+RANK_D->query_self(ob)+"真是天下無敵了！\n\n"NOR, ob);
		 ob->remove_all_killer();
	  	 ob->delete_temp("biwu");
	  	 ob->delete_temp("quest/try_fight_id");
			 if (!(room = find_object("/d/lanzhou/zhenting")))
            room = load_object("/d/lanzhou/zhenting");
       if( !room ) destruct(ob);
       else
       {
       	 if(!present("miao renfeng",room))
       	 {
       	 	message_vision("$N急急忙忙地離開了練武場。\n", ob);
       	 	ob->move(room);
			ob->remove_all_killer();
       	 	message_vision("$N急急忙忙地來到了"+environment(ob)->query("short")+"。\n", ob);
       	 }
  	     else destruct(ob);
       }
  }
 	message_vision(HIY"$N急急忙忙地離開了練武場。\n"NOR, me);
  if(me->query_temp("quest/雪山飛狐/武功/fight_id")=="miao renfeng") me->move("/d/lanzhou/zhenting");
  else me->move("/d/huanghe/fendi");
  me->delete_temp("quest/雪山飛狐/武功/fight_id");
	message_vision("$N急急忙忙地來到了"+environment(me)->query("short")+"。\n", me);
   log_file("quest/FEIHU", sprintf("%s(%s) 中止較量。經驗：%d。\n", me->name(1),me->query("id"),me->query("combat_exp")) );
  this_object()->delete_temp("biwu");
	return 1;
}
