// TangZhu.h for fight and get letter from TangZhu

#include "mingjiao.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("tuijian xin4",ob) )
        {
                command("say 怎麼樣，你拿我的推薦信去拜法王了嗎 ?");
                return 0;
        }

        if( (query("id", obj) == "tieyan ling" )
        && ob_fam["family_name"] == "明教"
         && ob_fam["generation"] == query("family/generation", me)+1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已得到教主許可，我們就來驗証一下武功。");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }
        
        if( query("id", obj) == "tuijian xin3"
         && query_temp("have_letter", ob )
        && ob_fam["generation"] == my_fam["generation"] + 2)
        {
                set_temp("apprentice_ok", 1, ob);
                command("say 好，"+query("name", ob)+"，你願意拜我為師嗎？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        command("smile");
        command("say 這東西給我可沒有什麼用。");
        command("give "+query("id", obj)+" to "+query("id", me));
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
                command("say 青出於藍勝於藍，不愧是我明教的佳弟子 ! 恭喜你了 !\n");
                message_vision("$N交給$n一封推薦信。\n", me, ob);
                set_temp("have_letter", 1, ob);
                obj=new("/d/mingjiao/obj/tuijianxin-4");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看來" + RANK_D->query_respect(ob) + 
                        "還得多加練習，方能在明教諸多弟子中出人頭地 !\n");
                return 1;
        }

        return 1;  
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob) )
                return;

        name=query("name", ob);

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "與本教素無來往，不知此話從何談起？");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，在下哪裡敢當 !");
                return;
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 1) )
        {
                command("say " + ob_fam["master_name"] + "的徒弟怎麼跑到我這兒來了，哈哈哈 !");
                command("recruit "+query("id", ob));
        }

        if ( ob_fam["generation"] == (my_fam["generation"] + 2) )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say 是" + ob_fam["master_name"] + "叫你來找我的吧，哈哈哈 !");
                        command("say 本堂又得一可塑之才，真是可喜可賀 !");
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
