// monk.c

inherit NPC;
void create()
{
        set_name("空光", ({ "shaolin monk", "monk"}) );
        set("gender", "男性" );
        set("age",random(10)+ 32);
        set("long", "這是少林寺出外化齋的和尚。\n");
        set("combat_exp", random(10000)+10000);
        set("attitude", "friendly");
        set("chat_chance", 20);
        set("chat_msg", ({
                "空光唱了個肥諾道：“施主捐點香火錢吧！”\n",
        }) );
        set_skill("unarmed", 5+random(40));
        set_skill("dodge",40);
        set_skill("force",20);
        set("force",100);
        set("max_neili",100);
        create_family("少林寺", 41, "弟子");
        setup();
        carry_object(CLOTH_DIR"sengpao")->wear();
        carry_object(__DIR__"obj/bowl");
}

int accept_object(object me, object obj)
{
        command("sigh");
        command("say 日子難過呀！\n");
        command("say 寺內的藏經樓總是丟書，方丈現在動不動就責罰弟子面壁十年！\n");
        command("thank"+query("id", me));
        return 1;
}