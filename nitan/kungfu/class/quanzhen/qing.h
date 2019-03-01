// qing.h 出家和清字輩收徒和推薦給志字輩
#include "quanzhen.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

        mappingmy_fam=query("family", me);
        mappingob_fam=query("family", ob);

        if( query_temp("have_letter", ob) && present("quanzhenletter1",ob) )
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
                obj=new("/d/quanzhen/obj/tuijianxin-1");
                obj->move(ob);
                return 1;
        }

        if( (query("qi", ob)*100/his_max_qi)<50 )
        {
                command("say 看來" + RANK_D->query_respect(ob) + "還得多加練習，方能在本教諸多弟子中出人頭地！\n");
                return 1;
        }

        return 1;
}

string ask_for_join()
{
        object me = this_player();
        mappingmy_fam=query("family", me);

        if( query("class", me) == "quanzhen" )
                return "無量壽佛！你我同屬玄門，何故跟小道開這等無聊玩笑？\n";

        if( my_fam["family_name"] == "全真教" && my_fam["generation"] <= 4)
                return "無量壽佛！玄門清修之士，應自小開始修行。\n";

        if( query("betrayer", me)>0 )
                return "無量壽佛！你生性反復無常，非我玄門清修之士之所為。\n";

        set_temp("pending/join_quanzhen", 1, me);
        return "無量壽佛！施主若真心皈依我全真教門，請跪下(kneel)受戒。\n";
}

int do_kneel()
{
        object me = this_player();

        string name, new_name;
        if( !query_temp("pending/join_quanzhen", me))return 0;

        message_vision(
                "$N右手捏著蓮花指，恭恭敬敬地磕下頭去。\n\n"
                "$n伸出雙手，將$N頭頂長發挽成一個道髻。\n\n",me,this_object());
        name=query("purename", me);
        if( !name)name=query("name", me);
        new_name = name[0..1] + "靜" + name[2..3];
        command("say 從今以後你的道法號就叫做" + new_name + "。");
        command("smile");
        delete_temp("pending/join_quanzhen", me);
        set("name", new_name, me);
        set("marks/old_name", name, me);
        set("class", "quanzhen", me);
        set("K_record",query("combat/PKS",  me)+query("combat/MKS", me), me);
        set("shen_record",query("shen",  me), me);
        set("shen", 0, me);

        return 1;
}

void attempt_apprentice(object ob)
{
        object me = this_object();
        mapping ob_fam;
        mappingmy_fam=query("family", me);

        if (! permit_recruit(ob))
                return;

        if( query("shen", ob)<0){
                command( "say 行俠仗義是我輩學武人的基本品質，你已快入魔道，我豈能收你為徒。\n");
                return;
        }
        if( query("gender", ob) == "男性" && query("gender", me) == "女性" )
        {
                command("say 我不收男徒，你還是去拜我幾位師兄為師吧。\n");
                return;
        }

        if( ob_fam=query("family", ob) )
        {
                if( ob_fam["generation"] <= my_fam["generation"] &&
                    ob_fam["family_name"] == my_fam["family_name"] )
                {
                        command("say "+RANK_D->query_respect(ob)+"，這個貧道哪敢當！");
                        return;
                }
        }
        if( query("class", ob) != "quanzhen" )
        {
                command ("say 無量壽佛！貧道就收下你做『俗家弟子』了。");
        }
        else
        {
                command ("say 無量壽佛！貧道就收你為全真教正式弟子。");
        }
        command("recruit "+query("id", ob));
}
