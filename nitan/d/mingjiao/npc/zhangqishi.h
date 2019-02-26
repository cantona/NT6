// ZhangQiShi.h for fight and get letter from ZhangQiShi
#include "mingjiao.h"

void init()
{
        object me,ob;
        me = this_object () ;
        ob = this_player () ;

        ::init();

        if( interactive(this_player()) && query_temp("fighting", this_player()) )
        {
                COMBAT_D->do_attack(this_object(), this_player(), query_temp("weapon") );
                addn_temp("beat_count", 1, this_player());
        }       
}

int accept_object(object ob, object obj)
{
        string name;
        string job_flg;
        object me = this_object();

        mapping ob_family=query("family", ob);
        name=query("id", obj);

        if( name == "huo qiang" && query("id", me) == "xin ran" )
        {
                job_flg = judge_jobmsg(ob,1);

                if ( job_flg !=  "打造火槍" ) 
                {
                        command("hmm"+query("id", ob));
                        command("say 閣下沒有這項工作，哪裏來的火槍？這火槍甚是危險，我先收下了。");
                        destruct(obj);
                        return 1;
                }
                else
                {
                        command("thumb "+query("id", ob));
                        command("say 這位兄弟辛苦了!下去好好休息休息！");
                        destruct(obj);
                        call_out("reward",0,ob,"打造火槍"); 
                        return 1;
                }
        }

        if( query_temp("have_letter", ob) && present("tuijian xin3",ob) )
        {
                command("say 怎麼樣，你拿我的推薦信去見五散人了嗎 ?");
                return 0;
        }

        if( (query("id", obj) == "tieyan ling" )
        && ob_family["family_name"] == "明教"
         && ob_family["generation"] == query("family/generation", me)+1
         && !query_temp("have_letter", ob) )
        {
                set_temp("fight_ok", 1, ob);
                command("say 好，既然已得到教主許可，我們就來驗證一下武功。");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

        if( query("id", obj) == "tuijian xin2"
         && query_temp("have_letter", ob )
         && ob_family["generation"] == query("family/generation", me)+2 )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say 好，"+query("name", ob)+"，你願意加入我旗嗎？");
                remove_call_out("destroying");
                call_out("destroying", 1, me, obj);
                return 1;
        }

       
        command("?");
        command("say 這東西給我可沒有什麼用。");
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
                obj=new("/d/mingjiao/obj/tuijianxin-3");
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
        object me;
        mapping ob_family;
        string qi,new_rank;

        me=this_object();

        if (! permit_recruit(ob) )
                return;

        if( !mapp(ob_family=query("family", ob)) || ob_family["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "與本教素無來往，不知此舉是何用意？");
                return;
        }

        if( query("family/generation", me) >= query("family/generation", ob) )
        {
                command("say " + RANK_D->query_respect(ob) + "，在下哪裏敢當 !");
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+1 )
        {
                command("say "+query("family/master_name", ob)+"的徒弟怎麼跑到我這兒來了，哈哈哈!");
                command("recruit "+query("id", ob));
                return;
        }

        if( query("family/generation", ob) == query("family/generation", me)+2 )
        {
                if( query_temp("apprentice_ok", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say 哈哈哈 !");
                        command("say 本旗又得一可塑之才，真是可喜可賀 !");
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
