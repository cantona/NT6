//Edited by fandog, 02/15/2000
#include <ansi.h>
inherit NPC;
string ask_me();

void create()
{
        set_name("凌霜華",({ "ling shuanghua", "ling"}));
        set("gender", "女性" );
        set("nickname", HIY"人淡如菊"NOR);
        set("title",HIM"知府千金"NOR);
        set("age", 18);
        set("long",
"一個清秀絕俗的少女正在觀賞菊花，穿一身嫩黃衫子，當真是人淡如菊。\n");
        set_temp("apply/defense", 5);
        set("combat_exp", 70);
        set("shen_type", 1);
        set("str", 14);
        set("per", 28);
        set("dex", 15);
        set("con", 16);
        set("int", 15);
        set("flower_count", 1);
        set("attitude", "friendly");
        set("chat_chance", 5);
        set("chat_msg", ({
                "凌霜華臉紅了紅，低聲道：“對不起，先生別見怪，小丫頭隨口亂說。”\n",
        }) );
        set("inquiry", ([
                "綠菊"   : (: ask_me :),
                "綠菊花" : (: ask_me :),
                "丁典"   : "“丁大哥為我受盡羞辱。”說罷，眼圈忽地一紅。\n",
                "丁大哥" : "“丁大哥為我受盡羞辱。”說罷，眼圈忽地一紅。\n",
        ]));
        setup();
        carry_object("/d/wuchang/obj/nenhuangshan")->wear();
        carry_object("/clone/cloth/female-shoe")->wear();
}


string ask_me()
{
        object ob;

        if (query("flower_count") < 1)
                return "謝謝你提醒我，我會給丁大哥放盆綠菊花的。";
        addn("flower_count", -1);
        ob = new("/d/jingzhou/obj/greenflower1");
        ob->move(this_player());
        return NOR"麻煩你，把這朵「"HIG"綠玉如意"NOR"」轉交給丁大哥，他就會明白的。"NOR;
}