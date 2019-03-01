#include <ansi.h>

inherit NPC;
void create()
{
        set_name("樵夫", ({ "qiaofu" }) );
        set("gender", "男性" );
        set("age", 30);
        set("per", 30);
        set("long", "一位面色黑紅，悠然自得的樵夫．\n");
        set("combat_exp", 10000);
        set("attitude", "friendly");
        set_skill("dodge", 60);
        set_skill("unarmed", 60);
        set_skill("parry", 60);

        set("chat_chance",10);
        set("chat_msg",({
                "只聽樵夫唱道：雲際依依認舊林，斷崖荒草路難尋。\n",
                "樵夫唱道：西山望見朝來雨，南澗歸時渡處深。\n",
                "樵夫唱道：觀棋柯爛，伐木丁丁，雲邊谷口徐行，賣薪沽酒，狂笑自陶情。\n",
                "樵夫低聲唱道：相逢處，非仙即道，靜坐講黃庭。\n",
        (:random_move:)
        }));

        setup();
        add_money("coin", 50);
        set("inquiry", ([
                "name": "大家都叫我阿牛．平常上山打柴，有時也採些藥材。\n",
                "here": "此乃臥龍崗．聽說山上有位臥龍先生。\n",
        ]) );
        carry_object("/d/city/obj/cloth")->wear();
}