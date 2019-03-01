#include <ansi.h>
inherit NPC;

void create()
{
        set_name("魯智深", ({"lu zhisheng", "lu", "zhisheng"}));
        set("long", "這個胖大和尚露出好一身花繡，正是五台山來的僧人。\n");
        set("gender", "男性");
        set("nickname", HIM "花和尚" NOR);
        set("title", "樑山好漢");
        set("age", 42);
        set("shen_type", 1);
        set("str", 35);
        set("int", 20);
        set("con", 20);
        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 2500);
        set("max_neili", 2500);
        set("jiali", 200);
        set("combat_exp", 1500000);
        set("score", 20000);
        set("apply/attack",  100);
        set("apply/defense", 100);

        set_skill("cuff", 180);
        set_skill("force", 180);
        set_skill("dodge", 180);
        set_skill("parry", 180);
        set_skill("strike", 180);
        set_skill("zixia-shengong", 180);
        set_skill("poyu-quan", 180);
        set_skill("hunyuan-zhang", 180);
        set_skill("feiyan-huixiang",180);

        map_skill("cuff", "poyu-quan");
        map_skill("force", "zixia-shengong");
        map_skill("dodge", "feiyan-huixiang");
        map_skill("parry", "poyu-quan");
        map_skill("strike", "hunyuan-zhang");

        prepare_skill("strike", "hunyuan-zhang");
        prepare_skill("cuff", "poyu-quan");

        set("chat_chance", 5);
        set("chat_msg", ({
                CYN "魯智深喝道：你這廝，賊眉賊眼的看老爺作什麼？\n" NOR,
                CYN "魯智深憤憤的道：幾個破落戶敢打洒家菜園子的主意，哼，哼！\n" NOR,
                CYN "魯智深說道：方丈說過上一年就讓我當個閣主，院主什麼的。\n" NOR,
        }));
        setup();

        carry_object(__DIR__"obj/dao-cloth")->wear();
        add_money("silver", 50);
}
