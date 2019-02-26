#include <ansi.h>
inherit NPC;

void create()
{
        set_name("江洋大盜",({ "jiangyang dadao","dadao" }) );
        set("title",HIB"專殺官府"NOR);
        set("gender", "男性" );
        set("long","這是一夥土匪大盜，專門與官府作對，實在不好惹。\n");  

        set("int", 30);
        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("age", 10+random(30));
        set("per", 14+random(20));
        
        set("scale", 150);
        set_temp("apply/armor", 30);
        set_temp("apply/damage", 20);
        set_temp("born_time", time());

        setup();
        carry_object( __DIR__ "obj/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", random(200));
}

void set_from_me(object me)
{
        int exp;
        int level;
        
        exp=query("combat_exp", me)/(random(5)+5);
        level = to_int(pow(to_float(exp / 100), 1.0 / 3)) * 10;

        set_skill("taiji-quan",level);
        set_skill("dodge", level);
        set_skill("parry", level);
        set_skill("sword", level);
        set_skill("unarmed", level);
        set_skill("taiji-jian", level);
        set_skill("force", level);
        set_skill("taiji-shengong", level);
        set_skill("tiyunzong", level);

        map_skill("sword", "taiji-jian");
        map_skill("force", "taiji-shengong");
        map_skill("parry", "taiji-quan");
        map_skill("unarmed", "taiji-quan");
        map_skill("dodge", "tiyunzong");

        set("combat_exp", exp);
        set("max_qi",query("max_qi", me)*2/5);
        set("qi",query("max_qi"));
        set("max_jing",query("max_jing", me)/2);
        set("jing",query("max_jing"));
        set("max_neili",query("max_neili", me)/2);
        set("neili",query("max_neili"));
        set("max_jingli",query("max_neili"));    
        set("jingli",query("max_neili"));    
        set("jiali",20);  
        set("killer",query("id", me));
        
        if( count_gt(exp, 3000000) )
        {
                set("chat_chance_combat", 30);
                set("chat_msg_combat", ({
                        (: perform_action, "unarmed.zhen" :),
                        (: perform_action, "sword.lian" :),
                }) );
        }
        if( count_gt(exp, 6000000) )
                set("family/family_name","武當派");
}

void init()
{
        remove_call_out("check_me");
        call_out("check_me", 1);  
}

int check_me()
{
        object me = this_object(), ob;

        remove_call_out("check_me");
        if( !query("killer", me )
                 || !present(query("killer", me),environment(me)) )
        {
                remove_call_out("check_me");
                call_out("escape_me",1,me);
        } else
        {
                ob=present(query("killer", me),environment(me));
                if(!ob->is_fighting(me))
                        kill_ob(ob);
                remove_call_out("check_me");
                call_out("check_me",3);

                return 1;
        }
}

varargs void die(object killer)
{
        object ob=this_object();

        message_vision(HIR"江陽大盜大呼一聲：點子硬，快撤！轉眼間一夥人馬消失得"
                 +"無影無蹤！\n"NOR,ob);    
        remove_call_out("check_me"); 
        if( !killer ) killer = query_last_damage_from(); 
        if( killer )
                GIFT_D->delay_war_bonus(killer, ([ "prompt" : "因殺死大盜", "exp" : 50, "pot" : 20, "mar" : 5, "gold" : 1 ])); 
        destruct(ob);
        return;
}

void escape_me(object me)
{
        destruct(me);
        return;
}     


