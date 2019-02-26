// fight.h
// 丐幫升袋

int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);
        int r;

        if (r = ::accept_object(ob, obj))
                return r;

        if( query("id", obj) != "qingzhu ling" )
        {
                command("say 啥玩藝？還是自個留着吧。");
                return 0;
        }

        if (! ob_fam || ob_fam["family_name"] != "丐幫")
        {
                command("say 你是從哪裏搞來的青竹令？");
                return 0;
        }

        if( query("combat_exp", ob)<10000 )
        {
                command("say 你這種水平簡長老怎麼會給你青竹令？");
                return 0;
        }

        if( query_temp("have_cloth", ob) && present("po bu",ob) )
        {
                command("say 你不是已經有破布麼？回去找簡長老吧。");
                return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("combat_exp", ob) <= 10000 )
            || (query("family/beggarlvl", ob) == 1
            && query("combat_exp", ob) <= 20000 )
            || (query("family/beggarlvl", ob) == 2
            && query("combat_exp", ob) <= 50000 )
            || (query("family/beggarlvl", ob) == 3
            && query("combat_exp", ob) <= 100000 )
            || (query("family/beggarlvl", ob) == 4
            && query("combat_exp", ob) <= 200000 )
            || (query("family/beggarlvl", ob) == 5
            && query("combat_exp", ob) <= 300000 )
            || (query("family/beggarlvl", ob) == 6
            && query("combat_exp", ob) <= 500000 )
            || (query("family/beggarlvl", ob) >= 7
            && query("combat_exp", ob) <= 800000) )
        {
             command("say 就你那點膿水？我看就算了吧。");
             return 0;
        }

        if( (query("family/beggarlvl", ob) == 0
            && query("title", me) == "丐幫一袋弟子" )
            || (query("family/beggarlvl", ob) == 1
            && query("title", me) == "丐幫二袋弟子" )
            || (query("family/beggarlvl", ob) == 2
            && query("title", me) == "丐幫三袋弟子" )
            || (query("family/beggarlvl", ob) == 3
            && query("title", me) == "丐幫四袋弟子" )
            || (query("family/beggarlvl", ob) == 4
            && query("title", me) == "丐幫五袋弟子" )
            || (query("family/beggarlvl", ob) == 5
            && query("title", me) == "丐幫六袋弟子" )
            || (query("family/beggarlvl", ob) == 6
            && query("title", me) == "丐幫七袋弟子" )
            || (query("family/beggarlvl", ob) == 7
            && query("title", me) == "丐幫八袋弟子" )
            || (query("family/beggarlvl", ob) == 8
            && query("title", me) == "丐幫九袋長老") )
        {
                set_temp("fight_ok",query("id",  me), ob);
                command("say 好吧。既然已有青竹令，那就看你的運氣了。");
                destruct(obj);
                return 1;
        }

        command("hmm");
        command("say 你到底懂不懂我們丐幫升袋的規矩？");
        return 0;
}

int accept_fight(object ob)
{
        if (query_competitor() == ob)
                return 1;

        if (is_fighting())
        {
                command("say 你等會，讓我把面前的這個傢伙放倒再説。");
                return 0;
        }

        if (query("qi") < query("eff_qi") * 2 / 3
           || query("jing") < query("eff_jing") * 2 / 3
           || query("neili") < query("max_neili") * 2 / 3)
        {
                command("say 我現在有點疲倦，待我歇會兒再説。");
                return 0;
        }

        if( query("family/family_name", ob) != query("family/family_name") )
        {
                command("say 免了，我可沒興趣和你動手。");
                return 0;
        }

        if( query_temp("fight_ok", ob) != query("id") )
        {
                command("say 你去向簡長老要了青竹令再來找我。");
                return 0;
        }

        delete_temp("fight_ok", ob);

        command("nod");
        command("say 就讓我試一試你的身手，看看你究竟有啥水平？");
        competition_with(ob);
        return 1;
}

void lost()
{
        object me, ob;

        me = query_competitor();
        set_temp("newtitle", query("title"), me);
        set_temp("have_cloth", 1, me);

        ob = new("/d/gaibang/npc/obj/po-bu");
        set("owner", me->name(1), ob);
        set("from", this_object()->name(1), ob);
        ob->move(this_object());

        command("say 厲害，厲害。既然你勝過了我，這塊破布就拿去吧。");
        command("give po bu to "+query("id", me));
        ::lost();
}

void win()
{
        object me = query_competitor();

        if (! objectp(me))
        {
                command("heihei");
                return;
        }
        command("say 就你這點水平也想升袋？下去練練再來吧。");
        ::win();
}
