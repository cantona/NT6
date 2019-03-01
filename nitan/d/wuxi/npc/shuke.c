// shuke.c

inherit NPC;

void create()
{
        set_name("書客",({ "shuke" }) );
        set("gender", "男性" );
        set("age", 26);
        set("long", 
"這是個聽書的書客，一副專注的神情，對進出的人等視而不見。\n");
        set("combat_exp", 5000);
        set("shen_type", 1);
        set("str", 20);
        set("per", 20);
        set("dex", 20);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/cloth/male-cloth")->wear();
}
