// npc: /d/city/npc/wei.c
// Dec.12.1997 by Venus
#include <ansi.h>;
inherit BUNCHER;
void create()
{
        set_name("韋春芳", ({ "wei chunfang", "chunfang", "wei" }) );
        set("gender", "女性" );
        set("title", "麗春院老板娘");
        set("age", 42);
        set("long",
            "韋春芳是當朝鹿鼎公兼紅花會總舵主韋小寶他娘，雖是徐"
            "娘半老，但風韻猶存。\n");
        set("str", 25);
        set("dex", 25);
        set("con", 25);
        set("int", 25);
        set("shen_type", 1);

        set_skill("unarmed", 20);
        set_skill("force", 20);
        set_skill("dodge", 35);

        set("combat_exp", 25000);

        set("max_qi", 300);
        set("max_jing", 100);
        set("neili", 500);
        set("max_neili", 500);

        set("attitude", "friendly");
        set("inquiry", ([
            "name"   : "老娘我就是韋春芳。",
            "韋小寶" : "那是我的乖兒子，長得就像你。",
            "麗春院" : "我們麗春院可是揚州城裡頭一份的找樂子去處。",
            "here"   : "我們麗春院可是揚州城裡頭一份的找樂子去處。",
        ]) );

        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "韋春芳得意地說道：當年老娘我標致得很，每天有好幾個客人。\n",
                "韋春芳怒罵道：辣塊媽媽，要是羅剎鬼、紅毛鬼子到麗春院來，老娘用\n"
                "大掃帚拍了出去。\n",
                "韋春芳對你說道：你一雙眼睛賊忒嘻嘻的，真像那個喇嘛！\n",
        }) );
        carry_object("/d/city/obj/flower_shoe")->wear();

        carry_object("/d/city/obj/pink_cloth")->wear();
}
void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
    if (! objectp(me) || environment(me) != environment())
        return;
    command("look"+query("id", me));

    if( query("gender", me) == "無性"){
       command("say 你當老娘是爛婊子嗎？辣塊媽媽，老娘滿漢蒙藏回都接，
就是不伺太監！\n");
       command("kick"+query("id", me));
/*
       message("vision", me->name() +"被韋春芳一腳踢出門外。\n",
                environment(me), ({me}));
       me->move("/d/city/nandajie2");
       message("vision", me->name() +
"被人從麗春院裡踢了出來，栽倒在地上，磕掉兩顆門牙。\n",environment(me), ({me}));
*/

    }
    else {
    if( query("class", me) == "bonze"){
       command("say 呦，" + RANK_D->query_respect(me)
                +"也來光顧我們麗春院啊。");
       command("say 想當年我接過一個西藏喇嘛，他上床前一定要念經，一面念經，
眼珠子就骨溜溜的瞧著我。");
    }
    if( query("gender", me) == "女性"){
       command("say 哎呀，這年月大姑娘也逛窯子，成何體同。");
       command("sigh");
       command("say 可惜我兒子不在，不然讓他伺候你。");
    }
    command("say 樓上樓下的姑娘們，客人來了！");
    }
    return ;
}
