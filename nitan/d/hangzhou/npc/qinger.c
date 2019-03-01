// huoji. 

inherit NPC;
#include <ansi.h>
inherit F_DEALER;

void create()
{
        set_name("情兒", ({ "qing er", "qing" }));
        set("title", HIM"琴瑟和鳴"NOR);
        set("nickname",HIR"赤繩綰結"NOR);
        set("shen_type", 1);

        set("str", 30);
        set("gender", "女性");
        set("age", 17);
         set("per", 30);
        set("long",
"一個常駐月老祠附近的小姑娘，賣一些稀
罕的東西，懸奇古怪，據說有助姻緣。\n"
);
        set("combat_exp", 2500);
        set("attitude", "friendly");
        set("chat_chance", 1);
        set("chat_msg", ({
                "情兒笑眯眯地說道：“求姻緣啊？來看看我賣的東西吧！”\n",
        }));

        set("vendor_goods", ({
                "/d/hangzhou/npc/obj/yuelao-xianshui.c",
                "/d/hangzhou/npc/obj/sansheng-youyue.c",
                "/d/hangzhou/npc/obj/ruyi-su.c",
                "/d/hangzhou/npc/obj/tongxin-jie.c",
                "/d/hangzhou/npc/obj/xuannv-lingfu.c",
                "/d/hangzhou/npc/obj/huangtong-suo.c",
        }));

        setup();
        carry_object("/d/hangzhou/npc/obj/sahua-qun.c")->wear();
}

void init()
{
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}
