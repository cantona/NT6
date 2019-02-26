inherit NPC;
#include <ansi.h>

string clear_degree(string arg);
int add_degree(object ob);

void create()
{
        set_name(HIY"趙一仁"NOR, ({"zhao yiren", "zhao", "yiren"}));
        set("nickname", HIR"兵部尚書"NOR);
        set("gender", "男性");
        set("age", 41);
        set("long", 
         "他就是當今兵部大大有名的尚書趙一仁，在朝中極有權勢。\n"
        );

        set("attitude", "friendly");
        set("per", 20);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("chat_chance", 5);

        set("chat_msg", ({
                "趙一仁歎了口氣道：最近怎麼沒什麼人來送禮了，看來得想想辦法了。\n",
        }));

        set("inquiry", ([
                "功名" : "要求取功名，好啊，可是老夫近來身體不適，這個。。。", 
        ]));

        setup();
        carry_object("clone/misc/cloth")->wear();
}

int add_degree(object ob)
{
        string degree,old_degree;

        degree=HIR "提督" NOR;
        if( query("degree", ob))old_degree=query("degree", ob);
        else old_degree="";

        message("channel:rumor",MAG"【大宋京城】"HIY"奉天承命，皇帝詔曰："
        +"策封"+old_degree+""+HIW+query("name", ob )
        +HIY" 為大宋 "NOR+degree+HIY"，欽此！\n"NOR,users());
        delete_temp("degree_jungong", ob);

        if( query("degree", ob) )
        {
         if( query("degree_ask", ob) )
         degree=HIM"☆"NOR+clear_degree(query("degree", ob) )
              +HIM " ☆ " NOR+degree+HIM " ☆ "NOR;
          else
         degree=HIM"☆"NOR+clear_degree(query("degree", ob) )
              +degree+HIM " ☆ " NOR;
        } else
         degree=HIM " ☆ " NOR+degree
              +HIM " ☆ " NOR;               

        set("degree_jungong", 8, ob);
        set("degree", degree, ob);

        return 1;
}

string clear_degree(string arg)
{
        if ((strsrch(arg, BLU "士卒" NOR) >= 0) ||
            (strsrch(arg, BLU "遊擊" NOR) >= 0) ||
            (strsrch(arg, HIC "參將" NOR) >= 0) ||
            (strsrch(arg, HIC "裨將" NOR) >= 0) ||
            (strsrch(arg, HIY "佐將" NOR) >= 0) ||
            (strsrch(arg, HIY "副將" NOR) >= 0) ||
            (strsrch(arg, HIR "將軍" NOR) >= 0) ||
            (strsrch(arg, HIR "提督" NOR) >= 0) ||
            (strsrch(arg, HIM " ☆ " NOR) >= 0))
        {
                arg = replace_string(arg, BLU "士卒" NOR,"");
                arg = replace_string(arg, BLU "遊擊" NOR,""); 
                arg = replace_string(arg, HIC "參將" NOR,"");
                arg = replace_string(arg, HIC "裨將" NOR,"");   
                arg = replace_string(arg, HIY "佐將" NOR,"");
                arg = replace_string(arg, HIY "副將" NOR,"");   
                arg = replace_string(arg, HIR "將軍" NOR,"");
                arg = replace_string(arg, HIR "提督" NOR,"");   
                arg = replace_string(arg, HIM " ☆ " NOR,"");
        }
        return arg;
}

int accept_object(object who, object ob)
{
        if( query("degree_jungong", who) >= 8 || query("guo_shoucheng/reward", who) >= 8100 )
        {
         message_vision("$N一臉憤慨：你我同朝為官，如何使這種不仁不義"
                        +"之舉？來呀，把"+query("name", who )
                        +"給我轟出去！！\n"+"$n被一羣家將連推帶打地轟"
                        +"出了尚書府！！\n"NOR,this_object(),who);
         who->move("/d/city2/ydmen");
         return 0;
        }

        if( query("money_id", ob) && ob->value() >= 10000000 )
        {
          message_vision(HIW"$N一張臉頓時笑顏大開：請稍侯，老夫為你進宮"
          +"走走。\n", this_object());
          this_object()->move("/d/city2/cddian");
          call_out("add_degree",10,who);
          return 1;
        } else
        {
          message_vision(HIY"$N大怒：給我滾出去！$n被一羣家將連推帶打地"
           +"轟出了尚書府！！\n"NOR, this_object(),who);
          who->move("/d/city2/ydmen");
          return 0;
        }
}