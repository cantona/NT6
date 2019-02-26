// shusheng
// by ruri
inherit NPC;
#include <ansi.h>;
inherit F_DEALER;

void create()
{
        set_name("月下書生", ({ "yuexia shusheng","shusheng","sheng" }));
        set("str", 27);
        set("title", HIC"翻雲覆雨"NOR);
        set("nickname", HIG"竹梅共侶"NOR);
        set("shen_type", 1);
        set("gender", "男性");
        set("age", 28);
        set("per", 28);
        set("long", "一個眉目俊秀的青年書生，閒來好替人解籤，有些瘋顛。\n");
        set("combat_exp", 15000);
        set("attitude", "friendly");
        set("chat_chance", 1);
        set("chat_msg", ({
                "月下書生搖頭晃腦地吟道：“著以長相思，緣以結不解？同心而離居，憂傷以終老。”\n"
        }));

        set("inquiry", ([
     "解籤" : "“身無彩蝶雙飛翼，心有靈犀一點通”，籤文上已經説得明明白白，為何你還不能\n明白上天為你安排的這一世情緣？\n"
                ]));
        
        set_skill("unarmed", 60);
        set_skill("dodge", 60);
        set_skill("parry", 60);

        setup();
        carry_object("/d/hangzhou/npc/obj/baibu-qingshan.c")->wear();
}
