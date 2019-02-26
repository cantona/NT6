// This program is a part of NT MudLIB

#include <ansi.h>

inherit NPC;

string ask_me(object who);

void create()
{
        set_name("落魄公子", ({ "gong zi", "gong" }) );
        set("gender", "男性" );
        set("shen_type", -1);
        set("age", 25);
        set("str", 25);
        set("cor", 25);
        set("cps", 25);
        set("int", 25);
        set("long",
        "這是個眉清目秀的青年公子，但精神頹廢，一身酒氣熏人，想必是在酒色場中淘空了身子。\n" );

        set("combat_exp", 20000);
        set("attitude", "heroism");
        set("chat_chance", 15);
        set("chat_msg", ({
                "公子説道: 哈哈，終於得到"HIR"鬼三"NOR"的傳家寶了，! \n",
                (: random_move :)
        }) );

        set("chat_chance_combat", 15);
        set("chat_msg_combat", ({
                "公子説道: 你當真吃了豹子膽啦 ? 你知道我是誰 ! \n",
                "公子忽然發出一劍，招數精奇，但劍到中途卻又急忙收招。\n",
                "公子説道: 快離開我 ! 我不能打架了 !....\n"
        }) );

        set("inquiry", ([
                "鬼三"   : (: ask_me :),
        ]) );

        set_skill("sword", 50);
        set_skill("dodge", 40);
        set_skill("unarmed", 50);
        set_skill("parry", 50);

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("clone/cloth/cloth")->wear();
}

string ask_me(object who)
{
        int i;
        object *ob;

        if (query("revealed"))
        {
                if (is_killing(who))
                        return "你既然知道了我的祕密，今日休想活命！\n";
                else
                {
                        kill_ob(who);
                        who->fight_ob(this_object());
                        return "知道我祕密的人都得死，納命來吧！\n";
                }
        }

        if ((random(10) < 5) || is_fighting())
                return "這個......\n";

        set_temp("apply/attack",  50);
        set_temp("apply/defense", 50);
        set_temp("apply/damage",  20);


        message("vision",
                HIY "落魄公子眼中突然放出獸性的光芒，怒聲説道，好小了,既然你是鬼三派來的,就去死吧？！\n"NOR,
                environment(), this_object());

        set("title", HIB"鬼手"NOR);
        set_name("李四",({ "li si", "li" }));
        carry_object("/clone/misc/xiao")->wear();
        set("pursuer", 1);
        set("vendetta/authority", 1);
        set("chat_msg_combat", ({
                (: random_move :)
        }) );
        set("chat_chance", 15);
        set("chat_msg", ({
                (: random_move :)
        }) );
        set("bellicosity", 100);
        set("combat_exp", 1000);
        set("max_qi",100);
        set("max_neili",120);
        set("max_jingli",120);
        set_skill("force", 20);
        set_skill("dodge", 20);
        set_skill("tiyunzong", 20);
        set_skill("parry", 10);
        set_skill("sword", 12);
        set_skill("taiji-jian", 20);
        set_skill("taoism", 30);
        set_skill("literate", 40);
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");

        ob = all_inventory(environment());
        for(i=sizeof(ob)-1; i>=0; i--) {
                if( !playerp(ob[i]) ) continue;
                if( query("combat_exp", ob[i])<5000 )
                        continue;
                kill_ob(ob[i]);
                ob[i]->fight(this_object());
        }
        add_money("silver", 20);
        set("revealed", 1);
        return "哈哈,既然知道了我的祕密你就得死！\n";
}
