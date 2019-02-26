//Npc : kongxiaotian.c 孔小天

inherit NPC;
#include "kid.h"

void create()
{
        set_name("孔小天",({ "kong xiaotian", "xiao hai", "kid"}) );
        set("title", "學童");
        set("gender", "男性" );
        set("age", 13);
        set("long", "這是個一個資政書院的學童，正在和同伴玩耍。\n");
        set("combat_exp", 3);
    set("positive_score", 10);
        set("str", 12);
        set("con", 18);
        set("dex", 20);
        set("per", 24);
        set("chat_chance", 3);
        set("chat_msg", ({
                "孔小天道：我們老大居然喜歡上了顧月兒了，真是奇怪了！\n",
        "孔小天道：想不想我告訴你一個祕密呢？\n",
        "孔小天道：我們的老師也挺可憐的，唉～～～～！\n"
    }));
    set("inquiry", ([
        "祕密" : (: ask_secret :),
        "secret" : "我不懂洋文的。\n",
    ]));
    set("papa_name", "孔萬擎" );
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/xiaogua")->wear();
}