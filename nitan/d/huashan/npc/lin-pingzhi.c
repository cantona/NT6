// lin-pingzhi.c

inherit NPC;
#include <ansi.h>;
void create()
{
        set_name("林平之", ({ "lin pingzhi","lin","pingzhi"}));
        set("gender", "男性");
        set("age", 18);
        set("long", "林平之是嶽不羣最小的一個弟子，"
                    "也是他的東牀快婿。\n");
        set("attitude", "peaceful");

        set("str", 26);
        set("con", 30);
        set("int", 24);
        set("dex", 35);

        set("max_qi", 1500);
        set("max_jing", 1500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 100);

        set("combat_exp", 3000);
        set("shen_type", -1);
        set("score", 120000);

        set("chat_chance_combat", 80);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :)
        }) );

        set_skill("unarmed", 60);
        set_skill("sword", 50);
        set_skill("force", 60);
        set_skill("parry", 50);
        set_skill("dodge", 60);
        set_skill("literate", 70);

        set_skill("huashan-sword", 80);
        set_skill("pixie-jian", 50);
        set_skill("huashan-neigong", 60);
        set_skill("huashan-quan", 60);
        set_skill("feiyan-huixiang", 60);

        map_skill("sword", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("force", "huashan-neigong");
        map_skill("unarmed", "huashan-quan");
        map_skill("dodge", "feiyan-huixiang");

        create_family("華山派", 14, "弟子");
        setup();

        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

/*
void die()
{
        object killer;
        object book;

        if( objectp(killer = query_last_damage_from()) &&
            userp(killer) )
        {
                     message_vision("$N得到一本辟邪劍譜。\n",killer);
                    book=new("/clone/book/pixie_book");
                     book->move(killer);
               }
        ::die();
}
*/
