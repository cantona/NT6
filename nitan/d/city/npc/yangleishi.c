// yangleishi.c

inherit NPC;

#include "kid.h"

void create()
{
        set_name("楊磊石",({ "yang leishi", "xiao hai", "kid"}) );
        set("title", "學童");
        set("gender", "男性" );
        set("age", 12);
        set("long", "這是個一個資政書院的學童，正在和同伴玩耍。\n");
        set("combat_exp", 4);
        set("chat_chance", 3);
        set("chat_msg", ({
                "楊磊石道：我最喜歡顧月兒了，長大了一定要娶她為妻。\n",
                "楊磊石道：想不想我告訴你一個秘密呢？\n",
                "楊磊石道：在所有的學童中我是老大！！！\n"
        }));
        set("inquiry", ([
                "秘密" : (: ask_secret :),
                "secret" : "我不懂洋文的。\n",
        ]));
        set("str", 11);
        set("cor", 18);
        set("cps", 20);
        set("per", 24);
        set("papa_name", "楊萬蕭" );
        set("attitude", "peaceful");
        setup();
        carry_object(__DIR__"obj/xiaogua")->wear();
}
