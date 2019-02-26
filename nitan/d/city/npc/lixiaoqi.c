//Npc : lixiaoqi.c 李小琪

inherit NPC;
#include "kid.h"

void create()
{
        set_name("李小琪",({ "li xiaoqi", "xiao hai", "kid"}) );
        set("title", "學童");
        set("gender", "男性" );
        set("age", 12);
        set("long", "這是個一個資政書院的學童，正在和同伴玩耍。\n");
        set("combat_exp", 4);
     set("positive_score", 10);
        set("str", 11);
        set("con", 18);
        set("chat_chance", 3);
        set("chat_msg", ({
                "李小琪道：我們老大居然喜歡上了顧月兒了，真是奇怪了！\n",
        "李小琪道：想不想我告訴你一個祕密呢？\n",
        "李小琪道：我們的老師是個笨蛋！！！！\n"
    }));
    set("inquiry", ([
        "祕密" : (: ask_secret :),
        "secret" : "我不懂洋文的。\n",
    ]));
    set("papa_name", "李千葉" );
        set("cps", 20);
        set("per", 24);
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/xiaogua")->wear();
}