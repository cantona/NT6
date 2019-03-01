// /d/shenlong/sg_process.h
// Last Modified by winder on Jul. 12 2002

void sg_process()
{
        object pang_ob;
        mixed spys;
        mapping sg_ob;
        int t, bonus;

// list all spys on line
        spys = filter_array(users(), "is_spy", this_object());

        remove_call_out("sg_process");
        if( !sizeof(spys) )
        {
                call_out("sg_process", 10000);
                return;
        } else call_out("sg_process", 1000);

// do zhong job to persuade highhands to leave shenlong
        if( !random(10) ) message_zhong(spys);

// do hong job to chase those highhands who refused to leave shenlong
        if( !random(100) ) message_hong(spys);
}

void message_zhong(object *spys)
{
        mixed leaver;
        object ob, zhong_ob, *obj;
        int i;

        if(sizeof(leaver = filter_array(spys, "is_leaving", this_object())) < 1)
                return;

        obj = filter_array(children(SGNPCS + "zhong.c"), (: clonep :));
        if( sizeof(obj) )
        {
                zhong_ob = obj[0];
                if( !living(zhong_ob) ||
                        query("sgwork/persuaded", zhong_ob) || 
                        zhong_ob->is_busy() || zhong_ob->is_fighting() )
                        return;
        } else zhong_ob = new(SGNPCS + "zhong.c");

        ob = leaver[random(sizeof(leaver))];

        message("vision", zhong_ob->name() + "急急忙忙地離開了。\n", environment(zhong_ob), ({zhong_ob}));
        zhong_ob->move(environment(ob));
        message_vision("\n$N走了過來。\n", zhong_ob);
        zhong_ob->set_leader(ob);
        set("sgwork/persuaded", 1, zhong_ob);

        call_out("persuade_leave", 1, zhong_ob, ob);
}

void persuade_leave(object zhong_ob, object ob)
{
        if( !zhong_ob ) return;

        if( !living(zhong_ob) )        
        {
                call_out("persuade_leave", 5, zhong_ob, ob);
                return;
        }
        if( !ob || environment(zhong_ob) != environment(ob) ||
                !query("sg/spy", ob) )
        {
                call_out("destroy_ob", 1, zhong_ob);
                return;
        }
        if( !living(ob) )
        {
                call_out("persuade_leave", 10 + random(10), zhong_ob, ob);
                return;
        }
        if( !query_temp("yield", zhong_ob) )
                set_temp("yield", 1, zhong_ob);

        message_vision("\n$N對$n苦苦規勸道：既然教主不再信任你，你還是儘快離開神龍教吧。\n", zhong_ob, ob);
        if( !query_temp("zhong/nod", ob) )
                set_temp("zhong/nod", 1, ob);
        tell_object(ob, "你只要打一個指令：leave shenlong，就算離開神龍了。\n");
        addn_temp("sg/zhong_persuade", 1, ob);

        if( query_temp("sg/zhong_persuade", ob)>3 )
        {
                addn("sg/zhong_persuade", 1, ob);
                set("sg/zhong_time", time(), ob);
                call_out("destroy_ob", 10 + random(10), zhong_ob);
        } else call_out("persuade_leave", 10 + random(10), zhong_ob, ob);
}

void message_hong(object *spys)
{
        mixed discarder;
        object *obj, ob, hong_ob, dest;
        string file;
        int i;

        if( sizeof(discarder =
                filter_array(spys, "is_discarding", this_object())) < 1 )
                return;
        obj = filter_array(children(SGNPCS + "hong.c"), (: clonep :));
        if( !sizeof(obj) ) return;
        hong_ob = obj[0];
        if( !living(hong_ob) || query("sgwork/chased", hong_ob) || 
                hong_ob->is_busy() || hong_ob->is_fighting() )
                return;
        ob = discarder[random(sizeof(discarder))];

        if( !(dest = environment(ob)) ) return;

        file = base_name(dest);
        if( query("no_fight", dest) || 
                strsrch(file, "/u/") == 0 ||
                strsrch(file, "/d/death/") == 0 ||
                strsrch(file, "/d/wizard/") == 0 ||
                strsrch(file, "/d/gaibang/") == 0 ||
                strsrch(file, "/d/taohua/") == 0 ||
                strsrch(file, "/d/xiakedao/") == 0 )  return;

        message("vision", hong_ob->name() + "急急忙忙地離開了。\n", environment(hong_ob), ({hong_ob}));
        hong_ob->move(dest);
        message_vision("\n$N走了過來。\n", hong_ob);
        hong_ob->set_leader(ob);
        "/cmds/std/look"->main(hong_ob,query("id", ob));
        set("sgwork/chased", 1, hong_ob);

        call_out("do_killing", 3 + random(10), hong_ob, ob);
}

void do_killing(object hong_ob, object ob)
{
        object dest;
        string file;

        if( !hong_ob ) return;
        if( !living(hong_ob) )
        {
                call_out("do_killing", 5, hong_ob, ob);
                return;
        }
        if( !ob || !query("sg/spy", ob) || !(dest=environment(ob)) )
        {
                call_out("destroy_ob", 1, hong_ob);
                return;
        }

        file = base_name(dest);
        if( dest != environment(hong_ob) ||
                query("no_fight", dest) || 
                strsrch(file, "/u/") == 0 ||
                strsrch(file, "/d/death/") == 0 ||
                strsrch(file, "/d/wizard/") == 0 ||
                strsrch(file, "/d/gaibang/") == 0 ||
                strsrch(file, "/d/taohua/") == 0 ||
                strsrch(file, "/d/xiakedao/") == 0 )
        {
                call_out("destroy_ob", 1, hong_ob);
                return;
        }
        message_vision(RED"\n$N對$n大聲喝道："+ RANK_D->query_rude(ob) + "！在教中這麼多年居然毫無建樹，我廢了你吧！！！\n\n"NOR, hong_ob, ob);
        hong_ob->kill_ob(ob);
        call_out("check_killing", 1, hong_ob, ob);
}

void check_killing(object hong_ob, object ob)
{
        object dest;
        string file;

        if( !hong_ob ) return;
        if( !living(hong_ob) )
        {
                call_out("check_killing", 5, hong_ob, ob);
                return;
        }
        if( !ob || !query("sg/spy", ob) || !(dest=environment(ob)) )
        {
                call_out("destroy_ob", 1, hong_ob);
                return;
        }
        file = base_name(dest);
        if( dest != environment(hong_ob) ||
                query("no_fight", dest) || 
                strsrch(file, "/u/") == 0 ||
                strsrch(file, "/d/death/") == 0 ||
                strsrch(file, "/d/wizard/") == 0 ||
                strsrch(file, "/d/gaibang/") == 0 ||
                strsrch(file, "/d/taohua/") == 0 ||
                strsrch(file, "/d/xiakedao/") == 0 )
        {
                call_out("destroy_ob", 1, hong_ob);
                return;
        }
        call_out("check_killing", 1, hong_ob, ob);
}

private int is_spy(object ob)
{
        if( !query("sg/spy", ob))return 0;
        return 1;
}

private int is_open(object ob)
{
        if( !query_temp("pang_message", ob))return 0;
        return 1;
}

private int is_leaving(object ob)
{
        if( query("combat_exp", ob)>500000 && 
                query("sg/exp", ob)*100<query("combat_exp", ob) && 
                time()>query("sg/zhong_time", ob)+259200 && 
                query("sg/zhong_persuade", ob)<4 )
                return 1;
        return 0;
}

private int is_discarding(object ob)
{
        if( query("sg/zhong_persuade", ob) >= 3 && 
                query("sg/spy", ob) )
                return 1;

        return 0;
}
