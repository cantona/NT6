void init()
{
        object me, ob;
        mapping fam;
        ::init();
        ob = this_player();
        me = this_object();
        if (interactive(ob) && userp(ob)
         && !query("no_fight", environment(ob) )
        && !present("tieyan ling", ob) 
         && ((fam=query("family", ob)) && fam["family_name"] != "明教")){
             if( !query_temp("warned", ob)){
                   command("say 你是誰？  怎麼闖到光明頂裏來了？！");
                   command("say 快給我速速離開，下次看到決不輕饒！");
                   set_temp("warned", 1, ob);
                   }
              else if( query_temp("stay", ob)<3)addn_temp("stay", 1, ob);
              else {
                   command("say 大膽狂徒，竟敢闖到明教來撒野！！！\n");
                   remove_call_out("hiting_ob");
                   call_out("hiting_ob", 1, ob);
                   }
        }       
}
int hiting_ob(object ob)
{
     object me;
     me=this_object();
     if(objectp(ob) && present(ob, environment(me)) && 
        !query("no_fight", environment(me))){
        me->set_leader(ob);
        ob->kill_ob(me);
        me->fight_ob(ob);
        remove_call_out("moving_ob");
        call_out("moving_ob",1,ob);
        }
      else if( query("startroom", me))me->move(query("startroom", me));
      else return 0;
}

void moving_ob(object ob)
{
        if (!ob) return;
     if (!living(ob)){
        switch( random(3) ) {
           case 0: command("say 哼，看你以後還敢不敢亂闖光明頂！！！"); break;
           case 1: command("say 交給冷大人處理吧，關他一年半月的。"); break;
           case 2: command("nod"); break;
           }
        ob->move("/d/mingjiao/jianyu");
        }
     else{
        remove_call_out("hiting_ob");
        call_out("hiting_ob",1,ob);
        }
}
