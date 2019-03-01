// person used in quest
#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

object jiufen_object = 0;
string jiufen_name = "";
string quest_ob = "";

string *say_msg = ({
"$N沖著$n憤怒的說：趕緊把我的obj_name還給我，否則對你不客氣！",
"$N指著$n的鼻子對大家說：你們來評評道理，這個臭賊去年拿走了我的obj_name，到現在還不還給我！",
"“碰”的一聲，卻是一張板凳給$N踹了老高，又落在$n的身邊，空氣中濃濃的火藥味。",
"$N死命的盯著$n，腳開始微微顫抖，似乎隨時都會踹出去。",
"$N咬咬牙，把手插進褲兜，似乎要掏出把什麼東西來，看到$n冷冷的目光，卻又空手抽了出來。",
"$N越說越激動：obj_name是我當初最好朋友留下的唯一遺物，給$n騙走後至今未歸還給我。",
"$N咬牙切齒的看著$n，當初說好是借一個星期，現在過了一年了怎不見你還給我？",
"$N滿臉不屑的看著$n，你真是一個大騙子！",
"$N怒火沖天的吼：就算是弄丟了你也得給我找回來！吐沫星子噴了$n滿臉。",
"$N一屁股坐地上，撒賴似的對著$n哼哼：不把東西還給我，以後我就吃你的喝你的用你的。",
"$N眼睛瞪得和香爐一樣大：$n你這個騙子，我不把你扁得滿臉冒血，你就不知道花兒~為什麼,那!樣!紅!!!~~",
"只見$N一個箭步，“啪....啪....啪”轉眼間已經在$n的屁股上留下十幾個腳印。",
"$N沖$n的鼻樑狠狠的打了一拳，然後$n眼淚嘩啦嘩啦流了一臉盆。",
"$N看著$n的滿臉的姦笑憤聲暗罵道：“他奶奶的！！！”",
"$N打了$n一記響亮的耳光。",
"$N真想$n去死。",
"$N對$n正色道：“直娘賊，你可不要自尋死路！”",
"$N對著$n陰陰的笑：你不把obj_name還給我，你就別想有好日子過！",
});

string *reply_msg = ({
"$N沖著$n故作茫然地說：你說什麼obj_name啊？我怎麼聽不懂哦？",
"$N指著$n的鼻子對大家說：你看看他這種窮酸樣，會是一個有obj_name的人麼？",
"“碰”的一聲，卻是一張板凳給$N踹了老高，又落在$n的身邊，空氣中濃濃的火藥味。",
"$N冷冷的盯著$n的腳，生怕它突然踹過來。",
"$N的火氣也越來越大：$n你口口聲聲說是我好朋友，不就是一個破爛obj_name，也值得你這樣？",
"$N越說越激動：obj_name本來就是我父親給$n的，現在回到我手裡也是很正常的嘛。",
"$N咬牙切齒的看著$n，就你這態度，還想我把obj_name還給你？做夢去吧！",
"$N滿臉不屑的看著$n，對付你這種豬頭豬腦的土包子，還用講什麼道理？",
"$N怒火沖天的吼：$n你給我聽著，別說我現在沒有obj_name，就算有也不會給了你！",
"$N看著$n突然嘻嘻的笑：你急啊，你叫啊，我就是不給你，你能怎的？吃了我？",
"$N眼睛瞪得和香爐一樣大：$n你這個臭小子，我不把你扁得滿臉冒血，你就不知道花兒~為什麼,那!樣!紅!!!~~",
"只見$N一個箭步，“啪....啪....啪”轉眼間已經在$n的屁股上留下十幾個腳印。",
"$N沖$n的鼻樑狠狠的打了一拳，然後$n眼淚嘩啦嘩啦流了一臉盆。",
"$N看著$n的怒氣沖天的樣子，突然哈哈一笑，翹起二郎腿慢慢的喝香茶。",
"$N打了$n一記響亮的耳光。",
"$N真想$n去死。",
"$N對$n正色道：“直娘賊，你可不要自尋死路！”",
"$N對著$n陰陰的笑：想我把obj_name還給你，除非跪下來給我磕三個響頭！",
});

void set_quest_ob(string arg);
void set_jiufen_object(object ob);
int  accept_object(object who, object ob);
int  leave();
int  is_stay_in_room()        { return 1; }
void heart_beat();
void destruct_me();
string ask_me();

void create()
{
        ::create();
        set("gender",query("gender"));
        set("age", 30 + random(30));
        if (arrayp(query("from")) && sizeof(query("from")))
                set("long",query("from")[random(sizeof(query("form")))] + "\n據說這次重入江湖乃是因為跟人有了糾紛。\n");
        else
                set("long","據說這次重入江湖乃是因為跟人有了糾紛\n");


        set("attitude", "friendly");
        set("chat_chance", 30);
        set("scale", 150);
        set_temp("apply/armor", 50);
        set_temp("apply/damage", 50);
        set_temp("born_time", time());
        set("inquiry", ([
                 "調解" : (: ask_me :),
         ]) );
        set_heart_beat(10);
}

void set_quest_ob(string arg)
{
       quest_ob = arg;
       return;
}

void set_jiufen_object(object ob)
{
       jiufen_object = ob;
       jiufen_name = ob->name();
       return;
}

int accept_fight(object ob)
{
        command("say 你我之間又沒什麼糾紛，湊啥熱鬧！");
        return notify_fail("你滿臉羞愧，取消了跟" + this_object()->name() + "比試的念頭！\n");
}

int accept_kill(object ob)
{
        command("say 怎麼說？你也來欺負我？");
        command("cry");
        return notify_fail("剎那間你只覺得下不了手。\n"); 
}

int accept_hit(object ob)
{
        command("say 怎麼說？你也來欺負我？");
        command("cry");
        return 0;
}

int accept_touxi(object ob)
{
        tell_object(ob,"你剛想偷襲，突然發現" + this_object()->name() + "防備很嚴謹。\n"); 
        return 1;
}

int accept_ansuan(object who) 
{
        return notify_fail("你剛想暗算，可是發現" + this_object()->name() + "非常小心謹慎，讓你無從下手。\n"); 
} 

void heart_beat()
{
       mapping msg;
       string msg1,msg2;

        if (time() - query_temp("born_time") > 900)
        {
                message_vision("$N哭鬧了半天，感覺沒什麼意思，訕訕的走了。\n", this_object());
                destruct_me();
                return;
        }

       if (!objectp(jiufen_object) || 
           !living(jiufen_object) ||
           !environment(this_object()) || 
           !environment(jiufen_object) ||
           environment(this_object()) != environment(jiufen_object))
        {
                message_vision("$N哼了一聲，恨恨的罵道：這個縮頭烏龜，今天我暫且先走了，下次再來！\n", this_object());
                destruct_me();
                return;
        }

       //如果已經開始調節糾紛，則停止吵架
       if (query_temp("on_tiaojie")) 
       {
              message_vision("$N對著$n哼了一聲。\n",this_object(),jiufen_object);
              message_vision("$n惱怒的瞪著$N，看上去正在強忍著心頭的怒氣。\n",this_object(),jiufen_object);
              return;
       }

       msg1 = say_msg[random(sizeof(say_msg))];
       msg2 = reply_msg[random(sizeof(reply_msg))];
       msg1 = replace_string(msg1,"obj_name",quest_ob);
       msg2 = replace_string(msg2,"obj_name",quest_ob);
       message_vision(msg1 + "\n",this_object(),jiufen_object);
       message_vision(msg2 + "\n",jiufen_object,this_object());
       return;
}

void destruct_me()
{
       message_vision("$N轉身離開了。\n",this_object());
       destruct(this_object());
       return;
}

int accept_object(object who,object ob)
{
       int exp,pot,weiwang,score;
       mapping b;

        if (ob->is_character() || ob->is_item_make())
                // 不接受人物和自造的兵器
                return 0;

       if( !query("bunch_quest", who) || 
           query("bunch_quest/type", who) != "調解糾紛" || 
           query("bunch_quest/ob", who) != this_object() )
               return notify_fail("你小子送我這個東西幹什麼？蒙我？\n");

       if( query("name", ob) != quest_ob )
       {
               command("angry");
               command("say TNND,拿這個破玩意來糊弄我？我要的是" + quest_ob + "，找不到就別來充老大！");
               return 0;
       }

       exp=query("bunch_quest/bonus", who);
       exp += random(exp);
       pot = exp/(2+random(1));
       weiwang = 5 + random(10);
       score = 5 + random(10);

       delete("bunch_quest", who);
       addn_temp("finish_bunch_times", 1, who);
       command("wa"+query("id", who));
       command("leyun"+query("id", who));
       command("spank"+query("id", who));
       command("say 既然這位" + RANK_D->query_respect(who) + "如此仗義，那我也沒話好說了，兄弟這次先告辭了，後會有期！");

       b = ([ "exp" : exp,
               "pot" : pot,
               "score" : score,
               "weiwang" : weiwang,
               "prompt": "在幫助" + jiufen_name + HIG "調解糾紛的過程中，經過鍛煉"
           ]);

       QUEST_D->delay_bonus(who, b);

       remove_call_out("destruct_me");
       call_out("destruct_me",0);

       return 1;
}

string ask_me()
{
       object who;
       who = this_player();
       if( !query("bunch_quest", who) || 
           query("bunch_quest/type", who) != "調解糾紛" || 
           query("bunch_quest/ob", who) != this_object() )
               return "你是誰？在一邊JJYY的煩不煩，給我滾遠點，這裡沒你的事！";
       
       set_temp("on_tiaojie", 1, this_object());
       return "調解？用什麼來調解？莫非你還能幫我把" + quest_ob + "找回來啊！";
}