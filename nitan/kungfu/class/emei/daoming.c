// daoming.c 道明

inherit NPC;

void create()
{
        set_name("道明小師父", ({ "daoming","xiaoshifu",}));
        set("long", "他是峨嵋報國寺樓的小和尚。\n");
        set("gender", "男性");
        set("age", 16);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("class", "bonze");

        set("str", 20);
        set("int", 20);
        set("con", 22);
        set("dex", 25);

        set("max_qi", 150);
        set("max_jing", 100);
        set("neili", 150);
        set("max_neili", 150);

        set("combat_exp", 2000);

        set_skill("force", 30);
        set_skill("dodge", 20);
        set_skill("unarmed", 20);
        set_skill("parry", 20);
        set_temp("apply/attack", 15);
        set_temp("apply/defense", 15);
        set_temp("apply/damage", 5);

        create_family("峨嵋派", 5, "弟子");

        setup();

        carry_object("/clone/cloth/dao-cloth.c")->wear();
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
     say( "道明小師父輕聲說道：歡迎來保國寺藏經樓。您要讀經書嗎？\n");
}
