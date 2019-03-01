// xiejian.c 邪劍李四

#include <ansi.h>

inherit BUNCHER;

void create()
{
        set_name("李四", ({ "li si", "li" }) );
        set("title", "小店老板");
        set("gender", "男性" );
        set("shen_type", -1);
        set("age", 40);

        set("str", 30);
        set("con", 30);
        set("int", 30);
        set("dex", 30);

        set("long",
                "這是整天笑咪咪的小店老板，雖然不賣什麼東西，卻也過得自在。\n" );

        set("combat_exp", 100000);
        set("attitude", "peaceful");
        set("chat_chance", 1);
        set("chat_msg", ({
                "李四說道: 這位客官，您想買些什麼東西嗎 ?\n",
        }) );

        set("inquiry", ([
                "邪劍"   : "我已經歸隱了，不幹這行了。",
                "殺人"   : "我已經歸隱了，不幹這行了。",
        ]) );

        set("max_qi", 700);
        set("max_jing", 400);
        set("neili", 700);
        set("max_neili", 700);
        set("jiali", 50);
        set("shen_type", -1);
        set("env/wimpy", 60);

        set_skill("force", 60); 
        set_skill("unarmed", 80);
        set_skill("sword", 100);
        set_skill("dodge", 100);
        set_skill("parry", 100);
        
        setup();
        
        carry_object("d/city/obj/gangjian")->wield();
        carry_object("d/city/obj/cloth")->wear();
}
