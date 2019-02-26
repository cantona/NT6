// qiuxingxing.c

inherit NPC;
#include "kid.h"
void create()
{
        set_name("仇星星",({ "qiu xingxing", "xiao hai","kid"}) );
        set("title", "學童");
        set("gender", "男性" );
        set("age", 11);
        set("long", "這是個一個資政書院的學童，正在和同伴玩耍。\n");
        set("combat_exp", 3);
    set("positive_score", 10);
        set("shen_type", 1);
        set("str", 10);
        set("cor", 16);
        set("cps", 20);
        set("per", 23);
        set("chat_chance", 3);
        set("chat_msg", ({
        "仇星星道：我們老大喜歡上了顧月兒了，唉～～～～～！\n",
        "仇星星道：想不想我告訴你一個祕密呢？\n",
        "仇星星道：我們的老師是個笨蛋！！！！\n"
    }));
    set("inquiry", ([
        "祕密" : (: ask_secret :),
        "secret" : "我不懂洋文的。\n",
    ]));
    set("papa_name", "仇好石" );
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/xiaogua")->wear();

}