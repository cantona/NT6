// Include file: daozhang.h
// Last Modifyed by Winder on Jan. 14 2002

#include <ansi.h>
#include "wudang.h"
int do_yes();

void attempt_apprentice(object ob)
{
        int i;
        mapping fam,skill_status;
        string *sname;
        string *wudang_skills = ({
                "unarmed",        "taiji-quan",        "wudang-quan",
                "sword",        "taiji-jian",        "liangyi-jian",        "wudang-jian",
                "force",        "taiji-shengong",
                "dodge",        "tiyunzong",
                "literate",        "taoism",
                "parry",
        });

        if (! permit_recruit(ob))
                return;

        if( query("class", ob) == "bonze" )
        {
                command ("say 佛家道家所信不同，你既然已經已經出了家，來我們這裏做什麼呢？");
                return;
        }
        if( query("shen", ob)<0 )
        {
                command("say 我武當乃是堂堂名門正派，對弟子要求極嚴。");
                command("say 在德行方面，" + RANK_D->query_respect(ob) + "是否還做得不夠？");
                return;
        }
        if( query("gender", ob) == "無性" )
        {
                command("say 道家內功練天地正氣，講陰陽調合。");
                command("say 公公無根無性，恐怕修之不宜！");
                return;
        }
        if( mapp(fam=query("family", ob)) && 
                (fam["family_name"] != "武當派") &&
                (skill_status = ob->query_skills()) )
        {
                sname  = keys(skill_status);

                for(i=0; i<sizeof(skill_status); i++)
                if (member_array(sname[i], wudang_skills) == -1)
                {
                        message_vision(this_object()->name()+"哈哈一笑："+ RANK_D->query_respect(ob) + "已經入了" + fam["family_name"]+ "了，怎麼卻來投奔武當？\n", ob);
                        message_vision(this_object()->name()+"頓了頓，正色道：我武當乃堂堂大派，從不拒天下英雄。\n", ob);
                        command( "say 你若誠心投奔武當，須放棄所有雜派功夫，以示誠意！");
                        delete_temp("pending/apprentice", ob);
                        return;
                }
        }
        if( query("title", ob) != "武當道童"
                 && query("family/family_name", ob) != "武當派" )
         {
                command("say 我武當之所以能在武林中興不衰，全靠各弟子自覺效力。");
                command("say 入門習武以前，" + RANK_D->query_respect(ob) + "是否願意為武當主動做些事情？");
                tell_object(ob, HIY"如果你答應的話，鍵入＂願意＂二字。\n"NOR);
                add_action("do_yes", "願意");
                return;
        }
        else
  if( query("wudang/offerring", ob)<query("age", ob)-11 )
                {
                        command("say 未練武，先學做人。在為武當自覺效力方面，");
                        command("say " + RANK_D->query_respect(ob) + "是否還不夠勤勉？");
                        delete_temp("pending/apprentice", ob);
                        return;
                }
        if( mapp(fam=query("family", ob)) && (fam["family_name"] == "武當派") )
                command("say 你我本是同門，貧道就收下你了！");
        else
        {
                command( "say 精誠所至，玉石為開！你為武當勤勉效力，眾道長早已是有口皆碑！");
                command( "say "+RANK_D->query_respect(ob)+"實乃我輩中人也！");
        }

        command("recruit "+query("id", ob));
        delete("class", ob);
}

int do_yes()
{
        object me, ob;

        me = this_object();
        ob = this_player();

        set("wudang/offerring", 1, ob);
        message_vision("$N大聲説道：願意！\n", ob);
        set("title", "武當道童", ob);
        delete_temp("pending/apprentice", ob);
        command("haha ");
        command("say 很好！很好！從今日起，你就是武當一名見習學徒。");
        command("say 希望"+ RANK_D->query_respect(ob) +"勤加努力，早日入我正門中。");

        return 1;
}
