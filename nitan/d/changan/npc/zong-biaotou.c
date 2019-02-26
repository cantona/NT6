//zong-biaotou.c

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("萬青山", ({ "wan qingshan", "wan", "qingshan" }) );
        set("title", HIR "龍行天下" NOR);
        set("gender", "男性" );
        set("age", 45);
        set("int", 30);
        set("skill_public",1);
        set("long",
                "河洛鏢局總鏢頭，為人豪爽，不少走江湖的人物都是向他求教的武功。\n"
        );
        set("chat_chance", 10);
        set("chat_msg", ({
                "萬青山説道：鏢局的人手越來越少了！\n",
                "萬青山説道：護鏢真是一件很危險的事！\n",
        }) );
        set("attitude", "peaceful");
        set_skill("unarmed", 40);
        set_skill("literate", 40);
        set_skill("force", 40);
        set_skill("dodge",40);
        set_skill("parry",40);
        set("combat_exp", 100000);
        setup();
        carry_object("/d/changan/npc/obj/jinzhuang")->wear();
}

int recognize_apprentice(object ob)
{
        return 1;
}
