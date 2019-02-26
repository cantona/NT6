#include <ansi.h>
inherit NPC;

void create()
{
        set_name("哈薩克人", ({ "hasake ren", "hasake", "ren"}));
        set("gender", "男性");
        set("age", 26);
        set("long", "一個哈薩克族青年，趕着幾十只羊。\n");
        set("attitude", "friendly");
        set("combat_exp", 4000);
        set("shen_type", 0);
        set("str", 32);
        set("int", 18);
        set("con", 22);
        set("dex", 17);
        set("max_qi", 600);
        set("max_jing", 600);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 50);
        set_skill("unarmed", 50);
        set_skill("blade", 50);
        set_skill("parry", 50);
        set_skill("dodge", 50);
        set_temp("apply/attack", 25);
        set_temp("apply/defense", 25);
        set_temp("apply/damage", 25);

        set("inquiry", ([
                    "蘇普"   : "呀，你也要跟蘇普摔跤？往東走你就會找到他。",
                    "阿曼"   : "歎，我摔跤總贏不了蘇普。",
                    "計老人" : "計老人會釀又香又烈的美酒，會醫牛羊馬匹的疾病。",
        ]));

        set("chat_chance", 10);
        set("chat_msg", ({
                CYN "哈薩克人道：上個月我用刀砍死了一頭狼，剝了狼皮送給咱阿妹。\n" NOR,
                CYN "哈薩克人道：阿曼是草原上一朵會走路的花。\n" NOR,
        }) );

        setup();
        carry_object(__DIR__"obj/duandao")->wield();
        carry_object(__DIR__"obj/ycloth")->wear();
}