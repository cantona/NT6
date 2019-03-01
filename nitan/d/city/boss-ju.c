// liumang.c 流氓
#include <ansi.h>

inherit NPC;

#define PLACE "yz"     //揚州
#define TYPE  "bad"    //黑道
#define WAIT_TIME 60    //完成不了任務的反省時間

string *fail_xc_msg1=({
        "place你查看了沒有？",
        "你有沒有看一下place？",
        "難道place就不用巡查了？",
        "去place再看看！",
        "你別把place給拉下啊，",
        "place是一個很重要的地方，不能不查看一下，",
        "你沒有去巡查place吧？",
});

string *fail_xc_msg2=({
        "你這算什麼巡城！",
        "你這就回來了？",
        "巡城怎麼可以這麼草率啊！",
        "不要總想著偷懶！",
        "你辦事情也太不認真了吧。",
        "這也能算巡城啊，當我老的管不了你了？",
        "別偷懶！",
        "做事情要踏踏實實！",
});

mapping bang_bad = ([
        "name" : "小刀會",
        "id"   : "xdh",
        "place": "yz",
        "boss" : "鞠老大",
]);

void create()
{
	set_name("鞠老大", ({ "ju laoda", "laoda" }));
	set("gender", "男性");
	set("age", 23);
	set("long", "他是一個長得很英俊的男子，看上去風流倜儻，讓人無法相信他就本城地頭蛇" + bang_bad["name"] + "的首領。\n");
	set("title",HIW"揚州小刀會總首領"NOR);
       set("nickname",HIY"天下第一大色狼"NOR);
       set("per",29);
	set("combat_exp", 1000000);
	set("shen_type", -1);

	set("attitude", "peaceful");
	
	set_skill("unarmed", 20);
	set_skill("dodge", 20);
	set_temp("apply/attack", 10);
	set_temp("apply/defense", 10);

	setup();
	carry_object("/clone/misc/cloth")->wear();
	add_money("silver",2);
}

void init()
{
       add_action("do_join","join");
       add_action("do_disengage","disengage");
       add_action("do_choose","choose");
       add_action("do_giveup","giveup");
}

int do_join()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if( query("bang_bad", me) )
       {
               if( query("bang_bad/name", me) == bang_bad["name"] )
               {
                       if( query("shen", me)>0 )
                       {
                               message_vision("$N對著$n勃然大怒：好你個兔崽子，沒事偏偏要去冒充什麼正人君子！\n",obj,me);
                               delete("bang_bad", me);
                               msg = "聽說" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                               CHANNEL_D->do_channel(this_object(), "rumor", msg);
                               return notify_fail("你被" + obj->name() + "開除出了" + bang_bad["name"] + "。\n");
                       }
                       return notify_fail("你已經是我"+query("bang_bad/name", me)+"的成員了，昏頭了？\n");
               }
               return notify_fail("你現在是"+query("bang_bad/name", me)+"的成員，要加入我"+bang_bad["name"]+"，得先脫離(disengage)原來的幫會。\n");
       }
       
       if( query("bang_good", me) || query("shen", me)>0 )
       {
               message_vision("$N上上下下的仔細打量著$n，臉色越來越難看。\n",obj,me);
               command("say " + "你這種自命正派人士的到我這裡來幹什麼？想找茬子？");
               return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
       }

       if( query("combat_exp", me)<10000 )
       {
               command("joke"+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，你還太嫩了點，先鍛煉鍛煉然後再出來跟我混。");
               return notify_fail("看來" + obj->name() + "覺得你實在太嫩了點。\n");
       }

       if( query("combat_exp", me) >= 600000 )
       {
               command("joke"+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，您身手這麼高了，我這種小幫會怎能留住你。");
               return notify_fail("看來" + obj->name() + "覺得你等級太高了。\n");
       }

       set("bang_bad", bang_bad, me);
       message_vision("$N單膝跪下，對著$n恭恭敬敬的喊了聲：老大！\n",me,obj);
       message_vision("$N微微一笑，對著$n點了點頭，擺手讓$n站起身來。\n",obj,me);
       tell_object(me,"恭喜你成為" + bang_bad["name"] + "的成員！\n");
       msg = "聽說" + me->name(1) + "拜" + obj->name(1) + "為老大，加入了" + bang_bad["name"];
       CHANNEL_D->do_channel(this_object(), "rumor", msg);
       return 1;
}

int do_disengage()
{
       string msg;
       object me,obj;
       me = this_player();
       obj = this_object();

       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔細打量著$n，臉色越來越難看。\n",obj,me);
               command("say " + "你這種自命正派人士的到我這裡來幹什麼？想找茬子？");
               return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
       }

       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bang_bad["name"] + "的成員啊！");
               return notify_fail("看來" + obj->name() + "給你搞的滿頭霧水。\n");
       }

       if( query("bang_bad/boss", me) != bang_bad["boss"] )
               return notify_fail("想脫離我小刀會？找你的介紹人"+query("bang_bad/boss", me)+"去吧。\n");

       delete("bang_bad", me);

       if( query("shen", me)>0 )
       {
               message_vision("$N對著$n勃然大怒：好你個兔崽子，沒事偏偏要去冒充什麼正人君子！\n",obj,me);
               delete("bang_bad", me);
               tell_object(me,"你被" + obj->name() + "開除出了" + bang_bad["name"] + "。\n");
               msg = "聽說" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
               CHANNEL_D->do_channel(this_object(), "rumor", msg);
       } else
       {
               message_vision("$N對著$n嘆氣道：早就知道你不會在這種小地方混一輩子的，也罷，你自己保重！\n",obj,me);
               delete("bang_bad", me);
               tell_object(me,"你決定脫離" + bang_bad["name"] + "。\n");
       }
       return 1;
}

int do_choose(string bh)
{
       string msg;
       mapping bang_quest;
       object me,obj;

       me = this_player();
       obj = this_object();

       //如果是白道的，就趕走
       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔細打量著$n，臉色越來越難看。\n",obj,me);
               command("say " + "你這種自命正派人士的到我這裡來幹什麼？想找茬子？");
               return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
       }

       //如果不是本幫會的，不給領取任務
       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bang_bad["name"] + "的成員啊！");
               return notify_fail("看來" + obj->name() + "給你搞的滿頭霧水。\n");
       }

       //如果是本幫會，但是變成了正神，那麼如果是本人收錄的成員，將其開除；否則，將其趕走
       if( query("shen", me)>0 )
       {
               message_vision("$N對著$n勃然大怒：好你個兔崽子，沒事偏偏要去冒充什麼正人君子！\n",obj,me);
               if( query("bang_bad/boss", me) == bang_bad["boss"] )
               {
                       message_vision("$N對著$n怒喝道：留你在我" + bang_bad["name"] + "豈非叫人笑話！\n",obj,me);
                       delete("bang_quest", me);
                       delete("bang_bad", me);
                       msg = "聽說" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("你被" + obj->name() + "開除出了" + bang_bad["name"] + "。\n");
               } else
               {
                       message_vision("$N對著$n怒喝：還不給我快滾！\n",obj,me);
                       return notify_fail("你沒有從" + obj->name() + "那裡領取到任何任務，反而挨了一頓臭罵。\n");
               }
       }

       //如果已經有任務在身，就痛罵一頓
       if( query("bang_quest", me) )
               return notify_fail(obj->name() + "生氣的看著你說：你剛才領的任務還沒有完成，急什麼？\n");

       //如果沒有輸入編號，則提示指令
       if (!bh)
               return notify_fail(obj->name() + "奇怪的看著你，你想領取什麼任務？指令是：choose <編號>。\n");
 
       //如果是追殺任務，則不需要領取任務
       if (bh[0..1] == "zs")
               return notify_fail(obj->name() + "微微一笑，既然是追殺令，還用領取任務？趕緊去完成吧！\n");

       //如果是巡城，則看玩家是否加入的本地幫會
       if( bh == "xc" && query("bang_bad/place", me) != bang_bad["place"] )
               return notify_fail(obj->name() + "對你擺了擺手說：巡城這種事情，我本城的兄弟就可以勝任，不勞你大駕了！\n");

       //如果這個NPC正BUSY，則不給任務
       if (obj->is_busy())
               return notify_fail(obj->name() + "正忙著呢，你稍微等一下。\n");

       //如果這個玩家剛放棄過任務，需要等待
       if( time()-query("last_bang_quest", me)<query("need_wait_time", me) )
               return notify_fail("完成不了任務，先好好反省一下，然後再來領取任務！\n");

       //檢查該編號的任務是否存在
       bang_quest = PARTY_QUEST_D->query_city_quest(PLACE,TYPE,bh);

       if (!bang_quest)
               return notify_fail(obj->name() + "翻開簿子看了看，對你說：目前沒有" + bh + "這個任務。\n");

       //如果是巡城任務，則檢查當天是否已經有人在巡城
       if (bang_quest["id"] == "xc" && !bang_quest["enable"])
               return notify_fail(obj->name() + "微微笑著說：今天已經有兄弟去巡城了，你就等改天吧！\n");

       //給任務，並且將該任務從列表中刪除 
       obj->start_busy(1);
       PARTY_QUEST_D->delete_city_quest(PLACE,TYPE,bh);
       set("bang_quest", bang_quest, me);
       message_vision("$N對著$n點了點頭：那麼這個任務就交給你了，好好去幹！\n",obj,me);
       tell_object(me,"你接的任務是：\n" + bang_quest["msg"] + "\n");
       return 1;
}

int do_giveup()
{
       string msg;
       object me,obj;

       me = this_player();
       obj = this_object();

       //如果是白道的，就趕走
       if( query("bang_good", me) )
       {
               message_vision("$N上上下下的仔細打量著$n，臉色越來越難看。\n",obj,me);
               command("say " + "你這種自命正派人士的到我這裡來幹什麼？想找茬子？");
               return notify_fail("看來" + obj->name() + "並不歡迎你！\n");
       }

       //如果不是本幫會的，不理會
       if( !query("bang_bad", me) || query("bang_bad/name", me) != bang_bad["name"] )
       {
               command("yi"+query("id", me));
               command("say 這位" + RANK_D->query_respect(me) + "，你並非我" + bang_bad["name"] + "的成員啊！");
               return notify_fail("看來" + obj->name() + "給你搞的滿頭霧水。\n");
       }

       //如果是本幫會，但是變成了正神，那麼如果是本人收錄的成員，將其開除；否則，將其趕走
       if( query("shen", me)>0 )
       {
               message_vision("$N對著$n勃然大怒：好你個兔崽子，沒事偏偏要去冒充什麼正人君子！\n",obj,me);
               if( query("bang_bad/boss", me) == bang_bad["boss"] )
               {
                       message_vision("$N對著$n怒喝道：留你在我" + bang_bad["name"] + "豈非叫人笑話！\n",obj,me);
                       delete("bang_quest", me);
                       delete("bang_bad", me);
                       msg = "聽說" + me->name(1) + "被" + obj->name(1) + "逐出了" + bang_bad["name"];
                       CHANNEL_D->do_channel(this_object(), "rumor", msg);
                       return notify_fail("你被" + obj->name() + "開除出了" + bang_bad["name"] + "。\n");
               } else
               {
                       message_vision("$N對著$n怒喝：還不給我快滾！\n",obj,me);
                       return notify_fail("你被" + obj->name() + "狠狠的痛罵了一番。\n");
               }
       }

       if( !query("bang_quest", me) )
               return notify_fail(obj->name() + "奇怪的看著你說：你現在並沒有任務在身啊，是不是閒的發慌了？\n");

       delete("bang_quest", me);
       message_vision("$N對著$n一個勁的嘆氣，似乎不明白為什麼$n為何如此的不成材。\n",obj,me);
       tell_object(me,obj->name() + "沖你瞪了一眼：這點小事情都完成不了，一邊去好好反省反省！\n");

       //記錄放棄時間
       set("last_bang_quest", time(), me);

       //如果玩家沒有連續完成任務的次數記錄，則累加該玩家需要等待的時間，最多WAIT_TIME秒，否則，等待3秒
       if( !query_temp("finish_bang_times", me) )
              set("need_wait_time",query("need_wait_time",  me)+3, me);
       else set("need_wait_time", 3, me);

       if( query("need_wait_time", me)>WAIT_TIME)set("need_wait_time", WAIT_TIME, me);

       //清除連續完成任務的次數
       delete_temp("finish_bang_times", me);
       return 1;
}

int accept_object(object who,object me,object ob)
{
       int exp,pot,score,weiwang;
       mapping bang_quest,bonus;
       object env;
       string *place,the_place,msg;

       if (base_name(ob) != "/d/city/npc/obj/yaopai")
               return notify_fail(who->name() + "不屑的把" + ob->name() + "拋還給你：什麼爛東西也給我？\n");

       if( !query("bang_quest", me) )
               return notify_fail(who->name() + "朝你點了點頭，沒有說什麼話。\n");

       bang_quest=query("bang_quest", me);

       if (bang_quest["id"] != "xc" || bang_quest["name"] != "巡揚州城")      
               return notify_fail(who->name() + "朝你點了點頭，沒有說什麼話。\n");

       place = bang_quest["place"];

       if (sizeof(place))
       {
               the_place = place[random(sizeof(place))];
               env = get_object(the_place);
               msg = fail_xc_msg1[random(sizeof(fail_xc_msg1))];
               msg = replace_string(msg,"place",env->short());
               msg += fail_xc_msg2[random(sizeof(fail_xc_msg2))];
               return notify_fail(who->name() + "生氣的對你說：" + msg + "\n");
       }

       message_vision("$N高興的拍了拍$n的肩膀：幹的好！\n",who,me);
       exp = bang_quest["bonus"]; 
       pot = exp/(2+random(2)); 
       weiwang = 5 + random(10); 
       score = 5 + random(10); 
       delete("bang_quest", me);
       addn_temp("finish_bang_times", 1, me);
       bonus = ([ "exp" : exp, 
                  "pot" : pot, 
                  "score" : score, 
                  "weiwang" : weiwang, 
                  "prompt": "在巡揚州城的過程中，經過鍛煉" 
               ]);
       QUEST_D->delay_bonus(me, bonus);
       destruct(ob);
       return 1;
}