inherit NPC;

string ask_xiang();

void create()
{
        set_name("值日喇嘛", ({ "zhiri lama", "lama" }));
        set("long", 
"這個值日喇嘛拿著一本賬簿，他是專門負責管理捐納箱的。\n");
        set("gender", "男性");
        set("age", 20);
        set("attitude", "peaceful");
        set("class","bonze");
        set("shen_type", 0);
        set("str", 22);
        set("int", 20);
        set("con", 22);
        set("dex", 21);
        
        set("max_qi", 300);
        set("max_jing", 300);
        set("neili", 100);
        set("max_neili", 100);
        set("jiali", 10);
        set("combat_exp", 1000);

        set_skill("force", 20);
        set_skill("dodge", 25);
        set_skill("parry", 20);
        set_skill("strike", 20);

        set("inquiry",([
                "捐納箱"  : (: ask_xiang :),
                "balance"  : (: ask_xiang :),
        ]));


        setup();

        carry_object("/d/xueshan/obj/lamajiasha")->wear();
}

string ask_xiang() 
{

   string stats, str1, str2, str3, *names;
   object xiang;
   mapping box_info = ([]);
   int i, first, second, third, temp;
   string first1, second1, third1, temp1;

   if (xiang = present("juan na xiang", environment(this_object()))) {

           if( !(box_info=query("box_content", xiang)) )
                return "";
       names = keys(box_info);

           if ( sizeof(names) < 2 )
                        return "";
           
           str1 = "本寺自今為止一共募集到" + MONEY_D->price_str(box_info["total_value"]) + "\n";
           str2 = "現捐納箱內還存有" + MONEY_D->price_str(box_info["current_value"]) + "\n";
           str3 = "";
           if (box_info["total_value"] > 0) {

                   // remove the two total values
                   names -= ({"total_value"});
                   names -= ({"current_value"});

                   first = 0;
                   second = 0;
                   third = 0;
                   first1 = "";
                   second1 = "";
                   third1 = "";
                   for (i=0; i<sizeof(names); i++) {

                                if (box_info[names[i]] > third) {
                                         third = box_info[names[i]];
                                         third1 = names[i];
                                         if (third > second) {
                                            temp = third;
                                                temp1 = third1;
                                                third = second;
                                                third1 = second1;
                                                second =  temp;
                                                second1 = temp1;
                                                if (second > first) {
                                            temp = second;
                                                        temp1 = second1;
                                                second = first;
                                                        second1 = first1;
                                                first =  temp;
                                                        first1 = temp1;
                                                }
                                         }
                                }
                   }

                   if (first > 0) {
                          str3 = "其中敬奉最多的幾位施主是：\n\n" + 
                          sprintf( "%30-s %s", first1, MONEY_D->price_str(first) ) + "\n";
                          if (second > 0)
                    str3 += sprintf( "%30-s %s", second1, MONEY_D->price_str(second) ) + "\n"; 
                          if (third > 0)
                    str3 += sprintf( "%30-s %s", third1, MONEY_D->price_str(third) ) + "\n";
           }
           stats = str1+str2+str3;
   }
   else
   {
       stats = "捐納箱被人拿走了，沒法查。\n";
   }

   return stats;
}
}