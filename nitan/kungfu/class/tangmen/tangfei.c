#include <ansi.h>
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

string ask_tanghua();

void create()
{
        set_name("唐肥", ({ "tang fei","tang"}));
        set("nickname", HIC "我也不知道" NOR);
        set("long", "唐門三絕之一，名列唐門一流高手之中，其使有的暗器“唐花”是唐門絕門暗器之一。\n");
        set("gender", "女性");
        set("age", 28);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 26);
        set("int", 26);
        set("con", 24);
        set("dex", 23);
        set("max_qi", 7000);
        set("max_jingli", 1400);
        set("max_douzhi", 450);
        set("douzhi", 450);
        set("neili", 3500);
        set("max_neili", 3500);
        set("yanli", 200);
        set("jiali", 100);
        set("combat_exp", 750000);
        set("score", 7000);
        set("level", 10);

        set_skill("force", 150);
        set_skill("throwing", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("literate", 150);
        set_skill("hand", 150);
        set_skill("sword", 150);
        set_skill("boyun-suowu", 150);
        set_skill("biyun-xinfa", 150);
        set_skill("qiulin-shiye", 150);
        set_skill("wuzhan-mei", 150);
        set_skill("poison", 150);
        set_skill("medical", 150);
        set_skill("tangmen-throwing", 150);
        set_skill("tangmen-poison", 150);
        set_skill("tangmen-medical", 150);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");

        set("chat_chance_combat",  20);
        set("chat_msg_combat",  ({
                (: exert_function, "recover" :),  
                (: perform_action, "throwing.san" :),   
                ( : command("use hua") : ),
                ( : command("use hua") : ),
        }) );   
        
        set("inquiry", ([
                "唐花"    : ( : ask_tanghua : ),
                "tanghua" : ( : ask_tanghua : ),
        ]) );           
        
        create_family("唐門世家", 3, "弟子");
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  
        
        set("master_ob", 2);
        setup();
        carry_object("/d/tangmen/obj/mcloth")->wear();
        carry_object("/d/tangmen/obj/mshoe")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/qinglianzi"));  
        carry_object("/d/tangmen/obj/qinglianzi");
        carry_object("/kungfu/class/tangmen/obj/hua")->wield();
        
}

string ask_tanghua()
{
        object me,ob,her;
        
        me = this_player();
        her = this_object();
                
        if( !query_temp("thua2", me) )
        { 
                command("laugh"+query("id", me));
                addn_temp("thua2", 1, me);
                return HIC "你以為我有啊！我還要找人要呢！\n" NOR;      
        }
        
        if( query("family/family_name", me) != "唐門世家" )
        {
                command("hmm"+query("id", me));
                her->kill_ob(me);
                return HIR"又是一個不要命的,哈哈......\n"NOR;
        }
        
        command("addoil"+query("id", me));
        command("pat "+ me->qurey("id") );
        command("say “好吧，這就是唐花，給你了。” \n");
        ob = new("/kungfu/class/tangmen/obj/hua.c");
        ob->move(me);
//           message("channel:rumor", HIM "【謠言四起】" HIM " 哇..." + me->query("name") + HIM "找到了唐門暗器" ;118                                  HIG "唐花" HIM "了！\n" NOR, users());
        return "好吧！\n";
}        
               
void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;

        if( query("family/family_name", ob) != "唐門世家" )
        {
                command("say “我四川唐門乃是武林世家，你已是武林中人，我不能收你為徒！”\n");
                return;
        }
                                        
        if ((int)ob->query_skill("biyun-xinfa", 1) < 100) {
                command("say 唐門雖然以暗器為主，但還是要輔以內力。"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否還應該在碧雲心法上多下點功夫？");
                return;
        }

        if ( ob->query_skill("biyun-xinfa", 1) < 80 && ob->query_skill("tangmen-throwing", 1) < 80 )
        {
                command("say “你的心法和暗器不太熟練，要加油啊！”\n");
                return;
        }                                   
        if( query("int", ob)<28){
                command("say 唐門歷來注重弟子的文學修為。");
                command("say 本派功夫要能熟練運用，必須能體會其中所含深遠意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性還大有潛力可挖，還是請回吧。");
                return;
        }
        command("say 好吧，我就收下你吧...");
        command("recruit "+query("id", ob));
}
