// Summer 9/26/1996.

inherit NPC;

void create()
{
        set_name("值日喇嘛", ({ "zhiri lama", "lama" }));
        set("long", 
"這是度母殿的值日喇嘛，專門負責各種敬奉事物。\n");
        set("gender", "男性");
        set("age", 20);
        set("attitude", "peaceful");
        set("class","lama");
        set("shen_type", 0);
        set("str", 22);
        set("int", 20);
        set("con", 22);
        set("dex", 21);
        
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 10);
        set("combat_exp", 1000);

        set_skill("force", 20);
        set_skill("dodge", 25);
        set_skill("parry", 20);
        set_skill("strike", 20);


        setup();
        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}
int accept_object(object me, object ob)
{
        object butter, gang;

        if ( userp(ob) || ob->is_character() )
        {
              command("slap"+query("id", me));
                 return notify_fail("你太黑心了吧，想謀殺啊？\n"); 
        }
        if (ob->name()!="酥油罐") {
        write("值日喇嘛臉上露出迷惑的表情。\n");
        command ("shake");
        // remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
        if ( objectp(butter = present("su you", ob)) && objectp(gang = present("tong gang", environment(this_object()))) ) {
                butter->move_liquid(gang);
        message_vision("$N將酥油小心翼翼的倒入遍照雪海內。\n", this_object());
        }
        if( query("class", me) == "bonze"){
        if (me->query_skill("lamaism", 1) < 30){
        set("lama_butter",query("mud_age",  me), me);
        command ("bow");
        command ("say 佛主保佑施主！");
        // remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
        if (me->query_skill("lamaism", 1) >= 30
        && me->query_skill("lamaism", 1) < 60){
        set("lama_butter",query("mud_age",  me)+7600, me);
        command ("bow");
        command ("say 佛主保佑施主！");
        // remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
        }
    }
        command ("say 佛主保佑施主！");
        // remove_call_out("destroy_it");
        call_out("destroy_it", 1, ob);
        return 1;
}
void destroy_it(object ob)
{
      if (!ob)
        return;
        destruct(ob);
        return ;
}



