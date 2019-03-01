// qing.h for fight and get letter from Qing

#include "shaolin.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("tuijianxin1",ob) )
        {
                command("say 怎麼樣，你拿我的推薦信去拜師了嗎 ?");
                return 0;
        }

        if( (query("id", obj) == "damo ling") && 
            ob_fam["generation"] == my_fam["generation"] + 1 &&
            !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已得到方丈許可，我們就來驗証一下武功。");
                destruct(obj);
                return 1;
        }
        
        command("smile");
        command("say 這東西給我可沒有什麼用。");
        command("give "+query("id", obj)+" to "+query("id", me));
        return 0;
}

int accept_fight(object ob)
{
        object me = this_object();
        
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
                call_out("checking", 2, me, ob);
                return 1;
        }

        if (! present(ob, environment())) return 1; 

        if( (query("qi", me)*100/my_max_qi) <= 50 )
        {
                command("say 青出於藍勝於藍，不愧是少林寺的佳弟"
                        "子！恭喜你了！\n");
                message_vision("$N交給$n一封推薦信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/shaolin/obj/tuijianxin-1");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看來" + RANK_D->query_respect(ob) + 
                        "還得多加練習，方能在少林諸多弟子中出人頭地 !\n");
                return 1;
        }

        return 1;  
}

#ifdef DEFINED_ATTEMPT_APPRENTICE
#else

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || 
            ob_fam["family_name"] != "少林派")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "與本派素無來往，不知此話從何談起？");
                return;
        }

        if( query("class", ob) != "bonze" && 
             ob_fam["family_name"] == "少林派") 
        {
                command("say " + RANK_D->query_respect(ob) + 
                        "是俗家弟子，不能在寺內學藝。");
                return;
        }

        if (ob_fam["generation"] == 0)
        {
                command("say 阿彌陀佛！貧僧就收下你做我的弟子了。");
                command("recruit "+query("id", ob));
                return;
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎麼跑到"
                        "我這兒來了，哈哈哈！");
                command("recruit "+query("id", ob));
        }

        if (ob_fam["generation"] <= my_fam["generation"])
        {
                command("say " + RANK_D->query_respect(ob) +
                        "，貧僧哪裡敢當 !");
                return;
        }

        return;
}
#endif
