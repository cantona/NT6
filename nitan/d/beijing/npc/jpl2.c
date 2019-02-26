#include <ansi.h>

inherit NPC;

void create()
{
        set_name("撿破爛的", ({ "jian polan" }));

        set("long", @LONG
這個人不但自己撿破爛，身上也穿得破爛不堪。
LONG
        );

        set("gender", "男性" );
        set("age", 30);

        set("combat_exp", 1000);
        set_skill("unarmed", 20); 
        set_skill("parry", 20); 
        set_skill("dodge", 20); 
               
        set_temp("apply/attack", 5); 
        set_temp("apply/defense", 5); 
        set_temp("apply/damage", 5); 
      
        set("attitude", "friendly"); 


        set("chat_chance", 10);
        set("chat_msg", ({
                (: command, "get all" :),
                "撿破爛的喃喃道：怎麼這些人那麼沒公德心，隨便亂扔東西。\n",
                "撿破爛的嘴裏嘟噥著，不知道説些什麼。\n",
                "撿破爛的伸手捉住了身上的蝨子，一腳踩得扁扁的。 \n",
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: command, "get all" :),
                (: random_move :)
        }) );

        setup();

        add_money("coin", 50);

}

int accept_object(object me, object obj)
{
        command("smile");
        command("say 多謝這位" + RANK_D->query_respect(me) + "！");
        return 1;
}

int accept_fight(object me)
{
        command("say " + RANK_D->query_respect(me) + "饒命！小的這就離開！\n");
        return 0;
}
