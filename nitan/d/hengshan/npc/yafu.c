// Last Modified by Sir on May. 22 2001
// yafu.c

inherit NPC;

void create()
{
        set_name("啞婦",({ "yafu" }) );
        set("gender", "女性" );
        set("age", 37);
        set("long", "這是個終年不開口的啞婦\n");
        set("combat_exp", 50000);
        set("shen_type", 0);
        set("str", 21);
        set("per", 20);
        set("dex", 21);
        set("con", 21);
        set("int", 21);
        set("attitude", "friendly");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}