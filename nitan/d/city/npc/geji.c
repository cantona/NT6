//NPC /d/city/npc/geji.c
#include <ansi.h>
inherit NPC;
void create()
{
        set_name("歌妓", ({ "ge ji", "ji" }));
        set("long", "她是揚州裡的著名的歌妓，賣藝不賣身。\n");
        set("gender", "女性");
        set("age", 17);
        set("attitude", "friendly");
        set("shen_type", 1);

        set("per", 27);
        set("str", 15);
        set("int", 14);
        set("con", 15);
        set("dex", 16);
        set("qi", 100);
        set("max_qi", 100);
        set("jing", 100);
        set("max_jing", 100);
        set("neili", 10);
        set("max_neili", 10);
        set("combat_exp", 500);

        set_skill("unarmed", 10);
        set_skill("dodge", 10);
        set_skill("parry", 10);

        set("chat_chance", 10);
        set("chat_msg", ({
                "歌妓宛轉唱道：
“青山隱隱水迢迢，秋盡江南草木凋。二十四橋明月夜，玉人何處教吹簫？”\n",
                "歌妓輕聲低唱：
“落魄江南載酒行，楚腰纖細掌中輕。十年一覺揚州夢，贏得青樓薄幸名。”\n",
                "歌妓幽幽淺唱：
“星分牛鬥，疆連淮海，揚州萬井提封。花發路香，鶯啼人起，朱簾十裡春風。
豪傑氣如虹。曳照春金紫，飛蓋相從。巷入垂楊，畫橋南北翠煙中。”\n",
                "歌妓幽幽淺唱：
“淮山浮遠翠，淮水漾深綠。倒影入樓台，滿欄花撲撲。誰知寰閨外，依舊
有蘆屋。時見淡妝人，青裙曳長幅。”\n",
                (: random_move :)
        }) );

        setup();
        carry_object(CLOTH_DIR+"cloth/qi-dress")->wear();
}