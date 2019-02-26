void destroy(object me)
{
              destruct(me);
}

/*
void init()
{
        object ob;

        ::init();

        ob = this_player();
}
*/

void checking(object me,object ob)
{
        object room;
        object robber;
        room = environment(ob);        
          if( query("qi", me)<1){
                  if( query_temp("start_job", ob) == 1 )
                  {
                        addn_temp("killed_mgb", 1, ob);
                  }
                  else
                        addn_temp("help_killed", 1, ob);
              message_vision("$N撲在地上掙扎了幾下，口中噴出幾口"HIR"鮮血"NOR"，死了！\n",me);
                       remove_call_out("destroy");
                 call_out("destroy",1, me);
                  if(ob->query_condition("jobshadi_limit")==0)
                  {
                        message_vision(CYN"\n一個守城宋兵跑過來説道：蒙古靼子暫時被擊退了，$N可以回去覆命了！\n"NOR,ob);
                        set_temp("job_over", 1, ob);
                        delete_temp("start_job", ob);
                  }
                  else
                  {
                 switch( random(2) ) {
                        case 0:
                        message_vision(HIR"城下又爬上來一個蒙古兵士。\n" NOR,ob); 
                        robber=new(__DIR__"robber1");
                        robber->do_change(this_player());
                        robber->move(room);
                        robber->kill_ob(ob);
                        robber->checking(robber,ob);
            ob->kill_ob(robber);
                        break;
                        case 1:
                        message_vision(HIR"城下又爬上來一個蒙古將領。\n" NOR,ob); 
                        robber=new(__DIR__"robber2");
                        robber->do_change(this_player());
                        robber->move(room);
                        robber->kill_ob(ob);
                        robber->checking(robber,ob);
            ob->kill_ob(robber);
//                        robber->checking(robber,ob);
                        break;
                        }       
//                        return 1;
                  }
              return;
        }

        if (me->is_fighting()) 
        {
                call_out("checking",1, me, ob);
           return;
        }

            return;
}

/*
int do_kill(string arg)
{
        object who = this_player();
        object me = this_object();
        if (me->is_fighting()) 
        {
                message_vision(CYN"\n加油！加油！\n"NOR,who);
                return 1;
        }
        if(!arg || present(arg,environment(me))!=me) return 0;
        me->kill_ob(who);
        call_out("checking",1,me,who);
        return 1;
} 

*/
