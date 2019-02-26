// Code of JHSH
// mingjiao job file

#include <ansi.h>
#define OBJ_PATH "/d/mingjiao/obj"
#define MINGJIAO "/d/mingjiao/"
#include "/d/mingjiao/obj/time_all.h"
#define BASE 80

string judge_jobmsg(object player,int flg)
{
        string s_msg,job_msg,job_flg;
        s_msg=query("mingjiao/job", player);

        switch (s_msg)
        {
                case "jin_caikuang":
                        job_flg="採集鐵礦";break;

                case "huo_zaoqiang":
                        job_flg="打造火槍";break;

                case "shui_tiaoshui":
                        job_flg="挑水";break;

                case "mu_kanshu":
                        job_flg="砍樹";        break;

                case "tu_didao":
                        job_flg="挖地道"; break;

//                default:
//                        job_msg="這位"+RANK_D->query_respect(player)+"現在好像沒有任務在身。";
//                        return job_msg;
//                        write("judge_jobmsg reached default! please report.\n");
        }

        if(flg)
        return job_flg;

        job_msg="這位"+RANK_D->query_respect(player)+"現在不是"+job_flg+"嗎？等完成了再來領取其它任務吧。";
        return job_msg;
}

int cut_abandon_jl(string job_kind)
{
        int cut_cc;

        switch (job_kind)
        {
                case "採集鐵礦":
                        cut_cc=BASE+random(BASE*2)/2; break;
                case "打造火槍":
                        cut_cc=BASE+random(BASE*3)/2; break;
                case "挑水":
                        cut_cc=BASE+random(BASE*3)/2; break;
                case "砍樹":
                        cut_cc=BASE+random(BASE*2)/2; break;
                case "挖地道":
                        cut_cc=BASE+random(BASE*2)/2; break;
        }

        if( query("family/gongji", this_player()) )
                addn("family/gongji", -cut_cc, this_player());
        if( query("family/gongji", this_player())<0 )
                delete("family/gongji", this_player());
        tell_object(this_player(),RED"你的明教功績下降了"+cut_cc+"點。\n"NOR);

        delete("mingjiao/job", this_player());

        return 1;
}




string ask_abandon()
{
        object player;
        string job_flg, id, name;
        player=this_player();

        if( !query("mingjiao/job", player) )
                return "這位"+RANK_D->query_respect(player)+"現在好像沒有任務在身。";

        job_flg=judge_jobmsg(player,1);

        switch (job_flg)
        {
                case "採集鐵礦":
                        id = "zhuang zheng"; name = "莊錚"; break;
                case "打造火槍":
                        id = "xin ran"; name = "辛然"; break;
                case "挑水":
                        id = "tang yang"; name = "唐洋"; break;
                case "砍樹":
                        id = "wen cangsong"; name = "聞蒼松"; break;
                case "挖地道":
                        delete_temp("didao_done", player);
                        id = "yan yuan"; name = "顏垣"; break;
        }

        if( query("id", this_object()) == id && query("name", this_object()) == name )
        {
                if(cut_abandon_jl(job_flg))
                        return "閣下連這種事情都辦不好，將來如何光大我光明聖火教。";
                else
                        return "閣下盡力完成這次任務吧。";
        }
        else
                return "既然這位"+RANK_D->query_respect(player)+"想放棄"+job_flg+"的任務，請去跟"+name+"旗主説一聲。";

        return "ask_abandon() has error!";
}



void reward(object me, string job_flg)
{
        int old_cc,add_cc,max_pot, add_exp,add_pot;
        mixed old_pot;

        if (!me) return;

        old_cc=query("family/gongji", me);
        old_pot=query("potential", me);

        switch(job_flg)
        {
                case "採集鐵礦":
                        add_cc=BASE+random(BASE*2)/2;                // BASE = 100
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "打造火槍":
                        add_cc=BASE+random(BASE*3)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "挑水":
                        add_cc=BASE+random(BASE*3)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "砍樹":
                        add_cc=BASE+random(BASE*2)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
                case "挖地道":
                        add_cc=BASE+random(BASE*2)/2;
                        add_exp=BASE+random(add_cc);
                        add_pot=add_exp/3+random(add_exp/4);
                        break;
        }

        delete("mingjiao/job", me);

        add_cc /= 10;
        addn("family/gongji", add_cc, me);
        addn("combat_exp", add_exp, me);
        addn("potential", add_pot, me);
        //if (me->query("potential") > me->query_potential_limit())
        //        me->set("potential",me->query_potential_limit());
        tell_object(me,HIG"恭喜！你的明教功績上升了"+add_cc+"點。\n"NOR);
        tell_object(me,HIG"你的經驗上升了"+add_exp+"點。\n"NOR);
        tell_object(me,HIG"你的潛能上升了"+add_pot+"點。\n"NOR);

}
