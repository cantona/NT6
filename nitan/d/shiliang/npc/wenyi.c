// This program is a part of NT MudLIB

inherit NPC;
string inquiry_shoupa();
void create()
{
        set_name("溫儀", ({ "wen yi","wen","yi"}) );
        set("gender", "女性" );
        set("title", "溫家小姐");
        set("age", 18);
        set("long", "這是一個美如天仙的女子，眉宇間卻是仿佛隱藏著深憂。\n");
        set("shen_type", 1);
        set("combat_exp", 500);
        set("str", 16);
        set("dex", 17);
        set("con", 17);
        set("int", 18);
        set("attitude", "friendly");
        set("chat_chance",1);
        set("chat_msg",({
                "溫儀靜靜地坐著,雙眼無神地望著窗外。\n",
                "溫儀自言自語地說：郎君啊，你為什麼要誤會我啊？──\n",
                "溫儀黯然淚下，無語地望著手中的手帕。\n",
                "突然間，溫儀的臉色變得蒼白起來：那...那..那碗蓮子羹......\n"
        }) );
        set("inquiry",([
                "手帕" : (: inquiry_shoupa :),
                "金蛇郎君" : "他是我心目中英雄的郎君....",
        ]) );
        set_temp("shoupa",1);
        setup();
        carry_object("/d/city/obj/necklace")->wear();
        carry_object("/d/city/obj/pink_cloth")->wear();
        carry_object("/d/city/obj/flower_shoe")->wear();
        carry_object("/d/city/obj/goldring")->wear();
}

string inquiry_shoupa()
{
        object me=this_player();
        object obn;
        message_vision("溫儀說道：這位"+ RANK_D->query_respect(me)+"，你能幫我個忙嗎？我只是想讓郎君知道我的心意。\n", me );
        if(query_temp("shoupa")==0)
        {  
                message_vision("溫儀又說道：這位"+ RANK_D->query_respect(me)+"，我已經托人幫我帶了，就不麻煩你了。\n",me);
                return "";
        }
        message_vision("溫儀說道：這位"+ RANK_D->query_respect(me)+"，這是我和郎君的信物，看見它，他就知道我的心意了。\n" , me);
        obn=new("/d/shiliang/npc/obj/shoupa");
        obn->move(me);
        set_temp("shoupa",0);
        return "請你一定交到他的手上，他就在莊西的山洞中。說完，溫儀給你一張繡花的手帕。\n";
}

