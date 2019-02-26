// Feb. 6, 1999 by Winder
inherit NPC;
string inquiry_afeng();
void create()
{
        set_name("阿土", ({ "a tu","a","tu"}) );
        set("gender", "男性" );
        set("age", 18);
        set("long", "這是一個英俊瀟灑的僕人。\n");
        set("shen_type", 1);
        set("combat_exp", 500);
        set("str", 16);
        set("dex", 17);
        set("con", 17);
        set("int", 18);
        set("attitude", "friendly");
        set("chat_chance",1);
        set("chat_msg",({
            "阿土一邊掃地一邊搖着頭。\n",
            "阿土自言自語地説：我一直喜歡阿鳳，但是怎麼向她表白呢？\n",
            "阿土突然拍了拍腦袋：對了，我給她寫情書吧！\n"
        }) );
        set("inquiry",([
                "阿鳳" : (: inquiry_afeng :),
        ]) );
        set_temp("qingshu",1);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}
string inquiry_afeng()
{
 object me=this_player();
 object obn;
 message_vision("阿土説道：這位"+ RANK_D->query_respect(me)+"，我看你也是性情中人,我就不和你繞圈子了，你能把這封信交給阿鳳嗎？\n", me );
 if(query_temp("qingshu")==0)
 {  message_vision("阿土又説道：這位"+ RANK_D->query_respect(me)+"，我已經託人幫我帶了，也不知道她的心意如何，唉.....\n",me);
   return "";
 }
   message_vision("阿土又説道：這位"+ RANK_D->query_respect(me)+"，我這裏有封我寫了三天三夜的情書，麻煩你了,我後半生的幸福就託給你了。\n" , me);
   obn=new("/d/shiliang/npc/obj/qingshu");
   obn->move(me);
   set_temp("qingshu",0);
   return "請你一定交到她的手上。説完從懷裏摸出一封摺疊成千紙鶴般的信，交給你。\n";
}