// tangfang.c 唐方

#include <ansi.h>
#include "tangmen.h"

string ask_me();
int carry_qian();

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("唐方", ({ "tang fang", "tang" }));
        set("long", 
"唐方身材嬌小，長的極為清秀，又帶幾分英氣，清勁多於柔弱。\n"
"她是唐門長房宗主唐堯舜之女，唐大之妹，後又得唐老太太親授衣缽，在唐門地位頗高。\n"
"她面容蒼白，神情憔悴，清麗的面龐彷彿還帶着淚痕。\n");                
        set("gender", "女性");
        set("age", 20);
        set("class", "tangmen");
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 20);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 800);
        set("max_jing", 2000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 60);
        set("combat_exp", 900000);
        set("level", 15);
        set("score", 80000);

        set_skill("force", 200);
        set_skill("biyun-xinfa", 200);
        set_skill("dodge", 200);
        set_skill("qiulin-shiye", 200);
        set_skill("hand", 200);
        set_skill("boyun-suowu", 180);
        set_skill("parry", 200);
        set_skill("throwing", 200);
        set_skill("sword", 200);
        set_skill("wuzhan-mei", 200);
        set_skill("tangmen-throwing", 200);
        set_skill("literate", 100);
        set_skill("poison", 200);
        set_skill("medical", 200);
        set_temp("apply/damage", 100);  
        set_temp("apply/unarmed_damage", 100);  
        set_temp("apply/armor", 200);          

        map_skill("force", "biyun-xinfa");
        map_skill("dodge", "qiulin-shiye");
        map_skill("hand", "boyun-suowu");
        map_skill("parry","boyun-suowu");
        map_skill("sword", "wuzhan-mei");
        map_skill("throwing","tangmen-throwing");
        map_skill("poison", "tangmen-poison");
        map_skill("medical", "tangmen-medical");

        prepare_skill("hand", "boyun-suowu");
                
        create_family("唐門世家", 3, "弟子");
        
        set("chat_chance" , 20);
        set("chat_msg", ({
                "我的蕭哥哥到哪兒去，到現在還不來看我！\n",
                "唐方幽幽歎口氣，輕輕按住琴絃，出神得看着遠方的湖面。\n",
                "唐方漫不經心地撥弄了幾下琴絃，自言自語道：也不知道蕭郎現在是生是死....。\n",
                "唐方輕輕吹了一下渺渺升起的檀香，兩行清淚緩緩流下面頰。 \n",                
                ( : command("shy") : ),
                ( : command("sigh") : ),
                ( : command("drop qianqian") : ),
                ( : command("wield all") : ),
                ( : command("drop qianqian") : ),
        }) );
        
        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                ( : command("yun recover") : ),
                ( : command("yun recover") : ),
                ( : carry_qian : ),
                ( : carry_qian : ),
                ( : command("use qian") : ),
                ( : command("use qian") : ),
                ( : command("wield all") : ),
                ( : command("wield all") : ),
        }) );

        set("inquiry", ([
                "千千結" : "問問老太太去啊！\n",
                "千千"   : "問問老太太去啊！\n",
                "蕭郎" : (: ask_me :),
        ]) );                 

        set("master_ob", 2);
        setup();
        carry_object("/d/tangmen/obj/mcloth")->wear();
        carry_object("/d/tangmen/obj/mshoe")->wear();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/qinglianzi")->wield();
        carry_object("/d/tangmen/obj/feidao")->wield();
        set_temp("handing", carry_object("/d/tangmen/obj/jili"));          
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
                                        
        if ((int)ob->query_skill("biyun-xinfa", 1) < 80) {
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
string ask_me()
{
        object me;
        me = this_player();
        
        if( query_temp("marks/蕭", me) )
        {
                return "算了吧，看來你也不知道蕭郎的消息，你走吧。\n";
        }
        command("ah"+query("id", this_player()));
        command("say 你知道蕭郎嗎！？自從他上次大鬧唐門後就失去了消息。\n");
        command("sigh");
        set_temp("marks/蕭", 1, this_player());
        return "老太太為這事非常生氣，再也不許我見他了。\n";
           

}
        
int accept_object(object who, object ob)
{
        object book;
        book = new("/d/tangmen/obj/throwbook");
        if( query("name", ob) == "玉佩" )
        {
                if(!query("yl_trigger")) 
                {
                        say(
"唐方説道：這不是蕭郎的玉佩嗎？太謝謝你了，雖然沒有見到蕭郎，\n"
"能見到他的信物,我已經很欣慰了。\n"
"唐方悠悠地歎了一口氣：這裏有一本暗器總訣，就算是給你的酬謝吧。\n"
"唐方把"+query("name", book)+"交給了"+query("name", who)+"。\n");
                        book->move(who);
                        set("yl_trigger", 1);
                }
                else say("唐方杏目圓睜，説道：你這個人怎麼這樣討厭啊。\n");
                call_out("destroy", 1, ob);
                return 1;
        }
        return 0;
}
void destroy(object ob)
{
        destruct(ob);
        return;
}

int carry_qian()
{
        object ob;

        ob = new("/kungfu/class/tangmen/obj/jie.c");
        ob->move(this_object());
        return 1;
}        
