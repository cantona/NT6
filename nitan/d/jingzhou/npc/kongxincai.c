//Edited by fandog, 02/15/2000

inherit NPC;

void create()
{
        set_name("空心菜",({ "kongxin cai", "kid" }) );
        set("gender", "女性" );
        set("age", 5);
        set("long", 
"一個天真可愛的小女孩，她是萬家公子萬圭的女兒。\n");
        set("combat_exp", 20);
        set("shen_type", 1);
        set("str", 14);
        set("per", 28);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("attitude", "friendly");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}
