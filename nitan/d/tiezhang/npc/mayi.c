#include <ansi.h>

inherit NPC;

void create()
{
        set_name("麻衣長老", ({ "mayi zhanglao", "mayi", "zhanglao" }));
        set("long",
        "他是一個年約六旬的老者，滿頭花發，兩鬢斑白。\n"
        "他兩側的太陽穴高高鼓起，微閉的雙目中時而閃過凌厲的眼神，似乎身懷絕技。\n"
        );
        set("gender", "男性");
        set("attitude", "peaceful");
        set("age", 30);
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiaji", 50);
        set("combat_exp", 10000);
        set("score", 1);

        set_skill("force", 120);
        set_skill("tiezhang-xinfa", 120);
        set_skill("dodge", 120);
        set_skill("dengping-dushui", 120);
        set_skill("strike", 120);
        set_skill("tongbi-zhang", 120);
        set_skill("parry", 120);

        map_skill("force", "tiezhang-xinfa");
        map_skill("dodge", "dengping-dushui");
        map_skill("strike", "tongbi-zhang");
        map_skill("parry", "tongbi-zhang");

        setup();
        carry_object(__DIR__"obj/black-cloth")->wear();
}