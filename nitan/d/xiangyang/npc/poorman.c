// poorman.c

inherit NPC;

void create()
{
        set_name("窮漢", ({ "poor man", "man" }) );
        set("gender", "男性" );
        set("age", 33);
        set("long", "一個骨瘦如柴，滿臉菜色的窮漢。\n");
        set("attitude", "friendly");
        set("combat_exp", 250);
//        set("shen", 50);
        set("shen_type", 1);
        set("str", 20);
        set("dex", 18);
        set("con", 17);
        set("int", 13);
        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
"窮漢懶洋洋地打了個哈欠。\n",
"窮漢嘆了口氣：那些蒙古韃子害得我家破人亡。\n",
                (: random_move :)
        }) );
        carry_object("/clone/misc/cloth")->wear();
}
