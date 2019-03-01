// renying.c

inherit NPC;
string inquiry_linghuchong();

void create()
{
        set_name("任盈盈", ({ "ren yingying","ren","ying"}) );
        set("gender", "女性" );
        set("age", 20);
        set("shen_type", 1);
        set("combat_exp", 500000);
        set("per", 30);
        set("str", 16);
        set("dex", 27);
        set("con", 17);
        set("int", 18);
        set("attitude", "friendly");
        set("chat_chance",60);
            set("chat_msg",({
        "任盈盈說道：不知令狐沖他，怎樣了，是否又和那小賤人在一起......\n",
        "任盈盈說道：你若能把這封信捎給他，可太謝謝你了.............\n",
        "任盈盈說道：也不知藍鳳凰見沒見到他，可真急死我了.......\n",
           }) );
       
           create_family("日月神教",2,"弟子 聖姑");
       set("inquiry",([
           "令狐沖" : (: inquiry_linghuchong:),
           ]) );
       set_temp("letter",1);
       setup();
       carry_object("/clone/cloth/female5-cloth")->wear();
        carry_object("/d/heimuya/npc/obj/jin")->wear();
       carry_object("/d/heimuya/npc/obj/letter");
}

string inquiry_linghuchong()
{
 object me=this_player();
 object obn;

 message_vision("任盈盈說道：去年上華山一去就再無音信，他不會忘記我吧......\n", me );
 if(query_temp("letter")==0)
 {  message_vision("任盈盈又說道：這位"+ RANK_D->query_respect(me)+"，我已經派
藍鳳凰去尋找了，也不知道怎麼樣了。\n",me);
   return "";
 }
   message_vision("任盈盈又說道：這位"+ RANK_D->query_respect(me)+"，我這裡有
信，你要是找到令狐沖，就把信交給他，他會明白的。\n" , me);
   obn=new("/d/heimuya/npc/obj/letter");
   obn->move(me);
   set_temp("letter",0);
   
   return ("這封信煩你交給令狐沖。\n");
}
