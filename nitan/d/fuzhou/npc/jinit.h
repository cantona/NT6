// jinit.h 劫匪檢查，自己消失的時間
#define A_TIME 20

void init()
{
        object me, ob, *obs;
        mapping skl;
        string *skillname;
        int i, j, exp, neili, skilllvl;
        me=this_object();

        obs = all_inventory(environment(me));
        exp = 0;
        neili = 0;
        skilllvl = 0;
        for (i=0; i<sizeof(obs); i++)
        {
                if( !living(obs[i]) || obs[i]==me ) continue;
                if( exp<query("combat_exp", obs[i]) )
                        exp=query("combat_exp", obs[i]);
                if( neili<query("max_neili", obs[i]) )
                        neili=query("max_neili", obs[i]);
                skl = obs[i]->query_skills();
                if (!sizeof(skl)) continue;
                skillname = sort_array( keys(skl), (: strcmp :) );
                for (j=0; j<sizeof(skl); j++)
                {
                        if (skilllvl < skl[skillname[j]])
                                skilllvl = skl[skillname[j]];
                }
        }

        if( exp <= 0 ) exp = random(3000) + 1;
                else exp = exp + random(10000) - 7000;
        exp = exp/10 + random(exp/10);
        set("combat_exp", exp, me);

        if( neili <= 0 ) neili = random(50) + 1;
                else neili = (int)(neili/5);
        set("max_neili", neili, me);
        set("neili", neili, me);
        set("jiali", (neili/80+random(neili/80)), me);

        if( skilllvl <= 0 ) skilllvl = random(3) + 6;
        skilllvl = skilllvl / 10 + random(skilllvl/10);
        me->set_skill("jinyan-gong", skilllvl + random(10) - 6);
        me->set_skill("haotian-zhang", skilllvl + random(10) - 6);
        me->set_skill("quanzhen-jian", skilllvl + random(10) - 6);
        me->set_skill("xiantian-qigong", skilllvl + random(10) - 6);
        skilllvl = (int) (skilllvl / 3 * 2);
        me->set_skill("force", skilllvl + random(10) - 4);
        me->set_skill("dodge", skilllvl + random(10) - 4);
        me->set_skill("parry", skilllvl + random(10) - 4);
        me->set_skill("sword", skilllvl + random(10) - 4);
        me->set_skill("unarmed", skilllvl + random(10) - 4);

        me->map_skill("dodge", "jinyan-gong");
        me->map_skill("force", "xiantian-qigong");
        me->map_skill("sword", "quanzhen-jian");
        me->map_skill("parry", "haotian-zhang");

        remove_call_out("do_check");
        call_out("do_check", 1);
}

void do_check()
{
        object me = this_object();
        object ob, cart;
        string *dirs;
        mapping exits;

        remove_call_out("do_check");
        if( !ob = present("biao tou",environment(me)))
        {
                remove_call_out("do_wait");
                call_out("do_wait", 20);
        }
        else
        {
                if(cart = present("cart",environment(me)))
                {
                        message_vision(HIY"\n$N對着$n大喝一聲：“你這"+RANK_D->query_rude(ob)+"，你大爺我可走了！”\n",me,ob);
                        message_vision(HIR"\n鏢車給黃河幫劫匪一路推着，一陣“轟隆隆”響着駛了開去。\n\n"NOR,me);
                        if( mapp(exits=query("exits", environment(me))) )
                                dirs = keys(exits);
                        command("go " + dirs[random(sizeof(dirs))]);
                        cart->move(environment(me));
                        message_vision(HIR"\n鏢車給黃河幫劫匪一路推着，一陣“轟隆隆”響着駛了開去。\n"NOR,me);
                }

                call_out("do_check", 1);
        }
}

void do_wait()
{
        string area, home;
        object ob, cart, where;
        object me = this_object();
        where = environment(me);

        remove_call_out("do_wait");
        if(!ob=present("biao tou",where))
        {
                if (cart=present("cart",where))
                {
                        message_vision("$N冷笑道：“這些臭保鏢的趕不上啦！大爺這就把鏢車拉回山寨了！”\n",me);
                        if (sscanf(file_name(where), "/d/%s/%s", area, home))
message("channel:chat",HIM"【謠言】"+query("guardby", cart)+"保的鏢，在"+to_chinese(area)+"地面上被黃河劫匪奪回山寨去了！\n"NOR,users());
                        cart->move(VOID_OB);
                        destruct(cart);
                        destruct(me);
                }
                remove_call_out("do_check");
                call_out("do_check", 1);
        }
}

