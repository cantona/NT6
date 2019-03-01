//tangjue.c

#include <ansi.h>;
#include "tangmen.h"

inherit NPC;
inherit F_MASTER;

int carry_obj();


void create()
{
        set_name("唐絕", ({ "tang jue","tang"}));
        set("nickname", HIR "絕大少" NOR);
        set("long", 
"唐門三絕之一，唐絕最絕，絕得連唐門中人都不知道他的絕法，所有的絕門暗器，他都會用。\n");
        set("gender", "男性");
        set("age", 32);
        set("class", "tangmen");
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 28);
        set("int", 26);
        set("con", 26);
        set("dex", 27);
        set("max_qi", 8000);
        set("max_jingli", 2500);
        set("max_douzhi", 600);
        set("douzhi", 600);
        set("neili", 4500);
        set("max_neili", 4500);
        set("yanli", 200);
        set("jiali", 120);
        set("combat_exp", 900000);
        set("level", 15);
        set("score", 8000);

        set_skill("force", 280);
        set_skill("throwing", 280);
        set_skill("dodge", 280);
        set_skill("parry", 280);
        set_skill("literate", 280);
        set_skill("hand", 280);
        set_skill("sword", 280);
        set_skill("boyun-suowu", 280);
        set_skill("biyun-xinfa", 280);
        set_skill("qiulin-shiye", 280);
        set_skill("wuzhan-mei", 280);
        set_skill("medical", 280);
        set_skill("poison", 280);
        set_skill("tangmen-throwing", 280);
        set_skill("tangmen-poison", 280);
        set_skill("tangmen-medical", 280);        
        
        map_skill("force", "biyun-xinfa");
        map_skill("throwing", "tangmen-throwing");
        map_skill("dodge", "qiulin-shiye");
        map_skill("parry", "boyun-suowu");
        map_skill("sword", "wuzhan-mei");        
        map_skill("hand", "boyun-suowu");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");
        
        prepare_skill("hand", "boyun-suowu");
        
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);  
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                ( : command("yun recover") : ),
                ( : command("yun recover") : ),
                ( : command("use qian") : ),
                ( : command("use hua") : ),
                ( : command("wield all") : ),
                ( : command("wield all") : ),
                ( : carry_obj : ),
                ( : carry_obj : ),
                
        }) );
        
        set("chat_chance" , 8 );
        set("chat_msg" , ({
                "唐門之大，但不容不肖子弟！\n",
                "學武之道在于勤奮！\n",
                "唐門的弟子要記好啊！\n",
        }) );
         
                
                
        create_family("唐門世家", 2, "嫡系高手");

        set("master_ob", 3);
        setup();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));  
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
}

int carry_obj()
{
        object me,ob;
        
        me = this_object();
        
        switch(2)
        {
        case 0:
                ob = new("/kungfu/class/tangmen/obj/hua");
                break;
        case 1:
                ob = new("/d/tangmen/obj/qianqian");
                break;
        }
         
        ob->move(me);
        return 1;
}         

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))  
                return;
                        
        if( query("shen", ob)<10000 )
         {
                command("say 我收徒最注重德行！");
                command("say 在德行方面，" + RANK_D->query_respect(ob) +
                        "是否還做得不夠？");
                return;
        }

        if ((int)ob->query_skill("biyun-xinfa", 1) < 120) {
                command("say 唐門雖然以暗器為主，但還是要輔以內力。"); 
                command("say " + RANK_D->query_respect(ob) + 
                        "是否還應該在碧雲心法上多下點功夫？");
                return;
        }
        if( query("int", ob)<28){
                command("say 唐門歷來注重弟子的文學修為。");
                command("say 本派功夫要能熟練運用，必須能體會其中所含深遠意境，悟性差了是不行的。");
                command("say " + RANK_D->query_respect(ob) + "的悟性還大有潛力可挖，還是請回吧。");
                return;
        }
        command("say 哈哈哈，我就收下你，記住以後要在江湖行俠仗義喔！");
        command("recruit "+query("id", ob));
}
