// xiao qiushui.c 蕭秋水

#include <ansi.h>

inherit NPC;

string ask_me();
void create()
{
        set_name("蕭秋水", ({ "xiao qiushui", "xiao" }));
        set("nickname", HIY "大俠" NOR);
        set("long", 
                "原來他就是與唐方痴心相戀，為了唐方大鬧唐門的蕭秋水。\n"
                "他在江湖上行俠仗義，俠名遠播，人稱“大俠”。\n"
                "他大約二十有餘，雖然受盡折磨，仍然帶着一身傲氣。\n");
        set("gender", "男性");
        set("age", 20);
set("attitude", "peaceful");        
        set("shen_type", 1);
        set("str", 28);
        set("int", 30);
        set("con", 30);
        set("dex", 32);
        
set("max_qi", 300000);        
set("max_jing", 150000);        
set("neili", 5000000);        
        set("max_neili", 3000);
set("jiali", 5000);        
set("combat_exp", 500000000);        
        set("score", 700000);

set_skill("force", 2000);        
set_skill("biyun-xinfa",1200);        
set_skill("dodge", 1800);        
set_skill("qiulin-shiye", 1200);        
set_skill("unarmed", 1200);        
set_skill("biye-wu", 1300);        
set_skill("parry", 1200);        
set_skill("sword", 1400);        
set_skill("wuzhan-mei", 1300);        
set_skill("literate", 2580);            

        map_skill("force", "biyun-xinfa");
        map_skill("dodge", "qiulin-shiye");
map_skill("unarmed", "biye-wu");        
        map_skill("parry", "wuzhan-mei");
        map_skill("sword", "wuzhan-mei");
        create_family("唐門", 7, "弟子");
        set("class", "tangmen");
        
        
set("chat_chance_combat", 200);        
        set("chat_msg_combat", ({
(: perform_action, "sword.yumei" :),        
                (: perform_action, "sword.wumei" :),
(: perform_action, "unarmed.huimeng" :),        
                (: exert_function, "recover" :),
        }) );
        set("inquiry", 
                ([
                        "唐方" : (: ask_me :)
                ]));
        set("yu_count", 1);

        setup();
carry_object("/clone/weapon/changjian")->wield();        
    carry_object("/clone/cloth/cloth")->wear();
}
string ask_me()
{object ob;
 object me;
 me=this_player();
        if (query("yu_count") < 1){return "是唐方叫你來見我的？可惜我的玉佩已經交給別人了。\n";}
        command("touch"+query("id", this_player()));
        command("say 是唐方叫你來見我的？\n");
        command("sigh" );
        command("say 自從當日大鬧唐門之後，我就和唐方生死相隔了。\n");
        ob=new("/d/tangmen/obj/yupei");
        ob->move(this_player());
        message_vision("$N交給$n一塊玉佩。\n", me, ob);
        addn("yu_count", -1);
        return"你把這塊玉佩交給唐方吧。\n";
        

                                                        

}