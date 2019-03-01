// liang.c

inherit NPC;

#include <ansi.h>;
void create()
{
        set_name("樑子翁", ({ "liang ziwen", "liang", "ziwen" }));
        set("gender", "男性");
        set("nickname", HIR"參仙"HIW"老怪"NOR);
        set("age", 43);
        set("str", 25);
        set("per", 20);
        set("dex", 16);
        set("long", "樑子翁身材中等，滿頭白發如銀，但臉色光潤，神採弈弈，穿一
件葛布長袍，打扮非道非俗。他是長白山武學的一派宗師。\n");
        set("combat_exp", 200000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("unarmed", 60);
        set_skill("force", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);
        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/armor", 100);
        set_temp("apply/damage", 100);

        set("neili", 800);
        set("max_neili", 800);
        set("jiali", 50);

        setup();
        carry_object(__DIR__"obj/changpao")->wear();
}
