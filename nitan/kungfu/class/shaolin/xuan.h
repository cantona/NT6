// xuan.h for fight and get letter from Xuan

#include "shaolin.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

#if IS_XUAN_CI
        int r;

        if (r = ::accept_object(ob, obj))
                return r;
#endif

        if( query("id", obj) == "tuijian xin4" && 
            query_temp("have_letter", ob) )
        {
                set_temp("apprentice_ok", 1, ob);
                command("say 好，"+query("name", ob)+
                        "，你願意拜我為師嗎？");
                destruct(obj);
                return 1;
        }

        command("smile");
        command("say 這東西給我可沒有什麼用。");
        command("give "+query("id", obj)+" to "+query("id", me));
        return 0;
}

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

        if (ob_fam["generation"] <= my_fam["generation"])
        {
                command("say " + RANK_D->query_respect(ob) +
                        "，貧僧哪裡敢當 !");
                return;
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say " + ob_fam["master_name"] +
                        "的徒弟怎麼跑到我這兒來了，哈哈哈 !");
                command("recruit "+query("id", ob));
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 2))
        {
                if( query_temp("apprentice_ok", ob) || 
                    query("luohan_winner", ob) )
                {
                        delete_temp("have_letter", ob);
                        delete_temp("apprentice_ok", ob);
        
                        command("say 是" + ob_fam["master_name"] +
                                "叫你來找我的吧，哈哈哈！");
                        command("say 貧僧又得一可塑之才，真是可喜可賀！");

                        name=query("name", ob);
                        new_name = "澄" + name[2..3];
                        set("name", new_name, ob);

                        command("say 從今以後你的法名叫做" + new_name +
                                "，恭喜你榮升為少林派澄字輩弟子！");
                        command("recruit "+query("id", ob));
                } else
                {
                        command("say " + RANK_D->query_respect(ob) +
                                "，你即沒有推薦信，也沒有過羅漢陣，"
                                "不能越級拜師。");
                        return;
                }
        }

        return;
}
