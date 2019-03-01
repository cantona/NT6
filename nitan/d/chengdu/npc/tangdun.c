#include <ansi.h>

inherit NPC;

void create()
{
        set_name("唐鈍", ({"tang dun"}));
        set("title","唐門長房弟子");
        set("long",
        "這是一個唐門長房弟子，一襲青衣，渾身透著一股邪氣。本月長房輪值。\n"
        );

        set("gender", "男性");
        set("attitude", "peaceful");

        set("age", 10+random(10));
        set("shen_type", -1);
        set("str", 25+random(10));
        set("dex", 25+random(10));
        set("max_qi", 200);
        set("max_jing", 150);
        set("neili", 200);
        set("max_neili", 200);
        set("jiaji", 5+random(5));
        set("combat_exp", 20000+random(10000));

        set_skill("force", 40);
        set_skill("dodge", 40);
        set_skill("unarmed", 40);
        set_skill("parry", 40);
        set_skill("sword", 60);
        set_skill("shedao-qigong", 30);
        map_skill("sword","shedao-qigong");
                set("chat_chance", 3);
        set("chat_msg", ({
            "唐鈍面無表情地說道: 江湖中無人敢侵犯唐門! \n",
        }) );

        setup();
}