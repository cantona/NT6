//baobiao.c

inherit NPC;

void create()
{
        set_name("羣玉樓保鏢", ({ "bao biao","baobiao" }));
        set("gender", "男性");
        set("age", random(10) + 20);
        set("str", 25);
        set("con", 25);
        set("spi", 25);
        set("dex", 25);
        set("int", 25);
        set("shen_type", -1);
        set("long", "他殺氣騰騰，負責羣玉樓所有女人的安全。\n");
        set("combat_exp", 100000);
        set("class", "fighter");
        set("attitude", "herosim");
        set_skill("unarmed", 70);
        set_skill("force", 70);
        set_skill("sword", 70);
        set_skill("dodge", 70);
        set_skill("parry", 70);
        set("max_qi", 700);
        set("max_jing", 700);
        set("max_neili", 600);
        set("neili",600);
        set("jiali", 40);
        set("max_jingli", 600);
        set("jingli", 600);

        setup();
        carry_object("/d/changan/npc/obj/sword")->wield();
        carry_object("/d/changan/npc/obj/zhanjia")->wear();
}

int accept_fight(object me)
{
        message_vision("羣玉樓保鏢對$N喝道：是不是想死啊！\n\n", me);
        return 0;
}

int heal_up()
{
        if (environment() && !is_fighting()) 
        {
                call_out("leave", 1);
                return 1;
        }
        return ::heal_up() + 1;
}

void leave()
{
        object stone;
        addn("time", 1, this_object());
        if( query("time", this_object()) >= 3 )
        {
                message("vision", name() + "嘿嘿一笑:“老子要回去"
                        "睡覺了，再有人來羣玉樓鬧事就叫我！”\n",
                        environment());
                destruct(this_object());
        }
        return;
}