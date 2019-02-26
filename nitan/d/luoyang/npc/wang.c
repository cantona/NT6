// wang.c

#include <ansi.h>

inherit NPC;
void create()
{
        set_name("王元霸", ({ "wang yuanba", "wang", "yuanba" }) );
        set("title", HIY"金刀門"NOR"第三代門主");
        set("nickname", HIG"中州大俠"HIY"金刀無敵"NOR);
        set("gender", "男性" );
        set("shen_type", 1);
        set("age", 70);
        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);
        set("long",
"王元霸已有七十來歲，滿面紅光，顎下一叢長長的白鬚飄在胸前，精神
矍鑠，左手嗆啷啷的玩着兩枚鵝蛋大小的金膽。武林中人手玩鐵膽，甚
是尋常，但均是鑌鐵或純鋼所鑄，王元霸手中所握的卻是兩枚黃澄澄的
金膽，比之鐵膽固重了一倍有餘，而且大顯華貴之氣。\n" );
        set("combat_exp", 500000);
        set("attitude", "friendly");
        set_skill("blade", 100);
        set_skill("dodge", 100);
        set_skill("unarmed", 100);
        set_skill("throwing", 100);
        set_skill("feixing-shu", 100);
        set_skill("yanfly", 100);
        set_skill("parry", 100);
        map_skill("throwing", "feixing-shu");
        map_skill("parry", "feixing-shu");
        map_skill("dodge", "yanfly");

        setup();
        carry_object(__DIR__"obj/jindan")->wield();
        carry_object(CLOTH_DIR"jinduan")->wear();
        add_money("gold", 5);
}
