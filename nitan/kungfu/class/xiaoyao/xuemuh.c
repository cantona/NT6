// This program is a part of NT MudLIB

#include <ansi.h>
#include "xiaoyao.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
int ask_me();
int ask_heal();
int ask_poison();
void create()
{
        set_name("薛慕華", ({ "xue muhua", "xue", "muhua" }));
        set("long", "他就是號稱閻王敵的神醫薛慕華，據說他\n"
                    "精通醫理，可以起死回生。\n");
        set("gender", "男性");
        set("title", "逍遙派函谷八友");
        set("nickname", HIM "閻王敵" NOR);
        set("age", 50);
        set("class", "shaman");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 27);
        set("con", 25);
        set("dex", 25);

        set("inquiry", ([
                "療傷" : (:ask_me:),
                "治病"  : (: ask_heal :),
                "解毒"  : (: ask_poison :),
        ]) );

        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 3500);
        set("max_neili", 3500);
        set("jiali", 100);
        set("level", 10);
        set("combat_exp", 1000000);

        set_skill("force", 160);
        set_skill("xiaowuxiang", 160);
        set_skill("dodge", 140);
        set_skill("feiyan-zoubi", 140);
        set_skill("strike", 160);
        set_skill("liuyang-zhang", 160);
        set_skill("hand", 160);
        set_skill("qingyun-shou", 160);
        set_skill("parry", 160);
        set_skill("blade", 140);
        set_skill("ruyi-dao", 140);
        set_skill("xiaoyao-qixue", 220);
        set_skill("medical", 220);
        set_skill("literate", 120);
        set_skill("martial-cognize", 140);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("hand", "qingyun-shou");
        map_skill("strike", "liuyang-zhang");
        map_skill("parry", "liuyang-zhang");
        map_skill("blade", "ruyi-dao");
        map_skill("medical", "xiaoyao-qixue");

        prepare_skill("hand", "qingyun-shou");
        prepare_skill("strike", "liuyang-zhang");

        create_family("逍遙派", 3, "弟子");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.zhuo" :),
                (: perform_action, "strike.pan" :),
                (: exert_function, "recover" :),
        }));

        set("master_ob", 3);
        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->query_int() < 26)
        {
                command("sigh");
                command("say 雖然都說勤能補拙，可是……我看你還是走吧。");
                return;
        }

        if (ob->query_skill("xiaowuxiang", 1) < 30)
        {
                command("sigh");
                command("say 你連本門的入門心法都沒有學好，教我如何收你？");
                return;
        }

        command("say 好吧，我就收下你了，以後要多為逍遙派出力啊。");
        command("recruit "+query("id", ob));
}

int ask_me()
{
        object ob=this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say 我現在沒空！");
                return 1;
        }

        if( query("count", me)<1 )
        {
                command("say 傷藥都用完了，我還沒來得及配，你一會再來吧。");
                return 1;
        }
        if( query("shen", ob)<0 )
        {
                command("say 你心術不正，我可不敢為你療傷！");
                return 1;
        }
        if( query("score", ob)<300 && query("combat_exp", ob)>100500 )
        {
                command("say 你這點江湖閱歷，也想讓我為你療傷？");
                return 1;
        }
        if( query("eff_qi", ob) == query("max_qi", ob )
         && query("eff_jing", ob) == query("max_jing", ob) )
        {
                command("?"+query("id", ob));
                command("say 你沒有受任何傷啊？");
                return 1;
        }
        else
        {
                message_vision("薛慕華喂$N服下一顆藥丸，然後盤膝坐下，雙掌貼著$N的背心。\n", ob);
                if( query("combat_exp", ob)>100500 )
                {
                        if( query("family/family_name", ob) != "逍遙派" )
                                addn("score", -200, ob);
                        else addn("score", -100, ob);
                }
                set_temp("busy", 1, me);
                ob->start_busy(2);
                addn("count",-1);
                remove_call_out("recover");
                call_out("recover",2,ob);
                if( query("count", me)<1 )
                {
                        where = environment(me);
                        addn("no_fight", 1, where);
                        remove_call_out("newyao");
                        call_out("newyao",1800,me);
                }
                return 1;
        }
}


int recover(object ob)
{
        delete_temp("busy", this_object());
        set("eff_qi",query("max_qi",  ob), ob);
        set("eff_jing",query("max_jing",  ob), ob);
        message_vision("大約過了一盅茶的時分，薛慕華慢慢地站了起來。\n",ob);
        command("say 你的傷勢已經全好了，可以走啦。");
        return 1;
}
int newyao(object me)
{
        object where = environment(me);
        delete_temp("busy", this_object());
        addn("count", 30, me);
        addn("no_fight", -1, where);
        return 1;
}

int ask_heal()
{
        object ob = this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say 我現在沒空！");
                return 1;
        }

        if( query("shen", ob)<0 )
        {
                command("say 你心術不正，我可不敢為你治病！");
                return 1;
        }
        if( query("score", ob)<300 && query("combat_exp", ob)>100000 )
        {
                command("say 你這點江湖閱歷，也想讓我為你治病？");
                return 1;
        }

        if( ob->query_condition("ill_kesou")
            || ob->query_condition("ill_zhongshu")
            ||ob->query_condition("ill_shanghan")
            ||ob->query_condition("ill_dongshang")
            ||ob->query_condition("ill_fashao"))
        {
                message_vision("薛慕華輕扣$N脈門，略一思索，隨後轉身從藥簍裡取出幾味草藥，開始為$N熬藥。\n", ob);
                if( query("combat_exp", ob)>100000 )
                {
                        if( query("family/family_name", ob) != "逍遙派" )
                                addn("score", -200, ob);
                        else addn("score", -100, ob);
                }
                addn("count", -1, me);
                set_temp("busy", 1, me);
                ob->start_busy(5);
                remove_call_out("recover_II");
                call_out("recover_II",5,ob);
                return 1;
        }

        else
        {
                command("?"+query("id", ob));
                command("say 看你的氣色，並沒有生病啊？");
                return 1;
        }

}
int recover_II(object ob)
{
        delete_temp("busy", this_object());
        if (ob->query_condition("ill_kesou"))
                ob->clear_condition("ill_kesou",0);
        if (ob->query_condition("ill_zhongshu"))
                ob->clear_condition("ill_zhongshu",0);
        if (ob->query_condition("ill_shanghan"))
                ob->clear_condition("ill_shanghan",0);
        if (ob->query_condition("ill_dongshang"))
                ob->clear_condition("ill_dongshang",0);
        if (ob->query_condition("ill_fashao"))
                ob->clear_condition("ill_fashao",0);
        message_vision("大約一柱香過後，薛慕華讓你喝下一碗剛熬好的熱氣騰騰的中藥。\n",ob);
        command("say 你的身體已無大礙,可以走啦。");
        return 1;
}


int ask_poison()
{
        object ob = this_player();
        object me = this_object();
        object where;

        if( me->is_fighting() || query_temp("busy", me) )
        {
                command("say 我現在沒空！");
                return 1;
        }

        if( query("shen", ob)<0 )
        {
                command("say 你心術不正，我可不敢為你解毒！");
                return 1;
        }
        if( query("score", ob)<500 && query("combat_exp", ob)>100000 )
        {
                command("say 你這點江湖閱歷，也想讓我為你解毒？");
                return 1;
        }

        if( ob->query_condition("chanchu_poison")
            || ob->query_condition("drunk")
            ||ob->query_condition("flower_poison")
            ||ob->query_condition("ice_poison")
            ||ob->query_condition("iceshock")
            || ob->query_condition("rose_poison")
            ||ob->query_condition("scorpion_poison")
            ||ob->query_condition("slumber_drug")
            || ob->query_condition("snake_poison")
        //   ||ob->query_condition("ss_poison")
            ||ob->query_condition("wugong_poison")
        //   || ob->query_condition("xx_poison")
            ||ob->query_condition("xiezi_poison")
            ||ob->query_condition("zhizhu_poison")
            || ob->query_condition("zhua_poison")
            ||ob->query_condition("ice_sting"))
        {
                message_vision("薛慕華輕扣$N脈門，雙眉深鎖，隨後喂$N服下一顆藥丸，盤膝坐下，雙掌貼著$N的背心，開始為$N解毒。\n", ob);
                if( query("combat_exp", ob)>100000 )
                {
                        if( query("family/family_name", ob) != "逍遙派" )
                                addn("score", -300, ob);
                        else addn("score", -200, ob);
                }
                addn("count", -1, me);
                set_temp("busy", 1, me);
                ob->start_busy(5);
                remove_call_out("recover_III");
                call_out("recover_III",5,ob);
                return 1;
        }

        else
        {
                command("?"+query("id", ob));
                command("say 看來我幫不了你什麼忙了！");
                return 1;
        }

}
int recover_III(object ob)
{
        delete_temp("busy", this_object());
        if (ob->query_condition("chanchu_poison"))
                ob->clear_condition("chanchu_poison",0);
        if (ob->query_condition("drunk"))
                ob->clear_condition("drunk",0);
        if (ob->query_condition("flower_poison"))
                ob->clear_condition("flower_poison",0);
        if (ob->query_condition("ice_poison"))
                ob->clear_condition("ice_poison",0);
        if (ob->query_condition("iceshock"))
                ob->clear_condition("iceshock",0);
        if (ob->query_condition("rose_poison"))
                ob->clear_condition("rose_poison",0);
        if (ob->query_condition("scorpion_poison"))
                ob->clear_condition("scorpion_poison",0);
        if (ob->query_condition("slumber_drug"))
                ob->clear_condition("slumber_drug",0);
        if (ob->query_condition("snake_poison"))
                ob->clear_condition("snake_poison",0);
//      if (ob->query_condition("ss_poison"))
//              ob->clear_condition("ss_poison",0);
        if (ob->query_condition("wugong_poison"))
                ob->clear_condition("wugong_poison",0);
//      if (ob->query_condition("xx_poison"))
//              ob->clear_condition("xx_poison",0);
        if (ob->query_condition("xiezi_poison"))
                ob->clear_condition("xiezi_poison",0);
        if (ob->query_condition("zhizhu_poison"))
                ob->clear_condition("zhizhu_poison",0);
        if (ob->query_condition("zhua_poison"))
                ob->clear_condition("zhua_poison",0);
        if (ob->query_condition("ice_sting"))
                ob->clear_condition("ice_sting", 0);
        message_vision("大約一柱香過後，$N吐出一口紫血，薛慕華慢慢地站了起來。\n",ob);
        command("say 你體內毒素已清,可以走啦。");
        return 1;
}
