// wraith.c

inherit NPC;

int is_ghost() { return 1; }

void create()
{
        set_name("翁四", ({ "wengsi" }) );
        set("long",
"一個披頭散髮，渾身是血的厲鬼，正在這裏飄來飄去。\n" );
        set("max_jing", 4000);
        set("max_qi", 4000);                    
        set("max_sen", 4000);
        set("max_neili",4000);
        set("neili",8000);
        set("jiali",150);
        set("bellicosity",50000);
        set("cor",30);
        set("combat_exp",4000000+random(2400000));

        set_skill("pixie-jian", 500);
        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("sword",500);
        set_skill("force",800); //防止別人來彈指
        set_skill("hamagong",500);
        set_skill("tiyunzong",500);
        map_skill("sword","pixie-jian");
        map_skill("parry","pixie-jian");
        map_skill("dodge","tiyunzong");
        map_skill("force","hamagong");
        set_temp("apply/attack",50);

        set("chat_chance_combat",5);
        set("chat_msg_combat", ({
                "還..我..命..來...\n",
        }) );

        set("shen_type",-1);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
}
void init()
{
        object ob;
        ::init();
        if (interactive(ob = this_player())) {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, ob);
        }
}
