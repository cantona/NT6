// Feb. 6, 1999 by Winder
inherit NPC;
void create()
{
        set_name("農夫", ({ "nong fu","nong","fu"}) );
        set("gender", "男性" );
        set("age", 24+random(10));
        set("long", "這是一個山間農夫，十分粗俗。\n");
        set("shen_type", 1);
        set("combat_exp", 4000);
        set("str", 18);
        set("dex", 18);
        set("con", 18);
        set("int", 19);
        set("attitude", "friendly");
        set("chat_msg", ({
        "農夫呸了一口，說道：溫家沒個好東西！活該女兒被糟蹋。\n",
        "農夫咬牙切齒地說道：溫家橫行霸道，不會有好報！\n"
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}