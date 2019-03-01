// zhi.h 志字輩收徒和推薦給處字輩

int accept_object(object ob, object obj)
{
        object me = this_object();

        mappingmy_fam=query("family", me);
        mappingob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("quanzhenxin2",ob) )
        {
                command("say 怎麼樣，你拿我的推薦信去拜師了嗎 ?");
                return 0;
        }

        if( (query("id", obj) == "quanzhenling" )
        && ob_fam["family_name"] == "全真教"
        && ob_fam["generation"] == my_fam["generation"] + 1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已有掌門真人許可，我們就來驗証一下武功。");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }
        
        if( query("id", obj) == "quanzhenxin1" && query_temp("have_letter", ob) )
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

int accept_fight(object ob)
{
        object me  = this_object();
        
        if( !query_temp("fight_ok", ob))return 0;

        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        delete_temp("fight_ok", ob);
        
        return 1;
}

int checking(object me, object ob)
{
        object obj;
        int my_max_qi, his_max_qi;

        my_max_qi=query("max_qi", me);
        his_max_qi=query("max_qi", ob);

        if (me->is_fighting()) 
        {
                call_out("checking",2, me, ob);
                return 1;
        }

        if ( !present(ob, environment()) ) return 1; 

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                command("say 青出於藍勝於藍，不愧是全真門下弟子！恭喜你了！\n");
                message_vision("$N交給$n一封推薦信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/quanzhen/obj/tuijianxin-2");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看來" + RANK_D->query_respect(ob) + 
                        "還得多加練習，方能在本教諸多弟子中出人頭地！\n");
                return 1;
        }

        return 1;  
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);
        string name, new_name;
        name=query("name", ob);

        if ((int)ob->query_skill("xiantian-qigong",1) < 30 ) {
                command("say 你的本門內功心法火候不足,難以領略更高深的武功。");
                return;
        }
        if( query("shen", ob)<1000){
                command( "say 行俠仗義是我輩學武人的基本品質，你若能多做些俠義之事，我一定收你為徒。\n");
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
                command("say "+RANK_D->query_respect(ob)+"，貧道哪裡敢當！");
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
                                new_name = name[0..1] + "清" + name[4..5];
                                set("name", new_name, ob);
                                command("say 從今以後你的道號叫做"+new_name+ "，你現在是全真教清字輩弟子了。");
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
