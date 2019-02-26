// shizhe.h for fight and get letter from ShiZhe
int accept_object(object ob, object obj)
{
        object me = this_object();

        mapping my_fam=query("family", me);
        mapping ob_fam=query("family", ob);

        if( query("id", obj) == "tuijian xin5"
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

#include "mingjiao.h"

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam=query("family", me);

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if( !(ob_fam=query("family", ob)) || ob_fam["family_name"] != "明教" )
        {
                command("say " + RANK_D->query_respect(ob) + "與本教素無來往，不知此話從何談起？");
                return;
        }

        if ( ob_fam["generation"] <= my_fam["generation"] )
        {
                command("say " + RANK_D->query_respect(ob) + "，小使哪裏敢當 !");
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
                        command("say 本使者又得一可塑之才，真是可喜可賀 !");

                        command("say 恭喜你榮升為明教護教法王！");
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

