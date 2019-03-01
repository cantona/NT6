// Room: /d/city/npc/yachai.c 官府衙差
// Last Modified by Winder on Nov. 15 2000

inherit NPC;

void create()
{
        set_name("衙差", ({ "ya chai", "chai" }));
        set("gender", "男性");
        set("age", 25);
        set("long","一個高大威猛的漢子，因為久在官府做事，臉上已經磨煉得毫無表情。\n");
        set("combat_exp", 7500);
        set("shen_type", 1);
        set_skill("unarmed", 30);
        set_skill("dodge", 30);
        set("inquiry", ([
                "工作" : "那還不簡單？你只要有膽量把文書揭下來(jie wenshu)，然後把目標殺了就可以。",
        ]) );
        set("chat_chance", 20);
        set("chat_msg", ({
                "衙差小聲嘀咕道：“常聽人說武林之中藏龍臥虎，也不知道是真是假？\n",
                "衙差朗聲說道：“各路英雄，本城目前懸賞捉拿江洋大盜，望各位能協助官府，懲治兇徒。\n",
        }) );
        setup();
        carry_object(__DIR__"obj/yayifu")->wear();
}