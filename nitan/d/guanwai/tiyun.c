// /guanwai/tiyun.c

inherit ROOM;

#include <ansi.h>

int i = 0;

string* msg = ({
  HIC "\n突然，一陣洪亮聲音從山峰間傳來……\n\n" NOR,
  HIW "神秘高人：“可惜，可惜啊！”\n\n" NOR, 
  HIY "你不禁心中一驚，暗想：“此人內力驚人，難道是隱居在這山谷中的高人？”\n" NOR,
  HIY "你運起內力大聲說道：“敢問前輩為何方高人，為何嘆息？”\n\n" NOR,
  HIW "神秘高人道：“閣下可是胡家刀法的傳人？”\n\n" NOR,
  HIY "你回答道：“正是，前輩有何指教？莫非前輩認識尊師？\n\n" NOR,
  HIW "神秘高人頓了頓繼續道：“往事休要再提……你剛才可是在演練刀劍歸真？”\n\n" NOR,
  HIY "你嘆了一口氣道：“哎！只怕在下今生是無緣窺視刀劍歸真之上乘境界了！”\n" NOR,
  HIY "你繼續道：“在下窮盡畢生精力也未有緣學得半點苗家劍法的招式，既然這樣，在下也只有認命了……”\n\n" NOR,
  HIW "神秘高人大笑道：“閣下何處此言，習武之人立于江湖，武功高低為次，「懲惡揚善、鋤強扶弱」為主，閣下豈能\n"
      "為此而灰心失意？\n\n" NOR,
  HIY "你爽朗地笑道：“前輩果真高人，在下聽得前輩教誨茅舍頓開，他日行走江湖定會以「懲惡揚善、鋤強扶弱」為重！”\n\n" NOR,
  HIW "神秘高人大笑道：“難得閣下有此寬大胸襟，你我也算是有緣人，我就傳你一個武功口訣，他日定會有用得到的地方！”\n\n" NOR,
  HIC "說罷，神秘高人將口訣一五一十的傳授于你，你一一記于心中 ……\n\n" NOR,
  HIW "你忽然想起什麼事情，急忙問道：“前輩，這武功可是 ………”\n\n" NOR,
  HIC "你發現你的聲音回盪于山谷間，那神秘高人早已隱去！\n\n" NOR,
  HIC "你學會了「苗家劍法」！\n\n" NOR,
});

void create()
{
        set("short", "梯雲峰");
        set("long", @LONG
玉柱峰北，有一山峰，峰脊出梯河瀑布，遠望如騰白如雲，縱列如梯，
故名梯雲峰。
LONG );
        set("exits", ([
                "south"      : __DIR__"yuzhu",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "changbai");
        setup();
}

void init()
{
        add_action("do_yanlian", "yanlian");
}

int do_yanlian(string arg)
{
       object me = this_player();
       object ob;

       if (!arg || arg != "daojian-guizhen")return 0;

       if (me->query_skill("hujia-daofa", 1) >= 250
            && query("character", me) == "光明磊落"
           && !(int)me->query_skill("miaojia-jian", 1)
            && ((ob=query_temp("weapon", me)) && (query("skill_type", ob) == "blade"
            || query("skill_type", ob) == "sword") )
            && random(10) == 1 && query("shen", me)>50000 )
      { 
           if( query_temp("learn_now", me))return notify_fail("等你忙完了再說。\n");
           set_temp("learn_now", 1, me);
           write("你開始演練刀劍歸真。\n");
           write("但是你卻發現你連一點苗家劍法都不會，難以繼續演練，你長嘆一聲，心中暗怪命運總捉弄…\n");
           me->start_busy(3);
           remove_call_out("learn_sword");
           call_out("learn_sword", 3, me);    
      }
      else return 0;
     
      return 1;
}

int learn_sword(object me)
{  
     me->start_busy(3);
   
     write(msg[i]);

     if (i == sizeof(msg) - 1)
     {
          me->set_skill("miaojia-jian", 1);
          i = 0;
          delete_temp("learn_now", me);
          return 1;
     }
 
     remove_call_out("learn_sword");
     call_out("learn_sword", 3, me);
 
     i ++;

}
