// 絕地末日·NPC: /d/suzhou/npc/meipo.c 只處理結婚與拜堂
// smallfish 修改2001.06

#include <ansi.h>
#define MARRY_RING      "/clone/misc/wedding-ring.c" 
#define RING_DIR        "/data/item/ring/" 

inherit NPC;

int do_marry(string);
int do_name(string);
int do_chase(object,object);
int do_ok(object,int);
int meipo_waiting(object,object,object);
int ready_marry(object,object,object);
int wait_marry(object,object,object);
int start_marry(object,object,object);
int go_lou(object,object);
int do_back(object);
int do_bai(string);
int do_right(object me, object ob);
int return_home(object);

void create()
{
        set_name("媒婆", ({ "meipo","po" }) );
        set("title", HIM""NOR);
        set("gender", "女性" );
        set("age", 43);
        set("long","一位精明能幹的老媒婆。\n");
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("inquiry", ([
                "結婚" : "媒婆笑眯眯地點頭道：“是啊... 要結婚(marry)當然要找我來做媒的呀！”\n",
                "marry" : "媒婆笑眯眯地點頭道：“是啊... 要結婚(marry)當然要找我來做媒的呀！”\n",
                "登記" : "媒婆笑眯眯地點頭道：“是啊... 要結婚(marry)登記當然要找我來做媒的呀！”\n",
                "離婚" : "媒婆臉色一變，有點勉強地笑道：“要...離婚(unmarry)？唉...！我可是看你們成婚的呀！\n"
                      "不過你們要是一定要離的話，那得去蘇州知府處辦理了！”\n",
                "unmarry" : "媒婆臉色一變，有點勉強地笑道：“要...離婚(unmarry)？唉...！我可是看你們成婚的呀！\n"
                      "不過你們要是一定要離的話，那得去蘇州知府處辦理了！”\n",
                "費用":"媒婆嘻嘻笑道：“結婚這麼大的事，花費的地方可不少，要50 gold，,而離婚\n"
                      "更要花費不少錢，所以要100 gold。”\n",
        ]) );
        set_skill("literate", 100);
        set_skill("dodge", 500);
        set_skill("unarmed", 300);
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me;
        int i;
        me=this_object();
        i=query("unmarried", me);
        
        ::init();
        if( query("unmarried", me) )
        {
delete("unmarried",                 me);
delete("married",                 me);
                if(i>2)
                {                
set("couple/married", 2,                         me);
                        message_vision("媒婆抬眼看了看$N説道：“你從前結了不少次的婚吧？現在新的婚姻法規定每人一生只許辦理\n"
                                "三次結婚手續，你嘛？唉！再給最後一次機會吧！再離婚，我這兒就不給你辦了！”\n",me);
                }
                else
set("couple/married", i,                         me);
        }
        add_action("do_marry", "marry");
        add_action("do_bai","拜");
        add_action("do_name","請");
}

int accept_object(object me, object ob)//交錢
{
        object meipo = this_object();
        
        if( !query("money_id", ob) )
             return notify_fail("媒婆嘻嘻笑道：“我老婆子有吃有喝不收什麼禮，您還是拿回去吧！”\n");
        if( !query_temp("ask_money", me))//由下面判斷交錢的人是否符合結婚條件。
                   return notify_fail("媒婆迷惑地問：“你想幹什麼？白給我錢？”\n");
          if( query_temp("marry/money", meipo))//已經有人交了錢了
                  return notify_fail("媒婆説：“等我忙完了一對再説。”\n");
          if(ob->value() < 500000)
                return notify_fail("媒婆皺了皺眉頭説道：“錢太少了吧？50 gold，結婚這麼大的事，再少就不行了。”\n");
        message_vision("媒婆接過錢對$N説：“這位"+RANK_D->query_respect(me)+"我可沒賺你的錢，呆會兒我還要張羅喜堂、還\n"
                   "要僱人、還有辦酒宴，搞不好我還得賠上一點的！而且我還可以幫你發請束，\n"
        "你可以輸入"HIC"‘請 <某人的中名>’"NOR"請你的朋友來參加婚禮。”\n",me);
set_temp("marry/money", me->name(),         meipo);//記錄給過錢的人
    log_file("money/MARRY",sprintf("%s(%s)結婚交錢in%s。\n",query("name", me),
query("id",                 me),ctime(time())));
          return 1;
}

int do_name(string target)//請客人
{
        object me,ob,dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();

        if (me->is_busy())
                return notify_fail("媒婆説道：“你忙完後再和我説話吧！”\n");
        if( ob->is_fighting()||me->is_fighting() )
                return notify_fail("媒婆説道：“現在沒功夫！”\n");
        if( !living(ob) )
                return notify_fail("你還是先想辦法把媒婆救醒吧。\n");
        if( query_temp("marry/money", ob) != me->name() )
      return notify_fail("媒婆眼睛斜了斜你：“你又沒交錢！”\n");
        if( query("marry/waiting_que", ob) )
                return notify_fail("媒婆笑笑説：“不要急，我的小喜鵲們還沒有飛回來呢！”\n");
        if( !target || target==" ")
                return notify_fail("媒婆抽出一張請柬寫了幾筆問：“你想請誰來參加你的婚禮？告訴我他(她)的名字！”\n");
        for(i=0; i<sizeof(all); i++)
        {
                if( query("env/invisibility", all[i]))continue;
                if( target == all[i]->name() || target == query("id", all[i]) )
                        dest = all[i];
        }
    if( !dest)
                return notify_fail("媒婆告訴你：“很遺憾，您想請的人他現在不在遊戲中！”\n");
        if (dest->is_ghost())
                   return notify_fail("媒婆婉惜地地告訴你：“據我們所知，您要請的人已經死了，您請節哀順便！”\n");
set("marry/waiting_que", 1,         ob);//等鵲
set("marry/me_name", me->name()+"("+query("id", me)+")",         ob);//主人名
        message_vision(HIG"媒婆一張喜柬上寫上幾個字，雙手一拍，從東廊就飛出一隻小喜鵲，銜着喜帖，\n"
                "撲愣愣地一下子消失在天空中了。\n" NOR,me);
        call_out("do_chase", 1, ob,dest);
        return 1;
}

int do_chase(object ob,object dest)//喜鵲送請柬
{
        object obj;

        if( !objectp(dest) || !environment(dest) )
        {
                call_out("do_ok",1,ob,1);//加一個失敗的參數回去
                return 1;
        }
        message_vision(HIY"\n天空中突然飛過來一隻花喜鵲，落在$N肩頭，將銜着的一張喜柬遞給$N。\n" NOR, dest);
        obj = new("/d/suzhou/npc/obj/xitie");
        obj->set_name(HIR+query("marry/me_name", ob)+"的結婚請帖"NOR);
        obj->move(dest);
        call_out("do_ok", 1, ob,0);
        return 1;
}

int do_ok(object ob,int flag)//喜鵲送柬成功回來
{
        if(flag)
                message_vision("花喜鵲從窗外撲楞楞地飛進來，落在媒婆身旁，媒婆哦了一聲説：“剛才的那個人沒找到，你先請其它人吧！”\n",ob);
        else
                message_vision("突然看見花喜鵲從窗外飛進來，落在媒婆身旁，媒婆笑眯眯地撫着花喜鵲的頭後\n"
                        "説道：“請柬剛才已經都送到了！您還想請誰？不想請了就開始結婚手續(marry <你的對象>)吧！”\n",ob);
  delete("marry/waiting_que",         ob);
delete("marry/me_name",         ob);
        return 1;
}

int do_marry(string arg) //判斷結婚
{
        object obj, me,ob,old_target;
        me = this_player();
        ob = this_object();
        if( query("marry/have_couple", ob) )
                return notify_fail("媒婆一愣：“啊！今天喜事這麼多？對不起，我把手頭這一對的婚事辦完，再給你辦吧！”\n");
        if( query("gender", me) == "無性" )
                return notify_fail("媒婆哼了一聲：“你無根無性，結個什麼婚？！”\n");
        if( (query("age", me)<18) && (query("gender", me) == "男性" )
                 || (query("age", me)<16) && (query("gender", me) == "女性") )
                return notify_fail("媒婆笑嘻嘻地説道：“你們現在還年輕，以後再説吧！”\n");
        if (me->is_busy())
                return notify_fail("媒婆説道：“你現在不是正忙着嗎？”\n");
        if( me->is_fighting(ob) )
        {
                if( !ob->is_killing(me) )
                        ob->kill_ob(me);
                return notify_fail("媒婆説道：“好，好，老孃送你去陰間成婚！”\n");
        }
        if( ob->is_fighting() )
                return notify_fail("媒婆説道：“沒看見這兒有人搗亂嗎！“\n");
        if( !living(ob) )
                return notify_fail("你還是先想辦法把媒婆救醒吧。\n");
        if( me->is_fighting() )
                return notify_fail("媒婆説道：嘿嘿，你先還是料理完你的朋友再説吧！\n");
        if( !environment() || base_name(environment()) != query("startroom"))
                return notify_fail("媒婆説道：“真抱歉，我現在很忙，請您等一會到紅娘堂來找我吧。”\n");
        if( query("class", me) == "bonze" || query("jobname", me) == "bonze" )
                return notify_fail("媒婆笑道：“哈哈！怎麼，信佛的也想開色戒了嗎?”\n");
        if( query("jobname", me) == "taoist" )
                return notify_fail("媒婆搖了搖頭道：“你修了道竟還是凡心不泯，唉！你要是真想，還是還了俗再來吧！”\n");
        if(!arg ||!objectp(obj = present(arg, environment(me))))
                return notify_fail("媒婆説道：“結婚可是要兩個人一起來的呀！”\n");
        if( query_temp("pending/pro", me) )
                return notify_fail("媒婆奇道：“咦？你的婚禮不是正在進行中嗎？還要問什麼？”\n");
        if( query_temp("pending/pro", obj) )
                return notify_fail("媒婆説道：“你想給別人攪局嗎？”\n");
        if( !obj->is_character() )
                return notify_fail("媒婆説道：“你這不是拿自己開涮嗎。”\n");

        if( mapp(query("couple", me)) )
        {
                if( query("couple/married", me)>2 )
                        return notify_fail("媒婆翻了翻姻緣簿，板下臉説道：“我早就跟你説過，怎麼又來了？\n"
                                "這次我實在不能幫你什麼了，你結婚次數太多了，按朝廷綱紀，是不準再給你們\n"
                                "辦結婚手續了，你們自己去做對野鴛鴦吧！\n");
                if( query("couple/have_couple", me) )
                {
                        if( obj == present(query("couple/couple_id", me),environment(me)) )
                                return notify_fail("媒婆奇道：“你們本來就是夫妻呀！幹嘛還要再來？”\n");
                        if( query("gender", me) == "女性" )
                                return notify_fail("媒婆説道：“你已經是有夫之婦了，這裏不允許重婚的。”\n");
                        else
                                return notify_fail("媒婆説道：“你已經是有婦之夫了，這裏不允許重婚的。”\n");
                }
        }
        if( mapp(query("couple", obj)) )
        {
      if( query("couple/married", obj)>2 )
              return notify_fail("媒婆翻了翻姻緣簿，歎了口氣道：“早跟你們説過，怎麼又離了，這\n"
              "次我實在不能幫你們什麼了，你是沒問題，但"+obj->name()+"結婚次數太多了，\n"
              "按朝廷綱紀，是不準再辦理結婚手續了，你們去做對野鴛鴦吧！\n");
             if( query("couple/have_couple", obj) )
                {
                        if( query("gender", obj) == "女性" )
                                return notify_fail("媒婆説道：可惜她已經是有夫之婦了，這裏不允許重婚的。\n");
                        else
                                return notify_fail("媒婆説道：可惜他已經是有婦之夫了，這裏不允許重婚的。\n");
                }
        }
        if( !living(obj) )
                return notify_fail("媒婆搖搖頭説道：“"+ obj->name()+"現在還沒清醒過來，我還不能確定你們雙方都是自願的。”\n");
        if(obj == me)
                return notify_fail("媒婆説道：“你這不是拿自己開涮嗎？”\n");
        if( query("gender", obj) == query("gender", me) )
                return notify_fail("媒婆驚道：“哇！你是同性戀？對不起，老婆子處理不了這事！”\n");
        if( !userp(obj) )
                return notify_fail("媒婆説道：“對不起，你只能和玩家結婚。”\n");
        if( query_temp("marry/money", ob) != me->name( )
                    && query_temp("marry/money", ob) != obj->name())//只要其中有一個人給過就行
           {
set_temp("ask_money", 1,                 me);
    set_temp("ask_money", 1,         obj);//表示條件符合，可以付錢，防止條件不符白付錢
                   return notify_fail("媒婆笑嘻嘻地道：結婚總要花一筆錢的嘍！要50 gold，不給錢，我可沒法給你辦！\n");
        }
        if( !query_temp("marry/answer", me) )
        {
                message_vision(HIG"媒婆攤開姻緣簿，絮絮叨叨地説道：“結婚是一輩子的終身大事，可不能\n"
                           "隨隨便便，否則，這世道就亂了。每個人只能在我這裏辦三次結婚手續。\n"
                        "讓我看看："HIC""+me->name()+"結過"+query("couple/married", me)+"次婚；"+obj->name()+"結過"+query("couple/married", obj)+"次婚；"
                        HIG"好的，\n最後，你們再認真考慮一下：是不是真心願意和對方結婚？”\n"NOR,me);
set_temp("marry/answer", 1,                 obj);
        }
        if( query_temp("pending/marry", obj) != me )
        {
                if( query("gender", obj) == "女性" )
                        message_vision(MAG "\n$N對著$n問道：“你願意嫁給我嗎？”\n\n"NOR, me,obj);
                else
                        message_vision(MAG "\n$N對著$n問道：“你願意娶我嗎？”\n\n"NOR, me,obj);

                if( objectp(old_target=query_temp("pending/marry", me)) && old_target != obj )
                        tell_object(old_target, YEL + me->name() +
                        "取消了和你結婚的念頭。\n" NOR);
set_temp("pending/marry", obj,                 me);
                if( query("gender", obj) == "女性" )
                        tell_object(obj, MAG "如果你願意嫁給他，請你也對" + me->name()
                        +"("+query("id", me)+")"+"下一次marry指令。\n"NOR);
                else
                        tell_object(obj, MAG "如果你願意娶她，請你也對" + me->name() +
                        "("+query("id", me)+")"+"下一次marry"+query("id", me)+"的指令。\n"NOR);
                write(MAG"現在你急切盼望着你的心上人説同意...\n" NOR);
                return 1;
        }
        message_vision(MAG "\n$N對著$n大聲説道：我願意！\n\n"NOR, me,obj);
        message_vision(MAG "媒婆呵呵笑道：“那就好，那就好，都跟我到東邊的姻緣堂來準備拜堂吧！”\n"
                "説完，媒婆一扭一扭地走進了東邊的大堂。\n" NOR, obj, me);
        me->delete_temp("ask_marry");//玩家取消問結婚的參數
        obj->delete_temp("ask_marry");//玩家取消問結婚的參數

        ob->delete_temp("marry/money");//媒婆取消交過錢的參數
set("marry/have_couple", 1,         ob);//媒婆在主持婚禮中
        ob->move("/d/suzhou/yinyuan-tang");

set_temp("pending/pro", 1,         me);
set_temp("pending/pro", 1,         obj);//婚禮中

set("couple/couple_name", obj->name(),         me);
set("couple/couple_id",query("id",  obj),         me);
set("couple/couple_name", me->name(),         obj);
set("couple/couple_id",query("id",  me),         obj);//正式結婚參數

        if( query("gender", obj) == "女性" )
        {
set("couple/couple_gender", "妻子",                 me);
set("couple/couple_gender", "丈夫",                 obj);
        }
        else
        {
set("couple/couple_gender", "妻子",                 obj);
set("couple/couple_gender", "丈夫",                 me);
        }
        call_out("meipo_waiting", 1,ob,me,obj);
         return 1;
}

int meipo_waiting(object ob,object me,object obj)//媒婆等拜堂
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say( "媒婆疑惑地説道：“小夫妻連拜堂也不急？難道真是有緣無份？唉，婚禮還是取消罷！\n"
              "老孃可是白賺了50 gold了，呵呵呵...”\n\n");
                call_out("do_back", 0, ob);
                return 1;
        }
        if( environment(ob)==environment(me)&&environment(ob)==environment(obj) )
        {                                                 //兩人都在
delete_temp("wait_time",                 ob);
                call_out("ready_marry", 1,ob,me,obj);
        }
        else
        {
                if( environment(ob)==environment(me)&&environment(ob)!=environment(obj) )
                {
                        if( random(10) == 0 )
                        say("\n媒婆問道：“"+me->name()+"！你去問問"+obj->name()+"怎麼還不過來？難道不願意了？\n");
addn_temp("wait_time", 1,                         ob);//其中一人obj不在
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                   else if( environment(ob)!=environment(me)&&environment(ob)==environment(obj) )
                {                                            //其中一人me不在
                        if( random(10) == 0 )
                        say("\n媒婆問道：“"+obj->name()+"！你去問問"+me->name()+"怎麼還不過來？難道不願意了？\n");
addn_temp("wait_time", 1,                         ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                else
                {
addn_temp("wait_time", 1,                         ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
        }
        return 1;
}

int ready_marry(object ob,object me,object obj)//準備婚禮
{
        object room,npc;

        if(!( room = find_object("/d/suzhou/yinyuan-tang")) )
        room = load_object("/d/suzhou/yinyuan-tang");

        message("vision", HIY "\n媒婆高聲叫道：“快快快，幹活的都出來了，馬上佈置喜堂！”\n" NOR, room);
        message("vision", HIC"\n只聽堂後響起一陣腳步聲，十幾個穿得五彩鮮豔衣服的少男少女嘻嘻哈哈地跑進來，\n"
                "嘰嘰喳喳地議論着，又分頭跑開了，時不時地笑着看一看"+me->name()+"和"+obj->name()+"。\n\n"NOR, room);
        say("媒婆對兩位新人説道：“不要着急，我們都是很有經驗的，很快就會佈置好的！”\n"
                CYN"只見身邊的人跑來跑去，忙得不得了。\n"NOR);
        call_out("wait_marry", 1, ob,me,obj);
        return 1;
}

int wait_marry(object ob,object me,object obj) //佈置喜堂
{
        object room,m_cloth,w_cloth;
        if(!( room = find_object("/d/suzhou/yinyuan-tang")) )
                room = load_object("/d/suzhou/yinyuan-tang");
addn_temp("wait_time", 1,         ob);
        switch(query_temp("wait_time", ob) )
        {
           case 0:
            say(RED"\n一個小傢伙跑過來，叫道：“媒婆，買紅紙的錢不夠了！”媒婆趕緊給他一些錢。\n\n"NOR);
                break;
        case 1:
             say(MAG"\n突然，那邊的小姑娘叫道：“媒婆，紅鴛鴦貼這邊正不正？”媒婆一看：“右邊再上去點！”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 2:
             say(CYN"\n四個傢伙哼喲嘿喲地抬着一隻大箱子從屋外你身邊走過，媒婆叮囑道：“慢些、輕點！”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 3:
                say("\n媒婆一把拉住身邊跑過的一個小夥子：“迎賓樓的喜宴訂了嗎？快去！”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 4:
                say(YEL"\n那邊的人叫道：“快拿火折來，把香燭點亮、點亮。”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 5:
             say("\n那邊又叫起來：“媒婆，給點錢打發送貨來的吧！”“來了！”媒婆趕緊跑過去。\n\n");
                 call_out("wait_marry", 1, ob,me,obj);
                break;
        case 6:
             say(CYN"\n媒婆一路小跑過來，看看新郎新娘的身材，點點頭回頭叫：“快，給新人準備喜裝。”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 7:
                  say(WHT"\n一幫人七手八腳地抬出了幾張大椅子，在中堂上掛了一個大大的\n"HIR
"                               ■      ■\n"
"                            ■■■■■■■■\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n"
"                              ◆◆    ◆◆\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
           case 8:
             say(YEL"\n嗩吶樂手開始調試歡快的樂曲，進進出出不少認識不認識的人，紛紛拱手相賀：“恭喜恭喜！”\n\n"NOR);
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 9:
                    say("\n幾個小姑娘笑嘻嘻地一邊擦着桌椅，一邊互相咬着耳朵，不時地偷眼看看新人。\n\n");
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 10:
                    say("\n兩位綵衣少女過來將一套大紅金邊滾龍袍遞給新郎，一套青邊戴花水雲袖交給新娘道：“有請新郎新娘穿喜裝”。\n\n");
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
                  call_out("wait_marry", 1, ob,me,obj);
                break;
        case 11:
                message("vision", HIY "\n媒婆高聲問了一聲：“都準備好了嗎？”眾人應道：“好了！”\n"
                "媒婆立刻拖長了聲音喊道：“有請月老主持婚禮……！”\n"
                HIM"頓時，鼓樂齊鳴，鞭炮大作，伴郎伴娘擁過來，七手八腳給新郎、新娘換上新衣，\n"
                        "綴擁着向大堂中央走去。\n"NOR, room);
                call_out("start_marry", 1, ob,me,obj);
                break;
   }
   return 1;
}

int start_marry(object ob,object me,object obj) //開始婚禮
{
        object moon,room;
        string msg;
        if(!(room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon=new("/d/suzhou/npc/yuelao");
        moon->move(room);
        message("vision", "\n隨着一陣哈哈大笑，一位紅面白鬚的老者，快步踱進堂中，在場的少年男女都躬身相拜：\n"
           "“恭請月老爺爺！”月老擺擺手，笑呵呵地看看"+me->name()+"和"+obj->name()+"，點點頭道：\n"
      "“好！好！郎才女貌，天作之合！天作之合呀！”\n"
           HIY"\n媒婆一揮手，喜樂又高起，只聽見月老高聲宣佈：“新郎…新娘…拜…天地……！”\n"NOR,room, moon);
        CHANNEL_D->do_channel(moon, "mudnews",
           sprintf("恭賀%s和%s喜結良緣，拜堂大禮即時開始！\n",me->name(),obj->name()));
        say("媒婆又小聲地對兩個新人説：“按順序輸入‘拜 天地、拜 高堂和拜 對方的名字’。”\n");
set_temp("pending/bai", 1,         me);
set_temp("pending/bai", 1,         obj);
        return 1;
}

int do_back(object ob)//結束
{
delete_temp("wait_time",         ob);
        ob->delete_temp("marry");//取消一切有關結婚的參數
        say("媒婆拍了拍身上，又一扭一扭地向西邊走去。\n");
        ob->move("/d/suzhou/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)//拜堂
{
        object me,ob,obj;
        string act;

        me = this_player();
        ob = this_object();
        if (me->is_busy())
                return notify_fail("媒婆説道：“你現在不是正忙着嗎？忙完再説！”\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("媒婆説道：“老孃好心給你辦婚事，你敢動武，送你去陰間成婚吧！”\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("媒婆説道：沒看見這兒有人搗亂嗎！\n");

        if( !living(this_object()) )
                return notify_fail("你還是先想辦法把媒婆救醒吧。\n");

        if( me->is_fighting() )
                return notify_fail("媒婆説道：“嘿嘿，你先還是料理完你的朋友再説吧！”\n");

        if( !environment()||base_name(environment()) != ("/d/suzhou/yinyuan-tang") )
                return notify_fail("媒婆説道：“你這人真是的，拜堂是要到姻緣堂才行的呀！”\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("媒婆笑道：“哈哈，你犯什麼傻呀！”\n");

        if( !objectp(obj=present(query("couple/couple_id", me),environment(me)) )
                 || !find_player(query("couple/couple_id", me)) )
        {
                message_vision("媒婆轉身一看，驚訝地説道：“唉呀！你的愛人怎麼突然跑了？婚禮怎麼舉行？大夥散攤吧。”\n"
                        "在一片惋惜聲，大家紛紛離場，喜堂上的東西也是一收而空。\n",me);
                call_out("do_back",1,ob);
                return 1;
        }
        if( arg == "天地" || arg == "高堂" || arg == ""+query("couple/couple_name", me) )
                return notify_fail("“拜”與後面的詞之間請用半角空格。\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "天地" )
                 || (query_temp("pending/bai", me) == 2 && arg != "高堂" )
                 || (query_temp("pending/bai", me) == 3 && arg != query("couple/couple_name", me)) )
                return notify_fail("媒婆笑道：“你亂拜什麼呀？一拜天地！二拜高堂！三拜你的愛人！可別再錯了！”\n");

        if( query_temp("pending/act", obj) != arg )
        {
                if( query_temp("pending/bai", me) != 3 )
                {
                        tell_object(obj, MAG"你的伴侶正等着和你拜 " + arg + " 呢...\n" NOR);
                        write(MAG "現在你正等待着你的伴侶...\n" NOR);
set_temp("pending/act", arg,                         me);
                }
                else
                {
                        tell_object(obj, MAG"你的伴侶正等着和你互拜（拜他的名字）呢...\n" NOR);
                        write(MAG "現在你正等待着你的伴侶...\n" NOR);
set_temp("pending/act", me->name(),                         me);
                }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
        {
                  message_vision("“一拜…天…地……”$N和$n在陣陣鼓樂聲中盈盈拜下......\n",me,obj);
addn_temp("pending/bai", 1,                 me);
addn_temp("pending/bai", 1,                 obj);
                return 1;
        }
        else if( query_temp("pending/bai", me) == 2 )
        {
                  message_vision("“二拜…高…堂……”$N和$n在站起來相視一笑，又緩緩拜下......\n",me,obj);
addn_temp("pending/bai", 1,                 me);
addn_temp("pending/bai", 1,                 obj);
                return 1;
        }
        else if( query_temp("pending/bai", me) == 3 )
        {
                  message_vision("“夫妻…對…拜……”$N和$n在相互深深拜了一拜......\n",me,obj);
                message_vision(HIY "月老笑呵呵地説道：“好，$N和$n，現在正式結為夫妻! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf( "恭喜%s和%s，一對璧人喜結良緣。\n        各位親朋好友，可攜禮到蘇州迎賓樓參加他們的婚宴！\n", me->name(), obj->name()));

addn("couple/married", 1,                 me);//結婚次數
set("couple/have_couple", 1,                 me);//處於已婚狀態
set_temp("married_party", 1,                 me);//做上記號，喜來福老闆看到就會同意開酒席
set_temp("married_party", 1,                 obj);//兩人都做，但只有男性才有用
addn("couple/married", 1,                 obj);//結婚次數
set("couple/have_couple", 1,                 obj);//已婚狀態

delete_temp("pending/bai",                 me);
delete_temp("pending/bai",                 obj);
delete_temp("pending/act",                 me);
delete_temp("pending/act",                 obj);
delete_temp("pending/pro",                 me);
delete_temp("pending/pro",                 obj);
     delete_temp("ask_money",         me);
delete_temp("ask_money",                 obj);
                call_out("do_right",1,me,obj);
                call_out("last_marry",1,ob,me,obj);
                return 1;
        }
}

int do_right(object me, object ob)
{
        string fn;
        string fc;
        object ring;

        message("visoin", name() + "笑着對二人説：“今個兒是你們" 
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
        ring = load_object(fn);
        ring->move(ob, 1);
        tell_object(ob, HIY "你獲得了一個結婚戒指。\n" NOR);
        set("can_summon/"+"weddingring", fn, ob);
        
        // record
        set("couple/witness", name(), me);
        me->save();
        set("couple/witness", name(), ob);
        ob->save();
        return 1;
}
int last_marry(object ob,object me,object obj)//拜堂結束
{
        object moon,room;
        if(!(room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon = present("yue lao", room);
        moon->move("/u/smallfish/workroom");
delete_temp("wait_time",         ob);
delete_temp("marry/money",         ob);
        say("媒婆喊道：“轎伕！快將新人送到迎賓樓舉行婚宴，我和月老就不去了，呵呵！”\n説完一扭一扭地向西邊走去。\n");
     write_file("/log/money/MARRY",sprintf("%s(%s)and%s(%s)marriedin%s。\n",query("name", me),query("id", me),
query("name",                 obj),query("id", obj),ctime(time())));
delete("have_couple",         ob);
        ob->move("/d/suzhou/hongniang-zhuang");
        message_vision(HIR"伴郎伴娘擁着兩位新人，上了門口的兩頂大紅花轎，只聽轎伕們一聲“起轎！”\n"
                   "一行人吹吹打打地奔向迎賓樓......\n"NOR,me,obj);
        me->move("/d/suzhou/jiao1");
        obj->move("/d/suzhou/jiao2");
        call_out("go_lou",8,me,obj);
        return 1;
}

int go_lou(object me,object obj)
{
        object npc;
        message_vision("\n    過了好長一會兒，只聽轎伕們一聲“到啦！”轎子整個兒一震，想是落到了地上，\n"
           "$N和$n從轎子中下來一看，原來已經到了迎賓樓。兩人又被擁扶着一直上了二樓福滿堂。\n"
      "只聽一陣呵呵笑聲，迎賓樓老闆喜來福笑容滿面地迎出來：“恭喜兩位新人！恭喜恭喜！”\n",me,obj);
        npc=new("/d/suzhou/npc/xi-laifu");
set("name1", me->name(),         npc);
set("name2", obj->name(),         npc);//雙方姓名
        npc->move("/d/suzhou/xifu-tang");
        me->move("/d/suzhou/xifu-tang");
        obj->move("/d/suzhou/xifu-tang");
        return 1;
}

int return_home(object home)//覆蓋標準繼承中的該函數，防止婚禮中更新，媒婆回家
{
    if( !environment()||  environment()==home ) return 1;
        if( !living(this_object()) ||  is_fighting()) return 0;
        if( query("marry", this_object()))return 0;//有結婚的參數就不回去

    message("vision", this_object()->name() + "急急忙忙地離開了。\n",
            environment(), this_object());
    return move(home);
}