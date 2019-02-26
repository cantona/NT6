// dizi.c
inherit NPC;

void create()
{
        mapping name = NAMES_D->random_name(0, 0, "唐", 0, 0);

        if (! name)
                name = ([ "name": "唐風",  "id": ({ "tang feng", "tang", "feng" }) ]);
                
        set_name(name["name"], name["id"]);
        set("gender", "男性");
        set("long",
                "唐門世家弟子，着一身灰色的勁裝\n"
        );
        set("combat_exp", random(50000));
        set("class", "tangmen");
        set("neili", random(500));
        set("max_neili", random(500));

        set("title", "唐門世家弟子");
        set_skill("force", 10+random(80));
        set_skill("dodge", 10+random(80));
        set_skill("throwing", 10+random(80));
        set_skill("parry", 10+random(80));
        setup();

        add_money("silver", 5);
        carry_object("clone/misc/cloth")->wear();
}

int accept_fight(object me)
{
        if( query("family/family_name", me) == "唐門世家"){
                command("nod");
                command("say 進招吧。");
                return 1;
        }
        command("say 唐門世家弟子不和別派的人過招。");
        return 0;
}
