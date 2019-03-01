// npc: /d/city/npc/gubancheng.c
// Last Modified by Winder on Jul. 15 2000

#include <ansi.h>

inherit NPC;
inherit F_DEALER;
void create()
{
        set_name( YEL "孔進金" NOR, ({ "kong jinjin","kong","jinjin" }) );
        set("gender", "男性" );
        set("title", "孔家頭巾舖老板");
        set("age", 47);
        set("long", @LONG
孔進金孔老板開了這家頭巾舖已經有好幾年了，頗受大家的好評，他的
生意也越做越大，可是他卻不享清福，仍然親自站櫃台，招呼生意。這
樣既省了人手又可以監視伙計們，讓他們沒有偷懶的機會。
LONG
    );
        set("attitude", "friendly");
        set("rank_info/respect", "老哥");
        set("rank_info/rude","老王八蛋");
        set("combat_exp",100);
        set("inquiry", ([
                "頭巾":"哎，一看您就是有眼光的主兒，要不怎麼想買咱家的頭巾呢？\n",
                "here":"哎喲，客官，您是頭回來揚州吧？好好轉轉吧。\n",
        ]) );
        set("chat_chance", 40);
        set("chat_msg", ({
                "孔老板道：喲，客官，一看您就是練武的人，練武人戴塊青色頭巾最好了。\n",
                "孔老板道：客官，您聽說沒有，大理的段王爺出錢開通了到大理的馬車。\n",
                "孔老板道：來，客官，選一塊喜歡的頭巾吧，我給您打個九五折怎麼樣？\n",
                "孔老板道：呵呵，客官，您要是不買您就多看看貨色，我這兒還忙著呢。\n",
        }));
        set("vendor_goods", ({
                HEAD_DIR+"damao",
                HEAD_DIR+"mabutoujin",
                HEAD_DIR+"nuanmao",
                HEAD_DIR+"qingshajin",
                HEAD_DIR+"sanshanmao",
                HEAD_DIR+"wanzijin",
                HEAD_DIR+"yizijin",
                HEAD_DIR+"zaoshahuajin",
                HEAD_DIR+"zhanmao",
        }) );
        set_skill("unarmed", 5);
        setup();
        carry_object( "/clone/cloth/male-cloth")->wear();
}

void init()
{
        object ob = this_player();
        ::init();
        if( interactive(ob) && !is_fighting() )
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_list", "list");
        add_action("do_buy", "buy");
}

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        message_vision( "孔老板見有人進來，連忙吆喝：“瞧一瞧，看一看，咱家的頭巾真不賴！”\n",ob);
        return;
}