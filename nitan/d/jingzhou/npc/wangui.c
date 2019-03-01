//Edited by fandog, 02/13/2000

inherit NPC;

void create ()
{
        set_name("萬圭", ({"wan gui","wan"}));
        set("long", "他是萬震山的獨子，他長身玉立，臉型微見瘦削，俊美瀟洒，倒象是個富家公子。\n");
        set("title","萬門三弟子");
        set("gender", "男性");
        set("age", 25);
        set("combat_exp", 100000);
        set("str", 20);
        set("int", 25);
        set("con", 20);
        set("dex", 28);
        set("per", 20);
        set("kar", 20);
        set_skill("force", 80);
        set_skill("dodge", 80);
        set_skill("sword", 80);
        set_skill("parry", 80);
        set_skill("yanfly", 80);
        set_skill("tangshi-jian", 80);
        map_skill("dodge", "yanfly");
        map_skill("parry", "tangshi-jian");
        map_skill("sword", "tangshi-jian");
        setup();

        carry_object("/clone/cloth/male-cloth")->wear();
        carry_object("/d/city/obj/changjian")->wield();
}  

