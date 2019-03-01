#include <ansi.h>;
inherit KNOWER;

void create()
{
        set_name("阿曼", ({ "a man", "a", "man" }));
        set("gender", "女性");
        set("age", 18);
        set("long", "美麗的哈薩克姑娘，身形裊娜面目姣好，眼光中閃爍著笑意。\n");
        set("shen_type", 1);
        set("per", 30);
        set("shen", 200);
        set("combat_exp", 2000);
        set("str", 16);
        set("dex", 18);
        set("con", 12);
        set("int", 24);
        set("attitude", "friendly");
        set("inquiry", ([
                "蘇普" : "嘻嘻，不告訴你。\n",
                "毛毯" : "客人，請到帳蓬裡挑選。\n",
                "李文秀" : "她才是一個大美人呢。\n",
        ]));
        setup();
        add_money("silver", 30);
        carry_object(__DIR__"obj/qcloth")->wear();
}