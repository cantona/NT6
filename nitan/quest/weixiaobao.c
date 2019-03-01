// quest_wei/wei.c
// Modified by Zeratul Jan 5 2001
// Modified by Sir 5/17/2001 
// 10個任務一輪,獎勵累加,增加兩個任務之間的時間限制，恢復用錢取消的功能
// 500個一輪，獎勵根據完成數增加
inherit NPC;
#include <ansi.h>;
#include <quest.h>
#define GIFT_DIR "/clone/gift/"

void special_bonus(object me, object who,string type);
string time_period(int timep,object me);
int do_answer(string arg);
int do_cancel();
int do_fangqi();
string do_gonglao();
#define MAX_BAOWU_EXP 10000000
#define MAX_NEED 1000000  //100gold取消
int is_manager() {return 1;}

void create()
{
  set_name("韋小寶", ({ "wei xiaobao", "wei", "xiaobao" }));
  set("title", HIC"大清國撫遠大將軍"HIY"一等鹿鼎公"NOR);
  set("nickname", HIW"小白龍"NOR);
  set("gender", "男性");
  set("age", 18);
  set("str", 20);
  set("int", 30);
  set("con", 30);
  set("dex", 20);
  set("per", 28);
  set("long", 
"這位少年將軍頭戴紅頂子，身穿黃馬褂，眉花眼笑，賊忒兮
兮，左手輕搖羽扇，宛若諸葛之亮，右手倒拖大刀，儼然關
雲之長，正乃韋公小寶是也。見你看著他，“哈哈哈”，仰
天大笑三聲，學足了戲文中曹操的模樣，你頓時忍不住湊個
趣，問一句：“將軍為何發笑？”\n");
  set("combat_exp", 50000);
  set("shen_type", 1);
  set("attitude", "peaceful");
  set("max_qi", 2500);
  set("max_jing", 1000);
  set("neili", 500);
  set("max_neili", 500);
  set("jiali", 50);

  set_skill("force", 20);
  set_skill("parry", 20);
  set_skill("hand", 20);
  set_skill("dodge", 20);
  set_skill("shenxing-baibian", 20);
  set_skill("yunlong-shengong", 20);
  set_skill("qianye-shou", 90);

  map_skill("force", "yunlong-shengong");
  map_skill("parry", "qianye-shou");
  map_skill("dodge", "shenxing-baibian");
  map_skill("hand", "qianye-shou");
  prepare_skill("hand", "qianye-shou");
  set("inquiry", ([
      "天地會" : "別煩我！\n",
      "陳近南" : "那是我師父！\n",
      "茅十八" : "就是那十八個毛蟲啊？他還沒死吧！\n",
      "獨臂神尼": "那是我美貌尼姑師父！\n",
      "韋春芳" : "我娘做婊子生意越來越差了，現在改行作老鴇了！\n",
      "康熙"   : "那是我皇帝師父！\n",
      "小玄子" : "那是我皇帝師父！\n",
      "小桂子" : "別提這個名字了，我怕怕！\n",
      "阿珂"   : "她是我明媒正娶的大老婆！\n",
      "雙兒"   : "你認識她？大功告成，親個嘴兒！\n",
      "曾柔"   : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
      "方怡"   : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
      "蘇荃"   : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
      "沐劍屏" : "我老婆你問那麼多幹嘛？皇上洪福齊天，我艷福齊天！\n",
      "建寧公主" : "這個騷娘皮，親厚不及雙兒、美貌不及阿珂、武功不及蘇荃、機巧不及方怡、天真純善不及沐劍屏、溫柔斯文不及曾柔，差有一日之長者，不過橫蠻潑辣而已！\n",
      "取消任務":  (: do_cancel :),
      "cancel" :   (: do_cancel :),
      "功勞"   :   (: do_gonglao :),
      "gonglao":   (: do_gonglao :),
//      "放棄"：  (:do_fangqi:),
//      "fangqi": (:do_fangqi:),
  ]) );

  setup();
  carry_object(CLOTH_DIR"jinduan")->wear();
}

void init()
{
  object ob;

  ::init();
  add_action("give_quest", "quest");
}
int do_cancel()
{ 
  object who=this_player();
  if (who->query("quest_wei/finished")==1)
  {
    tell_object(who,"韋小寶笑道：你沒有領任務啊，有什麼好取消的。\n");
    return 1;
  }
  if (who->query("balance")<1000000)
  {
    tell_object(who,"韋小寶笑道：你就這點微薄家產，還是好好找一下我要的東西吧。\n");
    return 1;
  }
  who->add("balance",-1000000); 
  tell_object(who,"韋小寶笑道：好好，我就收你一些黃金做為補償。你也不用再辛苦了，下去休息休息吧。\n");
  who->set("quest_wei/finished",1);
  who->delete( "quest_wei/time" );
  return 1;
}
string do_gonglao()
{
  if (this_player()->query("quest_num/wei"))
  return "你已經連續幫我收集到"+chinese_number(this_player()->query("quest_num/wei"))+"樣東西了。";
  else
  return "你沒有幫我做過什麼事情啊。";
}

int do_fangqi()
{
  object who=this_player();
  return 0; 
}
//int do_answer(object ob,object me,string arg)
int accept_reply(object me,object ob,string arg)
{
  object obj;
  string un;
  int meili,gift,ans;
  string type;
  string need;
  int mysc;
  
  if (!me->query_temp("quest_gift/got")||!stringp(type = me->query_temp("quest_gift/type")))   return 0;
  if (arg=="Y" || arg=="y" || arg=="yes")  ans=1;
  else if (arg=="N" || arg=="n" || arg=="no") ans=2;
  else return 0;
  if (living(me) && living(ob) && ans==1)
  {
                me->delete_temp("quest_gift/got");
                type = me->query_temp("quest_gift/type");
                if (type == "meili") 
                {
                        need = "江湖魅力";
                        mysc = me->query("meili");
                }
                else if (type == "gongxian") 
                {
                        need = "門派貢獻";
                        mysc = me->query("family/gongji");
                }
                if ( mysc < me->query_temp("quest_gift/need") )
                        return notify_fail("你就這麼點"+need+"，也好意思問"+ob->name()+"要東西？\n");
      message_vision(CYN "\n$N" CYN "急忙點點頭，說道：這東西正好我也需要，就交給我吧。\n" NOR, me);
      arg=me->query_temp("quest_gift/obj");
      obj = new(arg);
      if (!objectp(obj))
        return notify_fail(ob->name()+"納悶道：咦？我的東西呢？剛才還在，怎麼轉眼就沒了。\n");
      if (obj->query("base_unit"))
         un = obj->query("base_unit");
      else
         un = obj->query("unit");
      if (type == "gongxian")
              me->add( "family/gongji", - me->query_temp("quest_gift/need"));
      else 
              me->add(type, - me->query_temp("quest_gift/need"));
      message_vision("$N微微一笑，拿出一" + un + obj->name() + NOR "交給$n。\n" NOR,ob,me);
      obj->move(me);
      log_file("gift/wei_give",sprintf("[%s]%8s give %8s %20s \n",ctime(time()),ob->query("id"),me->query("id"),base_name(obj)));
      return 1;
    }
    else if (living(me) && living(ob) && ans==2)
      {
        me->delete_temp("quest_gift/got");
        tell_object(me,HIW+ob->name()+"嘆氣道：也罷，既然你不需要，這東西我"
                                       "就留給別人吧。\n"NOR);
        return 1;
      }
      return 0;
}

int give_quest()
{
  mapping quest;
  object me = this_player();
  int combatexp, timep, factor;
  int num;

  combatexp = (int) (me->query("combat_exp"));
  if(combatexp<1000)
  {
    tell_object(me,"韋小寶對你哼了一聲道：“辣塊媽媽，東西還沒長齊想幹嘛？”\n");
    return 1;
  }
/*  if(combatexp>10000000)
  {
    tell_object(me,"韋小寶對你哼了一聲道：“辣塊媽媽，花差大爺我忙著呢，沒空理你！”\n");
    return 1;
  }
*/  if (me->query("meili") < 0 || me->query("weiwang") < 0)
  {
    tell_object(me,"韋小寶對你哼了一聲道：“你是個什麼東西，也來這裡搗亂。\n");
    return 1;
  }
  if (me->query("combat_exp") <= me->query("quest_wei/busy_exp"))
  {
    tell_object(me,"韋小寶對你說道：我暫時不需要你幫忙，你先去其它地方歷練一下再來。\n");
    return 1;
  }
  if (me->query_temp("quest_gift/got"))
  {
     tell_object(me,"韋小寶對你說道：我正問你話呢，你快點回答(answer y|n)啊。\n");
      return 1;
    }
// Let's see if this player still carries an un-expired task
  if( me->query("quest_wei/quest") && !me->query( "quest_wei/finished" ) )
  {
    if( ((int) me->query("quest_wei/time")) > time() )
    {
      tell_object(me,"韋小寶對你笑道：說你不行吧，還不服氣？\n");
      return 1;
    }
    else
    {
      tell_object(me,"韋小寶對著你嘆了一口氣：沒關系去拿別的也成。\n");
//      me->add("qi",-(int)(me->query("qi")/5));
//      quest_failed( me, "wei" );

//      tell_object(me,HIW"韋小寶對你說道：不是讓你去拿『"+me->query("quest_wei/quest")+HIW+"』嗎？時間已經過了，我要的東西呢。\n"NOR);
//      return 1;
    }
  }
  else
//    if ( me->query("quest_wei/time") + 90 + random(60) > time())   
      if ( me->query("quest_wei/time") + 2 > time())   
    {
      tell_object(me,"韋小寶對你微微一笑道：你過于勞累，歇息會兒再上路吧。\n");
      return 1;
    }

//  factor=10;
    if(!me->query("quest_num/wei") || 
    (int)me->query("quest_num/wei")<0 ||
    (int)me->query("quest_num/wei")>500)
      me->set("quest_num/wei",1); //給人物第quest_num/wei個任務

  num=me->query("quest_num/wei");
  if(num <= 5)
    quest = __DIR__"qwlist1"->query_quest("easy_quest");
  else if ( num%50 == 0)
  {
    quest = __DIR__"qwlist1"->query_quest("hard_quest");
    tell_object(me,"韋小寶微微一笑：做得不錯嘛，看來我可以托付你個難一些的任務。\n");
  } 
  else
    quest = __DIR__"qwlist1"->query_quest("normal_quest");
  timep = random(10) * 60 + 15*60;
  
  tell_object(me,HIW "韋小寶吩咐道：給你在" + time_period(timep, me) + "內");
  tell_object(me,"找到『"+quest["quest"]+HIW"』給我，我會好好謝你。\n" NOR);

  quest["quest_type"] = "尋";
//  quest["exp_bonus"] = 10 + random(10);
//  quest["pot_bonus"] = 2 + random(4);
//  quest["score"] = 2 + random(4);

  me->set("quest_wei/quest", quest["quest"]);
  me->set("quest_wei/time", (int)time()+timep);
//  me->set("quest_wei/factor",factor);
  me->set( "quest_wei/finished",0 );
  me->set("quest_wei/quest_type",quest["quest_type"]);
  me->delete("quest_wei/busy_exp");
//  if(!me->query_temp("wei_quest_num") ||
//    (int)me->query_temp("wei_quest_num")==10)
//    me->set_temp("wei_quest_num",1);
//  if ((int)me->query_temp("wei_quest_num")<0) 
//    me->set_temp("wei_quest_num",1);
//add by sega 4/11/2000
//  me->set("last_quest_time",(int)time());
//  me->add("quests/require", 1);
  return 1;
}

string time_period(int timep, object me)
{
  int t, d, h, m, s;
  string time;
  t = timep;
  s = t % 60; t /= 60;
  m = t % 60; t /= 60;
  h = t % 24; t /= 24;
  d = t;

  if(d) time = chinese_number(d) + "天";
  else time = "";

  if(h) time += chinese_number(h) + "小時";
  if(m) time += chinese_number(m) + "分";
  time += chinese_number(s) + "秒";

  return time;
}

int accept_object(object who, object ob)
{
  int exp, pot, score, num,level, myexp;
  mapping quest;
  object gift;
  int need;

  if (ob->query("id") == "bao wu")
  {
    if (who->query_temp("baowunum") < 0)    
            return notify_fail("去去去，哪兒找的假貨，想來蒙韋爵爺我？！\n");               
    if (ob->query("owner") != who->query("id") )
    {
      tell_object(who,HIW"韋小寶高興地說，我正想要" + ob->query("name")+ HIW"呢，多謝你把別人的寶物轉送給我。\n"NOR);
    }
    else
    {
      exp = 10 + random(10);
      pot = 7 + random(5);
      score= 5 + random(10);
      who->add("score",score);
      who->add_temp("baowunum",-1);
      who->add("marks/baowu",1);
      tell_object(who,HIW"韋小寶高興地說，我正想要" + ob->query("name")+ HIW"呢，蒙你見愛，我也送你些東西吧。\n");
     if ((who->query("combat_exp") < MAX_BAOWU_EXP)  || who->query_temp("invite"))
      {
        who->add("combat_exp",exp);
        who->add("potential", pot);
        tell_object(who,"（"+ chinese_number(exp) + "點經驗，" + chinese_number(pot) + "點潛能，"+ chinese_number(score) + "點江湖閱歷。)\n"NOR);
                  }
                  else 
                  {
                          exp = exp/2;
                          pot = 1;
        who->add("combat_exp",exp);
        who->add("potential", pot);
        tell_object(who,"（"+ chinese_number(exp) + "點經驗，" + chinese_number(pot) + "點潛能，"+ chinese_number(score) + "點江湖閱歷。)\n"NOR);
            }
    }
    return 1;
  }
  if ( ob->query("money_id") )
  {
          need = 10000;
          myexp = who->query("combat_exp");
          if (myexp <= 100000 ) need = 1000; // 10 silver 
          else if (100000 <= myexp && myexp <= 500000) need = 3000; // 30 silver
          else if (500000 <= myexp && myexp <= 1000000) need = 5000; // 50 gold
          else if (100000 <= myexp && myexp <= 2000000) need = 10000; // 1 gold
          else if (200000 <= myexp && myexp <= 3000000) need = 20000; // 2 gold
          else if (300000 <= myexp && myexp <= 4000000) need = 30000; // 3 gold
          else if (400000 <= myexp && myexp <= 5000000) need = 40000; // 4 gold
          else need = 50000; // 5 gold
    if ( !who->query("quest_wei/quest") ||
      who->query("quest_wei/finished") ||
      ob->value() < need )
      tell_object(who,"韋小寶笑道：那我可就不客氣了。\n");
    else if (ob->value()>=MAX_NEED)
    {
      who->set("quest_wei/finished",1);
      tell_object(who,"韋小寶笑道：好好，看你這麼有誠意。你也不用再辛苦了，下去休息休息吧。\n");
      who->delete( "quest_wei/time" );
      }
    else
    {
      tell_object(who, "韋小寶嘆了口氣說道：那好，咱們買賣不成仁義在。想要好處再找我吧！\n");
      if(random(20)==1 && who->query("combat_exp") > 150000) 
        {
        tell_object(who,HIR"由于你經常完不成任務，韋小寶開始不信任你了。\n"NOR);
        who->add("weiwang",-10);
        who->set("quest_wei/busy_exp",who->query("combat_exp")+300);
        if (who->query("meili")>100)
        who->add("meili",(int)-query("meili")/3);
        else
        who->add("meili",-25);
        }
      who->set( "quest_wei/finished", 1 );
      who->set( "quest_wei/time" ,time()+10);
      who->delete("quest_num/wei");
    }
    return 1;
  }
  
  if (  (!quest = who->query( "quest_wei/quest" ))  ||
    who->query( "quest_wei/finished" ) )
  {
    tell_object( who,"韋小寶說道：你給我這個幹嘛？\n" );
    return 0;
  }
  if( ob->query("name") != quest || ob->is_character() )
  {
    tell_object(who, "韋小寶說道：這是什麼東西？我叫你辦的事你就這樣糊弄我？！\n");
    return 0;
  }
  if ((int) who->query("quest_wei/time") <= time() )
  {
    tell_object(who,"韋小寶說道：你是怎麼搞得，現在才把東西弄來！這次就算了，以後要注意。\n");
//    quest_failed( who, "wei" );
    who->delete("quest_wei/quest");
//    who->delete("quest_num/wei");
//    quest_finished( who, "wei" );
    who->delete("quest_wei/finished");
//    who->delete("")
//    destruct(ob);
    ob->set("id","bao wu");//讓give.c把物品dest
    return 1;
  }
  else
  {
    tell_object(who,"韋小寶讚許地點頭說道：不錯！差使辦得不錯！\n");
    who->set("quest_wei/finished",1);

    num = (int)who->query("quest_num/wei");
    if (num >= 450) level=9;
    else if (num >= 400) level=8;
    else if (num >= 200) level=7;
    else if (num >= 100) level=6;
    else if (num >= 50) level=5;    
    else if (num >= 20) level=4;
    else if (num >= 6) level=3;
    else level=0;
    if (who->query("combat_exp")<200000 && level<1) level=1;
    if (level>=10) level=10;
    exp = 60* level + random(30)+3;
    exp=exp*2/3+random(exp*2/3);
    pot = 18* level + random(9)+1; 
    pot=pot*2/3+random(pot*2/3);
    score = 20 + 20* level + random(10);
    who->add("combat_exp", exp);
    who->add("potential", pot);
    who->add("score", score);
        who->set_temp("prize_reason","小寶");
        who->set_temp("can_give_prize",1);
        who->set_temp("prize_exp",exp);
        who->set_temp("prize_pot",pot);
    tell_object(who,HIW"經過一番辛苦奔波，你增長了：" + chinese_number(exp) + "點實戰經驗，"+ chinese_number(pot) + "點潛能，" + chinese_number(score)+"點江湖閱歷。\n"NOR);
    tell_object(who,HIW"恭喜你完成第"+chinese_number(who->query("quest_num/wei"))+"個差使！\n"NOR);   

    who->delete("quest_wei/busy_exp");
    if (num>49 && num<501 && num%50==0 ) 
      special_bonus(this_object(),who,"meili");  //整五十做特殊物品獎勵

    who->add("quest_num/wei",1);
    who->add("quest_num/allwei",1);
    
    if (who->query("skybook/luding/passed")) who->add("meili",2);
    //完成四十二章經任務 獎勵魅力多一些
    else who->add("meili",1);
    
    who->set("quest_wei/time", (int)time());
    if (num>30 && random(100)==1)
    {
    who->set("quest_wei/busy_exp",who->query("combat_exp")+1000);
    gift=new("/clone/money/gold");
    gift->set_amount(50);
    message_vision("$N笑道：這位"+RANK_D->query_respect(who)+"實在是我的得力助手，這裡有些黃金你先拿著。下去好好歇息歇息，別累壞了身子。\n" NOR,this_object()); 
    gift->move(this_object());
    command("give 50 gold to "+who->query("id"));
    }
    destruct(ob);
    return 1;
  }
  return 1;
}

//物品獎勵
void special_bonus(object me, object who,string type)
{
        int cost;
        string need;
        int mysc;

        // 五十獎勵
        string *ob1_list = ({//珠寶
                "clone/jewelry/biyu",
                "clone/jewelry/feicui",
                "clone/jewelry/goldring",
                "clone/jewelry/maoeryan",
                "clone/jewelry/necklace",
                "clone/jewelry/shanhu",
                "clone/jewelry/yubei",
                "clone/jewelry/yudai",
        });

        // 完成一百個任務
        string *ob2_list = ({//傷藥
          "/clone/medicine/nostrum/baihudan",
          "/clone/medicine/nostrum/baiyunwan",
          "/clone/medicine/nostrum/huiyangsan",
          "/clone/medicine/nostrum/jiuhuawan",
          "/clone/medicine/nostrum/shenyangjiu",
          "/clone/medicine/nostrum/tianxianggao",
        });

        // 完成一百五十個任務
        string *ob3_list = ({//初級內力補藥
           "/clone/medicine/nostrum/xiongdan",
           "/clone/medicine/nostrum/guaishedan",
           "/clone/medicine/nostrum/guaishexue",
           "/clone/medicine/nostrum/huochan",
          GIFT_DIR+"gift/con1",
          GIFT_DIR+"gift/str1",
   //       GIFT_DIR+"gift/int1",
          GIFT_DIR+"gift/dex1",
        });

        // 完成二百個任務
        string *ob4_list = ({//低級武功藥
          GIFT_DIR+"pill/renshen1",
          GIFT_DIR+"pill/lingzhi1",
          GIFT_DIR+"pill/xuelian1",
          GIFT_DIR+"pill/shouwu1",
        });

        // 完成二百五十個任務
        string *ob5_list = ({//高級內力補藥
           "/clone/medicine/nostrum/labazhou",
           "/clone/medicine/nostrum/renshenguo", 
           "/clone/medicine/nostrum/binghuojiu",
        });

        // 完成三百個任務
        string *ob6_list = ({//中級武功藥
           "/clone/medicine/nostrum/puti-zi",
          GIFT_DIR+"pill/renshen2",
          GIFT_DIR+"pill/lingzhi2",
          GIFT_DIR+"pill/xuelian2",
          GIFT_DIR+"pill/shouwu2",
        });

        // 完成三百五十個任務
        string *ob7_list = ({//中級天賦藥
          GIFT_DIR+"gift/con2",
          GIFT_DIR+"gift/str2",
     //     GIFT_DIR+"gift/int2",
          GIFT_DIR+"gift/dex2",
        });

        // 完成四百個任務
        string *ob8_list = ({//高級武功藥
          GIFT_DIR+"pill/renshen3",
          GIFT_DIR+"pill/lingzhi3",
          GIFT_DIR+"pill/xuelian3",
          GIFT_DIR+"pill/shouwu3",
        });

        // 完成四百五十個任務
        string *ob9_list = ({//加福緣耐力靈性等的丹藥
          GIFT_DIR+"gift/kar",
          GIFT_DIR+"gift/spi",
          GIFT_DIR+"gift/sta",
          GIFT_DIR+"gift/per",
          GIFT_DIR+"gift/cps",
          GIFT_DIR+"gift/cor",
        });

        // 完成五百個任務
        string *ob10_list = ({//加臂力根骨身法悟性的丹藥
          GIFT_DIR+"gift/str3",
          GIFT_DIR+"gift/con3",
          GIFT_DIR+"gift/dex3",
       //   GIFT_DIR+"gift/int3",
        });


        string un, gift;
        object ob;
        int count;

        if (type == "meili") 
                count = who->query("quest_num/wei");
        else if (type == "gongxian")
                       count = who->query("quest_num/kill")/2;
               else count = 0;


        if (count == 500)
        {
                gift = ob10_list[random(sizeof(ob10_list))];
                cost = 200;
        } else

        if (count == 450)
        {
                gift = ob9_list[random(sizeof(ob9_list))];
                cost = 200;
        } else

        if (count == 400)
        {
                gift = ob8_list[random(sizeof(ob8_list))];
                cost = 150;
        } else

        if (count == 350)
        {
                gift = ob7_list[random(sizeof(ob7_list))];
                cost = 150;
        } else

        if (count == 300)
        {
                gift = ob6_list[random(sizeof(ob6_list))];
                cost = 100;
        } else

        if (count == 250)
        {
                gift = ob5_list[random(sizeof(ob5_list))];
                cost = 100;
        } else

        if (count == 200)
        {
                gift = ob4_list[random(sizeof(ob4_list))];
                cost = 70;
        } else

        if (count == 150)
        {
                gift = ob3_list[random(sizeof(ob3_list))];
                cost = 40;
        } else

        if (count == 100)
        {
                gift = ob2_list[random(sizeof(ob2_list))];
                cost = 10;
        } else

        if (count == 50)
        {
                gift = ob1_list[random(sizeof(ob1_list))];
                cost = 5;
        } 
        else
        {
                return;
        }
        ob = new(gift);

        if (ob->query("base_unit"))
                un = ob->query("base_unit");
        else
                un = ob->query("unit");
        
        if (type == "gongxian") mysc = who->query("family/gongji");
        else mysc = who->query(type);
        if (mysc >= cost)
        {
                message_vision(CYN "$n" CYN "對$N" CYN "微笑道：我這裡剛剛得到一"
                               + un + ob->name() + CYN "，你要的話，送你也無妨。\n" NOR, who, me);

                if (type == "meili") need = "江湖魅力";
                else if (type = "gongxian") need = "門派貢獻";
                tell_object(who, HIW "\n獲得" + ob->name() + HIW "會降低"
                                 "你" + chinese_number(cost) + "點"+need+
                                 "，你可以選擇回答(reply Y|N)是或者否。\n" NOR);

                // 記錄可以領取獎勵
                who->set_temp("quest_gift/got", 1);

                // 記錄任務獎勵物品的路徑
                who->set_temp("quest_gift/obj", gift);

                // 記錄領取該物品所需的門牌貢獻
                who->set_temp("quest_gift/need", cost);
                
                who->set_temp("quest_gift/type", type);
        } 
        else 
        {                
                message_vision(CYN "$n" CYN "對$N" CYN "微笑道：我剛剛拿到。。"+
                       "嗯，算了，想來你也用不著。\n" NOR, who, me);
        }
        destruct(ob);
}
