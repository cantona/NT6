// menwei

inherit NPC;

void create()
{
        set_name("門衛", ({ "men wei", "wei"}));
        set("long", 
        "他是唐門世家的門衛，對保護唐門世家可謂忠貞不二。\n");
        set("gender", "男性");
        set("age", 35);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 18);
        set("int", 25);
        set("con", 24);
        set("dex", 28);

        set("combat_exp", 700000);

        set_skill("force", 300);
        set_skill("dodge", 300);
        set_skill("parry", 300);
        set_skill("sword", 500);
        set_skill("blade", 300);    
        set_skill("strike", 300);
        create_family("唐門世家", 10, "家丁");

        setup();
        carry_object("/clone/misc/cloth")->wear();
}