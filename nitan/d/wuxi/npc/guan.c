// guan.c 武將

inherit NPC;

void create()
{
        set_name("蔡進義", ({ "cai jinyi", "cai", "jinyi" }));
        set("gender", "男性");
        set("age", random(10) + 30);
        set("str", 25);
        set("dex", 16);
        set("long", "
他滿臉是笑，正在聲嘶力極地向周圍的人遊説當兵的種種好處，並不時地扯
動自己嶄新的軍服、拍拍微微腆起的肚皮，要想參軍的話就去找他吧！\n");
        set("combat_exp", 75000);
        set("shen_type", 1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("sword", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 50);
        set_temp("apply/defense", 50);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 30);

        set("neili", 400);
        set("max_neili", 400);
        set("jiali", 10);

        setup();
        carry_object("/clone/weapon/gangjian")->wield();
        carry_object("/d/city/npc/obj/tiejia")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        tell_object(ob,"蔡進義左右看了看，説道：這位"+RANK_D->query_respect(ob)+"，要想當兵就趕快報名，我給你留個名額。\n");

        return;
}