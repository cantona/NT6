// /d/xiakedao/npc/zhangsan.c 張三 賞善使者
// Modified by Zeratul Jan 11 2001 改為給豬腿換玄冰酒

inherit NPC;
int inquiry_jiu();
#include <ansi.h>
void create()
{
        set_name("張三", ({ "zhang san" , "zhang" ,"san" }) );
        set("nickname", HIR"賞善使者"NOR);
        set("gender", "男性" );
        set("age", 30);
        set("long", "只見他身材魁梧，圓臉大耳，穿一襲古銅色綢袍，笑嘻嘻地一臉和藹可親。\n");
        set("attitude", "friendly");
        set("shen_type", 1);

        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set_temp("野豬/forleg", 0);
        set("no_get",1);
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
            "張三大聲稱讚着：好酒，真是好酒，真是盡興！\n",
            "張三咂咂嘴：可惜無肉下酒，不知有沒有地方弄點肉來？\n",
            "張三滿臉堆笑地對你説道：你站在這幹麼呢？是不是想和兄弟我喝兩杯？\n"

        }) );
        set("inquiry",([
                "酒" : (: inquiry_jiu :),
                "臘八粥":"\n去找龍島主看看你的緣分吧。\n",
                "石破天":"\n他是我的結拜兄弟呀，他也在這呢。\n",
                "賞善罰惡令":"\n這是我們兄弟的信物。\n",
//                "here" : "這裏當然就是俠客島啦",
//                "俠客行" : "往南面走，進山後就明白了",
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
                message_vision("張三笑道：酒不是已經給你了嗎？這位" + RANK_D->query_respect(me) + "不要開我們兄弟的玩笑。\n", me);
                return 1;
        }
        if( !query_temp("xkd/forleg", me) )
        { 
                message_vision( "張三笑道：這位"+RANK_D->query_respect(me)+"，這不是酒。不是我小氣，這東西你可喝不得的。\n", me);
                return 1;
        }
        if( !query_temp("xkd/backleg", me) )
        { 
                message_vision("張三笑道：好，好。不過我還得和我的兄弟商量一下。\n",me);
                return 1;
        }        
        if( query_temp("野豬/forleg") || random(10) > 8 )
        { 
                message_vision( "張三笑道：這位"+RANK_D->query_respect(me)+"來得不巧，酒我已經給了別人了。\n", me);
        }
        else
        {
                message_vision( "張三歎着氣説：這位"+RANK_D->query_respect(me)+"，你為什麼一定要喝這酒呢，這對你可未必有好處。\n好吧，既然你要，就給你吧，不過你要小心啊！\n",me);
//張三從腰間解下一個硃紅色的葫蘆，遞了給你。\n" , me);
                obn = new( "/clone/medicine/nostrum/binghuojiu" );
                obn->move( me );
                set_temp("xkd/jiu", 1, me);
        }
        set_temp( "野豬/forleg", 1);
        return 1;
}

int accept_object(object who, object ob)
{
        object me;
        me=this_object();
        command("smile");
        if( query("money_id", ob) )
        {
                command("say " + RANK_D->query_respect(who) +
                        "多謝你的好意，我們哥倆不缺錢花。錢嗎，我是要多少有多少。" );
                return 0;
        }
        if( query("id", ob) == "bone" )
        {
                command(" say " + "你又何苦開這玩笑呢，這要被我兄弟李四看見了，他非殺了你不可。\n");
                return 1;
        }
        if( query("id", ob) == "for leg" )
        {
//            set_temp("野豬/forleg", 1);
                set_temp("xkd/forleg", 1, who);
                return 1;
        }
        return 0;
}
