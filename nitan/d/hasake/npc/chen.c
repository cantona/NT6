// dingtong.c
#include <ansi.h>
inherit NPC;
void create()
{
       set_name("陳達海", ({ "chen dahai", "chen", "dahai" }) );
       set("title", "鏢師");
       set("nickname", "青蟒劍");
       set("gender", "男性" );
       set("shen", -2500);
       set("age", 43);
       set("str", 23);
       set("con", 20);
       set("int", 20);
       set("dex", 22);
       set("env/wimpy", 60);
       set("long","
一個身穿羊皮襖的高大漢子，虯髯滿腮，說的哈薩克語很不純正，
但目光炯炯，腰間掛著一柄長劍。他是霍元龍手下的鏢師之一。\n" );
       set("combat_exp", 250000);
       set("attitude", "heroism");
        set("chat_chance", 30);
       set("chat_msg", ({ (: random_move :) }) );          
       set("max_qi", 600);
       set("max_jing", 500);
       set("neili", 700);
       set("max_neili", 700);
       set("jiali", 10);
       set_skill("force", 140); 
       set_skill("unarmed", 140);
       set_skill("sword", 140);
       set_skill("dodge", 140);
       set_skill("parry", 140);
       set_skill("qingmang-sword", 150); 
       map_skill("sword", "qingmang-sword");
       map_skill("parry", "qingmang-sword");
       map_skill("parry", "qingmang-sword");       
       setup();
       carry_object(__DIR__"obj/jinjian")->wield();
       carry_object(CLOTH_DIR"cloth")->wear();
       add_money("silver", 10);
}
#include "bs.h";
