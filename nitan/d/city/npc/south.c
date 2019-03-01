// south.c 南家陳圓圓

inherit NPC;

void create()
{
        set_name("陳圓圓", ({ "chenyuanyuan"}));
        set("age", 40);
        set("gender", "女性");
        set("title", "南家");
        set("long","她就是陳圓圓。雖然後世認為丟了大明江山也有她的一點點幹系，但她砌長城的本事卻也不小。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("per", 40);
        set("combat_exp", 10000);
        set("shen_type", 1);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);
        setup();
}

void init()
{
        object ob;
        
        ::init();
        if (interactive(ob = this_player()) ) command( "addin" );
}
