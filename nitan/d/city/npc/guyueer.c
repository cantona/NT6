//Npc : guyueer.c 顧月兒

inherit NPC;

void create()
{
        set_name("顧月兒",({ "gu yueer", "xiao hai", "kid"}) );
        set("title", "學童");
        set("gender", "女性" );
        set("age", 10);
        set("long", "這是個一個資政書院的學童，正在和同伴玩耍。\n");
        set("combat_exp", 1);
        set("positive_score",10);
        set("str", 9);
        set("cor", 18);
        set("cps", 20);
        set("per", 26);
        set("chat_chance", 3);
        set("chat_msg", ({
        "顧月兒道：那個姓楊的最惡心了，老色迷迷額看著我，自以為很酷。\n",
        "顧月兒道：真不想再上學了，可是爹爹老逼我來。\n",
        "顧月兒道：我們的老師真可憐的，唉～～～～！\n"
    }));
    set("inquiry", ([
        "秘密" : "我能有什麼秘密呢？\n",
        "secret" : "我不懂洋文的。\n",
    ]));
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/huaao")->wear();
}