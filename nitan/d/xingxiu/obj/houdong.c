#include <ansi.h>

inherit ROOM;

#define MUDING "/clone/misc/swmuding"

string look_desk();
string look_pet();

void create()
{
        set("short", "日月後洞");
        set("long", @LONG
這裡是星宿派日月洞後洞，星宿老仙有時候會在這裡閉關練功。
只見洞內燈火通明，似乎比日月洞寬敞了許多。正前方有一個精致的
石桌（desk），石桌上擺著各式水果，想必是星宿派弟子送來孝敬老
仙的。
LONG );
        set("exits", ([
             "south"      : __DIR__"riyuedong",
             "southwest"  : __DIR__"riyuedong1",
        ]));

        set("item_desc", ([
                "desk" :  (: look_desk :),
                "pet"  :  (: look_pet :),
        ]));
               
        setup();

}

string look_desk()
{
       object me = this_player();
       object ob;

       ob = find_object(MUDING);
       if (! ob) ob = load_object(MUDING);       

       if( query_temp("move", me) )
       {
              if (! environment(ob))
                     write(HIC "看來這個石桌被人移動過！底下露出一個小洞，只見洞中放著一"
                           "個木鼎(mu ding)模樣的容器！\n你試圖想將它拿(pick)出來！\n" NOR);
              else 
                     write(HIW "看來這個石桌被人移動過！底下露出一個小洞，只見洞中空空如也！\n" NOR);
       }

       if (me->query_skill("poison", 1) < 160)
              return NOR + WHT "這是一張很精致的石桌，石桌上雕刻著各種像是毒物（pet）模樣的"
                     "圖案。陣陣奇特香氣\n從石桌中散發出來，你頓感覺頭暈目眩，胸悶之極。\n" NOR;

       return NOR + WHT "這是一張很精致的石桌，石桌上雕刻著各種像是毒物（pet）模樣的"
              "圖案。陣陣奇特香氣\n從石桌中散發出來，你心中一驚：“不好，這桌子上竟塗有劇毒！”\n" NOR;
}

string look_pet()
{
       object me = this_player();

       if( query("family/family_name", me) != "星宿派" || 
           me->query_skill("xingxiu-qishu", 1) < 160)
               return NOR + YEL "上面刻有蜈蚣，蜘蛛，蠍子，蛇，蟾蜍五種毒物。\n" NOR;

       return NOR + WHT "上面刻有" HIY "金蜈蚣" NOR + WHT "，" NOR + BLU "黑寡婦" NOR + WHT
              "，"HIR "赤蠍子" NOR + WHT "，" HIW "千年靈蛇" NOR + WHT "，" HIY "花" HIM 
              "斑" NOR + GRN "毒蟾 " NOR + WHT"。你心中一驚：“難道這便是五聖劇毒？”\n" NOR;
}

void init()
{
       add_action("do_move", "move");
       add_action("do_pick", "pick");              
}

int do_move(string arg)
{
       object me = this_player();
       object ob;

       if (! arg || arg != "desk")
             return notify_fail("你想移動什麼？\n");

       if( query_temp("move", me) )
             return notify_fail("你已經將石桌移開了！\n");
       
       ob=query_temp("armor/hands", me);

       if( !ob || query("id", ob) != "jinsishoutao" )
       {
             delete_temp("move", me);

             message_sort(HIC "\n$N" HIC "試圖將石桌移開，但是$P手剛碰到石桌，卻聽到一聲慘叫，$N" HIC
                            "倒在地上，連掙也沒有掙紮便一命嗚呼了！\n", me);

             set_temp("die_reason", "中星宿派具毒而亡", me);
             me->die();

             return 1;
             
       }

       set_temp("move", 1, me);
       message_vision(HIG "$N" HIG "輕輕地將石桌移開！\n" NOR, me);
       
       return 1;
}

int do_pick(string arg)
{
      object ob, me;
      object hand;

      me = this_player();

      if (! arg || arg != "mu ding from desk" )
            return notify_fail("你要拿什麼？\n");

      if( !query_temp("move", me) )
            return notify_fail("你要拿什麼？桌子上沒什麼好拿的！\n");

      ob = find_object(MUDING);
      if (! ob) ob = load_object(MUDING); 

      if (environment(ob))
            return notify_fail("神木王鼎已經被人拿走了！看來你來晚了！\n");

      hand=query_temp("armor/hands", me);

      if( !hand || query("id", hand) != "jinsishoutao" )
      {
             delete_temp("move", me);
       
             message_sort(HIM "\n$N" HIM "將手伸進石桌試圖拿取神木王鼎，但是突然一只赤蠍跳了出來一口"
                         "咬在$N" HIM "的手上，$N" HIM "怪叫一聲，頓時斃命！\n" NOR, me);

             me->die();

             return 1;
      }
  
      message_sort(HIM "\n$N" HIM "將手伸進石桌試圖拿取神木王鼎，突然一只赤蠍跳了出來一口"
                   "咬在$N" HIM "的" + hand->name() + HIM "上，但是$N" HIM "卻絲毫無傷地將"
                   "神木王鼎取了出來！\n" NOR, me);

      ob->move(me);
      delete_temp("move", me);
   
      return 1;
}