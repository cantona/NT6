// yi.c
#include <ansi.h>

inherit NPC;
int ask_lvzhuweng();

void create()
{
        set_name("易師爺", ({ "yi shiye", "yi", "shiye"}));
        set("long",
"易師爺是個瘦瘦小小、五十來歲的漢子，頦下留著一部稀稀疏
疏的胡子，衣履甚是整潔。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 14);
        set("str", 15);
        set("int", 25);
        set("con", 25);
        set("dex", 30);

        set("max_neili", 500);
        set("jiali", 50);
        set("combat_exp", 500);

        set_skill("dodge", 10);
        set_skill("unarmed", 10);

        set_temp("apply/attack", 15);
        set_temp("apply/damage", 15);
        set("inquiry", ([
                "綠竹翁"     : (: ask_lvzhuweng :),
                "東城綠竹翁" : (: ask_lvzhuweng :),
                "東城"       : "東城有個綠竹翁，彈得好琴，吹得好簫。\n",
        ]));

        set("chat_chance", 30);
        set("chat_msg", ({
                "東城有個綠竹翁，彈得好琴，吹得好簫。\n",
        }) );

        setup();
        carry_object("/clone/misc/cloth")->wear();
        add_money("gold",1);
}
int ask_lvzhuweng()
{
        object me = this_player();
        message_vision(CYN"易師爺猛地睜圓眯眯眼，對$N說道：你也想去見識他的琴簫？那我們一起去吧。\n"NOR,me);
        set_leader(me);
        return 1;
}
