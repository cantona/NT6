// Npc: /d/kunlun/npc/monkey.c
// Last Modified by winder on Jun. 29 2001

inherit NPC;

void create()
{
        set_name("猴子", ({ "monkey" }) );
        set("gender", "雄性");
        set("race", "走獸");
        set("age", 5);
        set("long", "這隻猴子在在桃樹間跳上跳下，還不時津津有味地啃幾口着蜜桃。\n");
        set("combat_exp", 5000);
        set("shen_type", -1);
        set("attitude", "peaceful");
        set("water", 200);
        set("food", 200);

        set("apply/attack", 10);
        set("apply/defense", 10);

        set("chat_chance", 2);
        set("chat_msg", ({
                "猴子衝着你大扮鬼臉，嘰嘰歪歪一陣亂叫......!\n",
                "猴子忽然跳了過來，一個倒勾，前爪一伸摘了你的草帽!\n",
                "猴子轟的一聲一起從這株樹跳到那株樹，把你嚇了一大跳!\n",
        }) );

        setup();
}
