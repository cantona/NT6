// by Lonely

int accept_fight(object ob)
{
        object obj, me = this_object();
        int my_max_qi=query("max_qi", me);

        if( query("qi", me)*100/my_max_qi <= 80 )
        {
                call_out("checking1", 1, me, ob);
                return 0;
        }

        remove_call_out("checking1");
        call_out("checking1", 1, me, ob);

        return 1;
}

int accept_kill(object ob)
{
        object obj, me = this_object();

        if( query("id", me) == "ailao" && obj=present("gaolao",environment(me)) )
        {
                command("say 好傢伙，竟想謀害老夫！師弟，準備雙刀合壁！");
                obj->kill_ob(ob);
        }

        if( query("id", me) == "gaolao" && obj=present("ailao",environment(me)) )
        {
                command("say 師兄，準備雙刀合壁超渡這傢伙！");
                obj->kill_ob(ob);
        }

        remove_call_out("checking2");
        call_out("checking2", 1, me, obj, ob);

        return 1;
}

int checking1(object me, object ob)
{
        object obj;

        if( me->is_fighting() && me->is_killing() && !query_temp("hebi", me) )
        {
                if( query("id", me) == "gaolao" && obj=present("ailao",environment(me)) )
                        obj->kill_ob(ob);
                if( query("id", me) == "ailao" && obj=present("ailao",environment(me)) )
                        obj->kill_ob(ob);
                call_out("checking2", 1, me, obj, ob);
        }
        else if (me->is_fighting())
        {
                call_out("checking1", 1, me, ob);
        }

        return 1;
}

int checking2(object me, object obj, object ob)
{
        if (me->is_fighting())
        {
                if (objectp(obj) && !obj->is_fighting())
                {
                        obj->kill_ob(ob);
                }

                if( !query_temp("hebi", me) )
                {
                        if( query("id", me) == "gaolao" )
                                command("perform hebi ai");
                        if( query("id", me) == "ailao" )
                                command("perform hebi gao");
                }

                call_out("checking2", 1, me, obj, ob);
        }

        return 1;
}

int accept_object(object me, object obj)
{
        object ob = this_player();
        int r;

        if (r = ::accept_object(me, obj))
                return r;

        if (me->is_fighting())
                return notify_fail("渾帳！你沒見我正忙着嗎？\n");

        if( query("id", obj) != "zixiapaper" )
                return 0;

        if( query("huashan/yin-jue", ob)>1 )
        {
                remove_call_out("ask_why");
                call_out("ask_why", 1, obj, ob);
                return 1;
        }

        if( query("family/family_name", ob) != "華山派" )
        {
                remove_call_out("thank_other");
                call_out("thank_other", 1, me, obj, ob);
        }
        else
        {
                remove_call_out("thank_huashan");
                call_out("thank_huashan", 1, obj, ob);
        }

        return 1;
}

int ask_why(object obj, object ob)
{
        object me = this_object();

        message_vision("$N皺着眉頭對$n説道：咦！你不是已閉關靜修過了嗎？\n", me, ob);
        command("say 紫霞遺頁交給我保管也好，你還有甚麼事嗎？");

        destruct(obj);
        return 1;
}

int thank_other(object me, object obj, object ob)
{
        message_vision("$N失聲叫道：啊！這竟是本派遺失多年的紫霞遺頁！這。。。本派真是無以為報。\n", me);
        command("say 請受老朽代表華山一脈向" + RANK_D->query_respect(ob) + "至意。");
        command("bow");
        message_vision("$N説完便飛身離去。\n", me);

        destruct(obj);
        destruct(me);
        return 1;
}

int thank_huashan(object obj, object ob)
{
        object ob1, me = this_object();

        message_vision("$N失聲叫道：啊！這竟是本派遺失多年的紫霞遺頁！\n", me);

        if( query("id", me) == "gaolao" && ob1=present("ailao",environment(me)) )
        {
                command("say 讓我和師哥商量商量，你便在此等着吧。");
                message_vision("$N將矮老者拉到一旁細説了一番，只見矮老者臉色變了幾變，兩人低頭沉思着。\n", me);
                me = ob1;
        }
        else if( query("id", me) == "ailao" && present("gaolao",environment(me)) )
        {
                command("say 讓我和師弟商量商量，你便在此等着吧。");
                message_vision("$N將高老者拉到一旁細説了一番。高老者聽罷臉色變了幾變，兩人低頭沉思着。\n", me);
        }
        else
        {
                command("say 讓我仔細研究此箋，你便在此等着吧。");
                message_vision("$N説完後便獨自走到一旁坐下，全神貫注地研讀起着紫霞遺頁來。\n", me);
        }

        remove_call_out("open_room");
        call_out("open_room", 5, me, ob, obj);

        return 1;
}

int open_room(object me, object ob, object obj)
{
        message_vision("$N走了過來，向$n凝視了一陣。\n", me, ob);
        command("say 你既能找回紫霞遺頁，實在是為本派立了個大功。華山有幸了！ ");

        if (file_name(environment(me)) != "/d/huashan/chaoyang")
        {
                command("say 你快回華山去吧，把喜訊告訴大夥兒！");
                message_vision("$N説完便飛身離去。\n", me);
                destruct(obj);
                if (objectp(me))
                        destruct(me);
        }
        else
        {
                command("say 好！我便為你護法。你安心在密室裏閉關修練玄功吧。");
                message_vision("$N將紫霞遺頁交還給$n。\n", me, ob);
                message_vision("接着$N轉身向牆上一處一按一掀，牆壁正中轟隆隆響了一陣，露出一道門來。\n", me);
                command("say 唉！數十年來我始終鑽研不透密室裏的用處，原來還有這個祕密。");
                command("say 好好利用密室裏的東西，小心別把練功的步驟搞錯了！");
                obj->move(ob);
                message_vision("$N走入了門內，石門便緩緩關閉起來。\n", ob);
                ob->move("/d/huashan/stair");
        }

        return 1;
}
