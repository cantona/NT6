// west.c 西家紅娘子
inherit NPC;

void create()
{
        set_name("紅娘子", ({ "hongniangzi"}));
        set("age", 30);
        set("gender", "女性");
        set("title", "西家");
        set("long","她就是紅娘子，雖然他老公被人切了頭，成了李闖王自毀的長城，她在這裡堆起長城也是毫不含糊。\n");
        set("attitude", "peaceful");
        set("str", 24);
        set("dex", 16);
        set("per", 35);
        set("combat_exp", 100000);
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
