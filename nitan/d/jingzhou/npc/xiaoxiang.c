#include <ansi.h>
inherit NPC;

void create()
{
        set_name("蕭湘子", ({ "xiao xiangzi", "xiao" }));
        set("long", "蕭湘先生被稱為當世第二大文學家，肚子裏的墨水比海還要深。\n");
        set("gender", "男性");
        set("age", 45);

        set_skill("literate", 300);
        set_skill("taoism", 300);

        set_skill("unarmed", 80);
        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_temp("apply/attack", 80);
        set_temp("apply/defense", 80);
        set_temp("apply/damage", 20);

        set("combat_exp", 400000);
        set("shen_type", 1);
        setup();

        set("chat_chance", 3);
        set("chat_msg", ({
                CYN "蕭湘子説道：普天之下，莫非王土；率土之濱，莫非王臣。\n" NOR,
                CYN "蕭湘子説道：出家人，小過損益焉；無妄大過，未濟鹹困之。\n" NOR,
                CYN "蕭湘子説道：大學之道，在明明德。在親民，在止於至善。 \n" NOR,
                CYN "蕭湘子説道：格物致知，誠意正心，修身齊家，治國平天下。\n" NOR,
        }) );
        carry_object("/clone/misc/cloth")->wear();
}