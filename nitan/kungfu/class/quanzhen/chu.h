// chu.h 處字輩收徒

int accept_object(object ob, object obj)
{
        object me = this_object();

        if( query("id", obj) == "quanzhenxin2" && query_temp("have_letter", ob) )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say好，"+query("name", ob)+"，你願意拜我為師嗎？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say 這東西給我可沒有什麼用。");
        command("give"+query("id", obj)+"to"+query("id", me));
        return 0;

}

void destroying(object me, object obj)
{
        destruct(obj);
        return;
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);
        string name, new_name;
        name=query("name", ob);

        if ((int)ob->query_skill("xiantian-qigong",1) < 70 ) {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<10000){
                command( "say 行俠仗義是我輩本份，你若能多做些俠義之事，我一定收你為徒。\n");
                return;
        }
        if( query("gender", ob) == "男性" && query("gender", me) == "女性"){
                command("say 我不收男徒，你還是去拜我幾位師兄為師吧。\n");
                return;
        }
        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "全真教" )
        {
                command("say 我教為玄門正宗，" + RANK_D->query_respect(ob) + "若要學藝，還是先找本門四代弟子吧。");
                return;
        }
        if ( ob_fam["generation"] == 0 )
        {
                command("say 無量壽佛！你還是先找四代弟子學點基本功吧。");
                return;
        }
        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say "+RANK_D->query_respect(ob)+"，貧道哪裏敢當！");
                return;
        }
        if ( ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say 我和"+ob_fam["master_name"]+"搶徒弟，哈哈哈！");
                command("recruit "+query("id", ob));
        }
        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say 是"+ob_fam["master_name"]+"叫你來找我的？好，好。");
                        command("say 貧道看你是可塑之才，你就安心學藝吧！");
                        if( query("class", ob) == "quanzhen" )
                        {
                                new_name = name[0..1] + "志" + name[4..5];
                                set("name", new_name, ob);
                                command("say 從今以後你的道號叫做"+new_name+ "，你現在是全真教志字輩弟子了。");
                        }
                        else command("say 你沒有出家，我雖可以收你，以後你可別後悔了。");
                        command("recruit "+query("id", ob));
                }
                else
                {
                        command("say " + RANK_D->query_respect(ob) + "，你沒有推薦信，不能越級拜師。");
                        return;
                }
        }
        return;
}
