// llm 99/06/04 修改2000.09
// updated by lonely 11/03
// hongniang.c 紅娘

#include <ansi.h>

#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR        "/data/item/ring/"

inherit NPC;

int waiting(object ob);
int do_name(string target);
int do_chase(object ob);
int do_ok(object ob);
int meipo_waiting(object ob, object me, object obj);
int ready_marry(object ob, object me, object obj);
int wait_marry(object ob, object me, object obj);
int start_marry(object ob, object me, object obj);
int do_back(object ob);
int do_bai(string arg);
int ask_baitang();

void create()
{
        set_name("紅娘", ({ "hong niang", "hongniang", "marriage witness" }));
        set("long", 
                "她是一個長得很好看的小姑娘，忽閃忽"
                "閃的大眼睛透著一絲狡黠。\n");
        set("gender", "女性");
        set("age", 18);
        set("str", 200);
        set("combat_exp", 1000);

        set("inquiry", ([
                "結婚": "要結婚？我可以為你們做媒啊，你們人都來齊了麼？",
                "離婚": "結婚找我，離婚我也幫忙，不過可以慎重哦。一日夫妻百日恩嘛！",
                "拜堂": (: ask_baitang :),
        ]));

        setup();
        seteuid(getuid());
}

void init()
{
           add_action("do_bai", "拜");
        add_action("do_name", "請");
        add_action("do_name", "qing");
}

int accept_object(object me, object ob) 
{
           if( !query("money_id", ob) || !query("couple/id", me) || 
               !query_temp("ask_money", me) )
                     return notify_fail("紅娘嘻嘻笑道：“我老婆子有吃有喝不收什麼禮，您還是拿回去吧！”\n");

          if (ob->value() < 10000000)
                      return notify_fail("紅娘皺了皺眉頭說道：“錢太少了吧？1000 gold，如果是結婚這麼大的事，再少就不行了。”\n");
              
        message_vision("紅娘接過錢對$N說：“這位" + RANK_D->query_respect(me) + "我可沒賺你的錢，呆會兒我還要張羅喜堂、還\n"
                          "要雇人、還有辦酒宴，搞不好我還得賠上一點的！而且我還可以幫你發請束，\n"
                        "你可以輸入‘請 <某人的中名>’。”\n", me);
        set_temp("marry/money", me->name(), this_object());
        command("say 你先告訴我你要請(qing)哪些人吧，如果不想請朋友，那麼就準備拜堂(ask hong niang about 拜堂)吧！");
          return 1;
}

int do_name(string target)
{
        object me, ob, dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();
                  
           if (query_temp("marry/money") != me->name())
           {
                   message_vision(name() + "笑嘻嘻地道：結婚總要花一筆錢的嘍！" 
                                  "要 1000 gold，不給錢，我可沒法給辦！\n", me);
                   return 1;
           }
           
        if (me->is_busy())
                return notify_fail("紅娘說道：“你忙完後再和我說話吧！”\n");
                
        if (ob->is_fighting() || me->is_fighting())
                return notify_fail("紅娘說道：“現在沒功夫！”\n");
                
        if (! living(ob))
                return notify_fail("你還是先想辦法把紅娘救醒吧。\n");
                
        if( query_temp("marry/money", ob) != me->name() )
                      return notify_fail("紅娘斜了斜你：“你又沒交錢！”\n");
                      
        if( query("waiting_target", ob) )
                return notify_fail("紅娘笑笑說：“不要急，我的小喜鵲們還沒有飛回來呢！”\n");
                
        if (! target || target == " ")
                return notify_fail("紅娘抽出一張請柬寫了幾筆問：“你想請誰來參加你的婚禮？告訴我他(她)的名字！”\n");
                
        for (i = 0; i < sizeof(all); i++)
        {
                if( target == all[i]->name() || target == query("id", all[i]) )
                        dest = all[i];
        }
        
        if (! dest)
                return notify_fail("紅娘告訴你：“很遺憾，您想請的人他現在不在遊戲中！”\n");
                
        if (dest->is_ghost())
                   return notify_fail("紅娘婉惜地地告訴你：“據我們所知，您要請的人已經死了，您請節哀順便！”\n");
                   
        set("waiting_target",query("id",  dest), ob);
        set("me_name",query("name",  me), ob);
        set("me_id",query("id",  me), ob);
        message_vision(HIG "紅娘一張喜柬上寫上幾個字，雙手一拍，從東廊就飛出一只小喜鵲，銜著喜帖，\n"
                          "撲愣愣地一下子消失在天空中了。\n" NOR, me);
        call_out("do_chase", 1, ob);
        return 1;
}

int do_chase(object ob)
{
        object dest, obj;
        dest=find_player(query("waiting_target", ob));

        if (! objectp(dest) || ! environment(dest))
        {
                call_out("waiting", 0, ob);
                return 1;
        }
        
        message_vision(HIY "天空中突然飛過來一只花喜鵲，落在$N肩頭，將銜著的一張喜柬遞給$N。\n" NOR, dest);
        obj = new("/adm/npc/obj/xitie"); 
           set("name", HIR+query("me_name", ob)+"("+query("me_id", ob)+")"+"的結婚請帖"NOR, obj);
        obj->move(dest);
        call_out("do_ok", 0, ob);
        return 1;
}

int waiting(object ob)
{
        object dest;
        dest=find_player(query("waiting_target", ob));

        if (objectp(dest) && dest->is_ghost())
        {
                delete("waiting_target", ob);
                call_out("do_ok", 1, ob);
                return 1;
        }
        remove_call_out("waiting");
        call_out("waiting", 60, ob);
           return 1;
}

int do_ok(object ob)
{
        message("vision", "突然看見花喜鵲從窗外飛進來，落在紅娘身旁，紅娘笑眯眯地撫著花喜鵲的頭後\n"
                "說道：“請柬剛才已經都送到了！您還想請誰？不想請了就開始結婚其他手續(ask hong niang about 拜堂)吧！”\n", 
                environment(), ob);
          delete("waiting_target", ob);
        delete("me_name", ob);
        delete("me_id", ob);
        return 1;
}

int ask_baitang()
{
        object me, obj, 
        
        ob = this_object();
        me = this_player();
        
           if (query_temp("marry/money") != me->name() || ! mapp(query("couple", me))) 
        {
                tell_object(me, "紅娘迷惑不解的看著你！\n");
                return 1;
        }
                
        if( !(obj=present(query("couple/id", me),environment(me))) )
        {
                tell_object(me, "你的伴侶不在啊！\n");
                return 1;
        }
        
        message("vision", MAG "\n紅娘呵呵笑道：“那就好，那就好，都跟我到東邊的姻緣堂來準備拜堂吧！”\n"
                "說完，紅娘一扭一扭地走進了東邊的大堂。\n" NOR, me, obj);    
                   
           ob->move("/d/suzhou/yinyuan-tang");
        call_out("meipo_waiting", 1, ob, me, obj);
        return 1;
}

int meipo_waiting(object ob, object me, object obj) 
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say("紅娘疑惑地說道：“小夫妻連拜堂也不急？難道真是有緣無份？唉，婚禮還是取消罷！\n"
                          "老娘可是白賺了1000 gold了，呵呵呵...”\n\n");
                call_out("do_back", 0, ob);
                      return 1;
        }
        if (environment(ob) == environment(me) && environment(ob) == environment(obj))
           {                                                
                      delete_temp("wait_time", ob);
                   call_out("ready_marry", 1, ob, me, obj);
           }
        else
           {
                if (environment(ob) == environment(me) && environment(ob) != environment(obj))
                {
                        if (random(10) == 0)
                                say("\n紅娘問道：“" + me->name() + "！你去問問" + obj->name() +
                                    "怎麼還不過來？難道不願意了？\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                }
                   else if (environment(ob) != environment(me) && environment(ob) == environment(obj))
                {                                            
                        if (random(10) == 0)
                                say("\n紅娘問道：“" + obj->name() + "！你去問問" + me->name() +
                                    "怎麼還不過來？難道不願意了？\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                }
                else
                      {
                           addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                      }
           }
        return 1;
}

int ready_marry(object ob, object me, object obj)
{
        object room;

        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");

        message("vision", HIY "\n紅娘高聲叫道：“快快快，幹活的都出來了，馬上布置喜堂！”\n" NOR, room);
        message("vision", HIC "\n只聽堂後響起一陣腳步聲，十幾個穿得五彩鮮艷衣服的少男少女嘻嘻哈哈地跑進來，\n"
                "嘰嘰喳喳地議論著，又分頭跑開了，時不時地笑著看一看" + me->name() + "和" + obj->name() + "。\n\n" NOR, 
                room);
        say("紅娘對兩位新人說道：“不要著急，我們都是很有經驗的，很快就會布置好的！”\n"
               CYN "只見身邊的人跑來跑去，忙得不得了。\n"NOR);
        call_out("wait_marry", 1, ob, me, obj);
           return 1;
}

int wait_marry(object ob, object me, object obj) 
{
        object room;
        object m_cloth, w_cloth;
        
        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        
        switch(query_temp("wait_time", ob) )
        {
           case 0:
                    say(RED "\n一個小家伙跑過來，叫道：“紅娘，買紅紙的錢不夠了！”紅娘趕緊給他一些錢。\n\n" NOR);
                   set_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                   break;
              case 1:
                     say(MAG "\n突然，那邊的小姑娘叫道：“紅娘，紅鴛鴦貼這邊正不正？”紅娘一看：“右邊再上去點！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
              case 2:
                     say(CYN "\n四個家伙哼喲嘿喲地抬著一只大箱子從屋外你身邊走過，紅娘叮囑道：“慢些、輕點！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 3:
                      say("\n紅娘一把拉住身邊跑過的一個小伙子：“喜福堂的喜宴訂了嗎？快去！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
              case 4:
                     say(YEL "\n那邊的人叫道：“快拿火折來，把香燭點亮、點亮。”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                   break;
        case 5:
                     say("\n那邊又叫起來：“紅娘，給點錢打發送貨來的吧！”“來了！”紅娘趕緊跑過去。\n\n");
                      addn_temp("wait_time", 1, ob);
                 call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 6:
                     say(CYN "\n紅娘一路小跑過來，看看新郎新娘的身材，點點頭回頭叫：“快，給新人準備喜裝。”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 7:
                  say(WHT "\n一幫人七手八腳地抬出了幾張大椅子，在中堂上掛了一個大大的\n" HIR
"                               ■      ■\n"
"                            ■■■■■■■■\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n"
"                              ◆◆    ◆◆\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n\n" NOR);
                addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
           case 8:
                     say(YEL "\n嗩吶樂手開始調試歡快的樂曲，進進出出不少認識不認識的人，紛紛拱手相賀：“恭喜恭喜！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 9:
                    say("\n幾個小姑娘笑嘻嘻地一邊擦著桌椅，一邊互相咬著耳朵，不時地偷眼看看新人。\n\n");
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                break;
        case 10:
                    say("\n兩位彩衣少女過來將一套大紅金邊滾龍袍遞給新郎，一套青邊戴花水雲袖交給新娘道：“有請新郎新娘穿喜裝”。\n\n");
                    m_cloth = new("/d/suzhou/npc/obj/longpao");
                    w_cloth = new("/d/suzhou/npc/obj/yunxiu");
                    if( query("gender", me) == "男性" )
                    {
                            m_cloth->move(me);
                            w_cloth->move(obj);
                    }
                    else
                    {
                            m_cloth->move(obj);
                            w_cloth->move(me);
                    }
                addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
                break;                
        case 11:
                message("vision", HIY "\n紅娘高聲問了一聲：“都準備好了嗎？”眾人應道：“好了！”\n"
                              "紅娘立刻拖長了聲音喊道：“有請月老主持婚禮……！”\n"
                              HIM "頓時，鼓樂齊鳴，鞭炮大作，伴郎伴娘擁過來，七手八腳給新郎、新娘換上新衣，\n"
                              "綴擁著向大堂中央走去。\n" NOR, room);
                      call_out("start_marry", 1, ob, me, obj);
                      break;
           }
           return 1;
}

int start_marry(object ob, object me, object obj) 
{
        object moon, room;

        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon = new("/d/suzhou/npc/yuelao");
           moon->move(room);
        message("vision", "\n隨著一陣哈哈大笑，一位紅面白須的老者，快步踱進堂中，在場的少年男女都躬身相拜：\n"
                   "“恭請月老爺爺！”月老擺擺手，笑呵呵地看看" + me->name() + "和" + obj->name() + "，點點頭道：\n"
                      "“好！好！郎才女貌，天作之合！天作之合呀！”\n"
                   HIY "\n紅娘一揮手，喜樂又高起，只聽見月老高聲宣布：“新郎…新娘…拜…天地……！”\n" NOR, room, moon);
           say("紅娘又小聲地對兩個新人說：“按順序輸入‘拜 天地、拜 高堂和拜 對方的名字’。”\n");
           CHANNEL_D->do_channel(moon, "mudnews",
                                 sprintf("恭賀%s和%s喜結良緣，拜堂大禮即時開始！\n", me->name(), obj->name()));
        set_temp("pending/bai", 1, me);
           set_temp("pending/bai", 1, obj);
        return 1;
}

int do_back(object ob)
{
           delete_temp("wait_time", ob);
           delete_temp("marry/money", ob);
        say("紅娘拍了拍身上，又一扭一扭地向西邊走去。\n");
           ob->move("/d/suzhou/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)
{
        object me, ob, obj;

        me = this_player();
           ob = this_object();
        if (me->is_busy())
                return notify_fail("紅娘說道：“你現在不是正忙著嗎？忙完再說！”\n");

        if (me->is_fighting(this_object()))
        {
                if (! this_object()->is_killing(me))
                        this_object()->kill_ob(me);
                return notify_fail("紅娘說道：“老娘好心給你辦婚事，你敢動武，送你去陰間成婚吧！”\n");
        }

        if (this_object()->is_fighting())
                return notify_fail("紅娘說道：沒看見這兒有人搗亂嗎！\n");

        if (! living(this_object()))
                return notify_fail("你還是先想辦法把紅娘救醒吧。\n");

        if (me->is_fighting())
                return notify_fail("紅娘說道：“嘿嘿，你先還是料理完你的朋友再說吧！”\n");

        if (! environment() || base_name(environment()) != ("/d/suzhou/yinyuan-tang"))
                return notify_fail("紅娘說道：“你這人真是的，拜堂是要到姻緣堂才行的呀！”\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("紅娘笑道：“哈哈，你犯什麼傻呀！”\n");

        if( !objectp(obj=present(query("couple/id", me),environment(me)) )
         || !find_player(query("couple/id", me)) )
        {
                   message_vision("紅娘轉身一看，驚訝地說道：“唉呀！你的愛人怎麼突然跑了？婚禮怎麼舉行？大伙散攤吧。”\n"
                                     "在一片惋惜聲，大家紛紛離場，喜堂上的東西也是一收而空。\n", me);
                      call_out("do_back", 1, ob);
                      return 1;
           }

           if( arg == "天地" || arg == "高堂" || arg == ""+query("couple/name", me) )
                return notify_fail("“拜”與後面的詞之間請用半角空格。\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "天地" )
         || (query_temp("pending/bai", me) == 2 && arg != "高堂" )
         || (query_temp("pending/bai", me) == 3 && arg != query("couple/name", me)) )
                return notify_fail("紅娘笑道：“你亂拜什麼呀？一拜天地！二拜高堂！三拜你的愛人！可別再錯了！”\n");

        if( query_temp("pending/act", obj) != arg )
        {
                      if( query_temp("pending/bai", me) != 3 )
                      {
                        tell_object(obj, MAG "你的伴侶正等著和你拜 " + arg + " 呢...\n" NOR);
                        write(MAG "現在你正等待著你的伴侶...\n" NOR);
                        set_temp("pending/act", arg, me);
                      }
                      else
                      {
                        tell_object(obj, MAG "你的伴侶正等著和你互拜（拜他的名字）呢...\n" NOR);
                        write(MAG "現在你正等待著你的伴侶...\n" NOR);
                        set_temp("pending/act", me->name(), me);
                      }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
           {
                  message_vision("“一拜…天…地……”$N和$n在陣陣鼓樂聲中盈盈拜下......\n", me, obj);
                      addn_temp("pending/bai", 1, me);
                      addn_temp("pending/bai", 1, obj);
                      return 1;
           }
        else if( query_temp("pending/bai", me) == 2 )
           {
                  message_vision("“二拜…高…堂……”$N和$n在站起來相視一笑，又緩緩拜下......\n", me, obj);
                      addn_temp("pending/bai", 1, me);
                      addn_temp("pending/bai", 1, obj);
                      return 1;
           }
        else if( query_temp("pending/bai", me) == 3 )
           {
                  message_vision("“夫妻…對…拜……”$N和$n在相互深深拜了一拜......\n", me, obj);
                message_vision(HIY "月老笑呵呵地說道：“好，$N和$n，現在正式結為夫妻! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf("恭喜%s和%s，一對璧人喜結良緣。\n            各位親朋好友，可攜禮到汝州喜福堂參加他們的婚宴！\n",
                                me->name(), obj->name()));
                                
                      set_temp("married_party", 1, me);//做上記號，喜來福老板看到就會同意開酒席
                      set_temp("married_party", 1, obj);//兩人都做，但只有男性才有用

                      delete_temp("pending/bai", me);
                      delete_temp("pending/bai", obj);
                      delete_temp("pending/act", me);
                      delete_temp("pending/act", obj);

                   call_out("last_marry", 1, ob, me, obj);
                return 1;
           }
}

int last_marry(object ob, object me, object obj)
{
        object moon, room;
        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon = present("yue lao", room);
        moon->move("/u/lonely/workroom");
           delete_temp("wait_time", ob);
           delete_temp("marry/money", ob);
        say("紅娘喊道：“轎夫！快將新人送到喜福堂舉行婚宴，我和月老就不去了，呵呵！”\n說完一扭一扭地向西邊走去。\n");
           ob->move("/d/suzhou/hongniang-zhuang");
        message_vision(HIR "伴郎伴娘擁著兩位新人，上了門口的兩頂大紅花轎，只聽轎夫們一聲“起轎！”\n"
                          "一行人吹吹打打地奔向喜福堂......\n" NOR, me, obj);
           me->move("/d/suzhou/jiao1");
           obj->move("/d/suzhou/jiao2");
        call_out("go_lou", 8, ob, me, obj);
        call_out("do_back", 10, ob);
        return 1;
}

int go_lou(object ob,object me,object obj)//到酒樓
{
        object room, npc;
        
        if (! (room = find_object("/d/suzhou/xifu-tang")))
                room = load_object("/d/suzhou/xifu-tang");
                
        message_vision("\n    過了好長一會兒，只聽轎夫們一聲“到啦！”轎子整個兒一震，想是落到了地上，\n"
                   "$N和$n從轎子中下來一看，原來已經到了喜福堂。兩人又被擁扶著一直上了二樓福滿堂。\n"
                      "只聽到一陣呵呵笑聲，喜福堂老板喜來福笑容滿面地迎出來：“恭喜兩位新人！恭喜恭喜！\n”", me, obj);
                      
           npc = new("/d/suzhou/npc/xi-laifu");
           set("name1", me->name(), npc);
           set("name2", obj->name(), npc);//雙方姓名
           npc->move(room);
           me->move(room);
           obj->move(room);
           return 1;
}

int do_witness(object me, object ob)
{
        message_vision("$N含情脈脈的望著$n，真是柔情似水，過了良久才對" +
                       name() + "道：這位小姑娘能否為我們証婚？\n\n",
                       me, ob);
                       
        if (! living(ob))
        {
                message_vision(name() + "吃吃的掩嘴而笑，對$N道：我"
                               "看你還是先把這位弄醒再說吧。\n", me);
                return 1;
        }

        if (! userp(ob))
        {
                message_vision(name() + "滿臉都是苦笑，笑啥"
                               "呢？你也呵呵的跟著傻笑。\n", me);
                return 1;
        }

        message_vision(name() + "大聲喊道：“很好啊，好得很！俗"
                       "話說：“在天願為比翼鳥，在地願成連理枝。”\n" +
                       "促成良緣是天大的美事！我" + name() + "最願意了，問題是這位" +
                       RANK_D->query_respect(ob) + "也願意嗎？”\n\n", me);

        tell_object(ob, YEL + name() + "悄聲問你：" + me->name(1) +
                        "在向你求婚呢，你答應(right)還是不答應(refuse)？\n" NOR);
        ob->set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
        ob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));
        set_temp("pending/engage", ob, me);
        return 1;
}

int do_right(object me, object ob)
{
        string fn;
        string fc;
        object ring;

        message_vision("$N偷偷看了看$n，使勁的點頭道：我願意，願意極了！\n" + name() +
                       "聽了，笑嘻嘻道：“兩廂情願，又有我這媒人，那還不好辦嗎？”\n\n",
                       me, ob);
        command("chat 恭喜" + me->name(1) + "和" + ob->name(1) +
                 "成為百年之好！");
        message("visoin", name() + "笑著對二人說：“今個兒是你們"
                "大喜的日子，我沒有什麼禮物，只好送給你"
                "們這對新人一對結婚戒指吧！”\n\n", environment(me));

        fc = read_file(MARRY_RING);
        fc = replace_string(fc, "LONG_DESCRIPTION",
                            "這是" + me->name(1) + "和" +
                            ob->name(1) + "的結婚戒指，是兩人的定情之物。\n");

        // give ring to me
        fn=RING_DIR+query("id", me);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        VERSION_D->append_sn(fn + ".c");
        ring = load_object(fn);
        ring->move(me, 1);
        tell_object(me, HIY "你獲得了一個結婚戒指。\n" NOR);
        set("can_summon/"+"weddingring", fn, me);

        // give ring to ob
        fn=RING_DIR+query("id", ob);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        VERSION_D->append_sn(fn + ".c");
        ring = load_object(fn);
        ring->move(ob, 1);
        tell_object(ob, HIY "你獲得了一個結婚戒指。\n" NOR);
        set("can_summon/"+"weddingring", fn, ob);
        
        // record
        set("couple/id",query("id",  ob), me);
        set("couple/name", ob->name(1), me);
        set("couple/witness", name(), me);
        me->save();
        set("couple/id",query("id",  me), ob);
        set("couple/name", me->name(1), ob);
        set("couple/witness", name(), ob);
        ob->save();
        set_temp("ask_money", 1, me);
        set_temp("ask_money", 1, ob);
        tell_object(me, HIR "你們如果想把這次結婚搞的風光點，你只要給我 1000 gold，我可以幫你們張羅所有的事情。\n" NOR);
        tell_object(ob, HIR "你們如果想把這次結婚搞的風光點，你只要給我 1000 gold，我可以幫你們張羅所有的事情。\n" NOR);
        return 1;
}

int do_refuse(object me, object ob)
{
        message_vision("$N瞥了$n一眼，轉過頭去不再看，連吐了"
                       "幾口，“呸、呸、我呸呸呸！”\n" +
                       name() + "無奈的對$n道：“你也看到了，"
                       "俗話說強扭的瓜不甜啊...”\n", me, ob);
        return 1;
}

int do_divorce(object me)
{
        object ob;

        if( query("couple/witness", me) != name() )
        {
                message_vision(name() + "搖搖頭，對$N道：“我可"
                               "不是你們的媒人，你們要離就離，別來煩我！”\n", me);
                return 1;
        }

        ob=find_player(query("couple/id", me));
        if (! ob || environment(ob) != environment(me))
        {
                message_vision(name() + "吃驚的看著$N道：“怎麼，吵"
                               "架了？唉，花無百日好啊！不過要離你怎"
                               "麼也得把人家找來一起談談啊！”\n", me);
                return 1;
        }

        if (! living(ob))
        {
                message_vision(name() + "搖搖頭，對$N道：“我說這位" +
                               RANK_D->query_respect(me) +
                               "，怎麼也得等人家醒過來再說吧！”\n", me);
                return 1;
        }

        if( query_temp("pending/submit_divorce", me) )
        {
                message_vision(name() + "搖搖頭，對$N道：“你著"
                               "什麼急，也不看看人家的意思？”\n",
                               me);
                return 1;
        }

        if( !query_temp("pending/submit_divorce", ob) )
        {
                message_vision(name() + "輕輕嘆了口氣，一張幼稚的臉上也"
                               "不禁有些滄桑，回頭看了看$n，問道：“你"
                               "也是鐵了心不和" + ob->name() + "過了？”\n\n", me, ob);
                tell_object(ob, YEL + name() + "悄悄的告訴你：要是那樣，你就輸入("
                                "divorce"+query("id", me)+")表示決心已定。\n");
                set_temp("pending/submit_divorce", 1, me);
                return 1;
        }

        message_vision(name() + "痛心的對$N和$n道：“當初我為你們"
                       "兩個做媒的時候，可真沒想到會有這麼一天！”\n\n", me, ob);
        command("chat 從今天起" + me->name(1) + "和" + ob->name(1) +
                "分手了，以後可就各走各的路啦！");
        UPDATE_D->clear_user_data(query("id", me),"couple");
        return 1;
}

int accept_fight()
{
        command("fear");
        command("say 別來，我好怕怕的。");
        return notify_fail("你還是算了吧！\n");
}

int accept_hit()
{
        command("say 不要啊！不要亂動手！");
        return notify_fail("你還是算了吧！\n");
}

int accept_kill()
{
        command("say 呀！你想幹什麼？");
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 不好了！出人命了！");
        message_vision("$N飛也似的逃走了。\n", this_object());
        destruct(this_object());
}

int return_home(object home) // 防止婚禮中更新，紅娘回家
{
        if (! environment() || environment() == home) 
                return 1;
        if (! living(this_object()) ||  is_fighting()) 
                return 0;
        if( query_temp("wait_time", this_object()) )
                return 0; // 有結婚的參數就不回去

        message("vision", this_object()->name() + "急急忙忙地離開了。\n",
                    environment(), this_object());
        return move(home);
}
