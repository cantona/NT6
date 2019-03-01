#include <ansi.h>
inherit NPC;

void create()
{
        set_name("寡婦", ({ "gua fu", "gua", "fu" }));
        set("gender", "女性" );
        set("age", 25);
        set("long", "一個年輕漂亮又不甘寂寞的小寡婦。\n");
        set("shen_type", -1);
        set("combat_exp", 10000);
        set("str", 18);
        set("dex", 19);
        set("con", 19);
        set("int", 19);
        set("attitude", "friendly");
        set("chat_chance", 2);
        set("chat_msg", ({
                CYN "小寡婦哭着：我苦命的夫哇，你怎麼撇下我不管了喲。\n" NOR,
                CYN "小寡婦抹了把眼淚，暗暗瞟了你一眼。\n" NOR,
        }));
        setup();
        carry_object("/clone/misc/cloth")->wear();
}