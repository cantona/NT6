// /d/xiakedao/npc/lisi.c 李四，罰惡使者
// Modified by Zeratul Jan 11 2001 改為給豬腿換玄冰酒

inherit NPC;
#include <ansi.h>
int inquiry_jiu();

void create()
{
        set_name("李四", ({ "li si" , "li" , "si" }) );
        set("nickname", BLU"罰惡使者"NOR);
        set("gender", "男性" );
        set("age", 30);
        set("long", "只見他身材甚高，十分瘦削，身穿天藍色長袍，一臉的苦象。\n");
        set("attitude", "friendly");
        set("shen_type", 0);

        set_temp("野豬/forleg", 0);
        set("no_get",1);

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("combat_exp", 2000000);
        set("score", 20000);
        set_skill("parry", 200);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("unarmed", 200);
        set_skill("taixuan-gong", 200);
        map_skill("parry", "taixuan-gong");
        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        set("chat_chance",3);
        set("chat_msg",({
            "李四大聲稱讚着：好酒，真是好酒，真是酒逢知己千杯少啊！\n",
            "李四咂咂嘴：可惜無肉下酒，喝起來不爽。\n",
            "李四斜睨着你説道：你站在這幹麼呢？難道也想和我兄弟倆乾一杯不成？\n"
        }) );
        set("inquiry",([
           "酒"     : (: inquiry_jiu :),
//           "here"   : "這裏當然就是俠客島啦。",
//           "俠客行" : "往南面走，進山後就明白了。",
        ]) );
        create_family("俠客島", 2, "弟子");
        setup();
}

int inquiry_jiu()
{
        object me=this_player();
        object obn;

        if( query_temp("xkd/jiu", me) )
        { 
                message_vision("李四瞪眼説到：酒不是已經給你了嗎？這位"+RANK_D->query_respect(me) + "不要貪得無厭。\n", me);
                return 1;
        }
        if( !query_temp("xkd/backleg", me) )
        { 
                message_vision( "李四瞪眼説到：這位"+RANK_D->query_respect(me)+"，你以為這是什麼酒，是二鍋頭啊？？這麼寶貴的東西我怎能隨便給人呢。\n", me);
                return 1;
        }
        if( !query_temp("xkd/forleg", me) )
        { 
                message_vision( "李四瞪眼説到：這位"+RANK_D->query_respect(me)+"，想要酒我還得和我的兄弟商量一下。\n", me);
                return 1;
        }        
        if( query_temp("野豬/backleg") || random(10) > 5 ) 
        { 
                message_vision( "李四瞪眼説到：這位"+RANK_D->query_respect(me)+"來得不巧，酒我已經給了別人了。\n", me);
        }
        else
        {
                message_vision( "李四冷冷地説道：這位" + RANK_D->query_respect(me)+"，居然想喝我的毒酒，好吧，你有膽子就喝吧，不過可別後悔。\n",me);
                obn = new( "/clone/medicine/nostrum/binghuojiu" );
                obn->move( me );
                set_temp("xkd/jiu", 1, me);
        }
        set_temp( "野豬/backleg", 1 );
        return 1;
}

int accept_object(object who, object ob)
{
        object me;
        me=this_object();
        if( query("money_id", ob) )
        {
                command("say " + RANK_D->query_respect(who) +
                "你以為我們哥倆缺錢花嗎？告訴你吧，你就算把皇宮大內" +
                "的奇軫異寶都擺到我面前，我也視如糞土。" );
                return 0;
        }
        if( query("id", ob) == "bone" )
        {
               command(" say " + "你這廝，居然敢拿這種東西來戲弄老子。真是天堂有路你不走，地獄無門你偏來。\n");
               me->set_leader(who);
               me->kill_ob(who);
               who->fight_ob(me);
               return 0;
        }
        if( query("id", ob) == "back leg" )
        {
               set_temp("xkd/backleg", 1, who);
               return 1;
        }
        return 0;

}
