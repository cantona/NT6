#include <ansi.h>
#include <command.h>

inherit ITEM;
#include "songs.c"

void create()
{
        set_name(YEL "曲譜" NOR, ({ "qu pu", "pu"}));
        set_weight(10000);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit", "冊");
                set("long", "
一冊裱釘精美的曲譜，你可以唱(chang)裏面的曲子：

  《圓圓曲》(yuanyuan_qu)
  《望海潮》(wanghai_chao)
  《問世間  情為何物》(wenshi_jian)
  《蝶戀花》(dielian_hua)
  《波斯小曲》(bosi_xiaoqu)
  《春江花月夜》(chunjiang_huayueye)
  《飲馬長城窟行》(yinma_changcheng)
  《將進酒》(jiangjin_jiu)
  《笑傲江湖》(xiaoao_jianghu)
  《白雪歌送武判官回京》(baixue_ge)
  《虞美人》(yu_meiren)
  《蘭陵王·丙子送春》 (song_chun)
  《詠荷》 (yong_he)
  《水調歌頭·中秋 》 (shuidiao_getou)
  《滿江紅》 (manjiang_hong)
  《雨霖鈴》 (yulin_lin)
  《一剪梅》 (yijian_mei)

你如果覺得唱得不好，可以停(ting)下，再回去練練。
\n");
                set("value", 10000);
                set("material", "silk");
             }
        setup();
}


void init()
{
        add_action("do_sing", "chang");
        add_action("do_halt", "ting");
}
int do_halt()
{
        if (find_call_out("sing_stage") < 0) return 0;
        delete_temp("qupu", this_player());
        
message_vision(HIR"\n$N發現大家一臉痛苦的表情，尷尬地咳嗽了兩聲，停下了噪音。\n"NOR, 
this_player());
        remove_call_out("sing_stage");
              return 1;
}
int do_sing(string arg)
{
       object me, ob;
       int i = sizeof(qupu);
       int stage;
       stage = 0;
       me = this_player();
       ob = this_object();
       if (find_call_out("sing_stage") >= 0) return 
notify_fail("你能同時唱兩首曲子嗎？\n");
       if(!arg) return notify_fail("你想唱什麼？\n");
        while (i--) if (arg == qupu[i]["name"]) break;
        if (i<0) return notify_fail("曲譜裏還沒有你想唱的曲子。\n");
        if(me->is_busy())
           return notify_fail("你正忙着呢。\n");
        if( query_temp("qupu", me))return notify_fail("你正在唱着呢。\n");
        if( query("gender", me) != "男性"){
          if(present("dong xiao", me))
             message_vision(MAG
"$N輕捻$n"MAG"，起身盈盈拜起，玉脣含簫，只聽：
曲調柔媚宛轉，簫聲緩緩盪漾，猶似微風起處，荷塘水波輕響。
接着$N微微一笑，曼聲開始唱道：\n\n"NOR, me, ob);
          else 
message_vision("$N輕捻$n，起身盈盈一拜，然後曼聲開始唱道：\n\n"NOR, me, ob);
          }
        else {
          if(present("yao qin", me))
             
message_vision(BLU"$N翻開$n"BLU"，盤膝坐下，將瑤琴放在膝上，理弦調韻，按節捻弦，彈唱起來：\n\n"NOR, 
me, ob);
          else message_vision("$N翻開$n，放開歌喉，呀呀呀唱了起來：\n\n"NOR, 
me, ob);
          }
      set_temp("qupu", 1, me);
      call_out("sing_stage", 2, me, stage, i, sizeof(qupu[i]["context"]));
      return 1;
}

void sing_stage(object me, int stage, int i, int size)
{
   if(stage < size) {
   message_vision(qupu[i]["context"][stage], me);
   me->start_busy(1);
   call_out("sing_stage", 1, me, ++stage, i, size);
   }
   else {
    delete_temp("qupu", me);
    if( query("gender", me) != "男性"){

      if(present("dong xiao", me))
          
message_vision(MAG"\n過了一會，$N簫聲漸緩漸輕，似乎流水汩汩遠去，終於歌完曲終，寂然無聲。\n"NOR,me);
      else 
message_vision("\n$N聲調轉高，唱完最後一字，歌聲卻依然曼長不絕，在空中來回盪漾。。。\n", 
me);
          }
    else {
      if(present("yao qin", me))
         
message_vision(BLU"\n只聽簫鳴止歇，$N唱完一曲，站起身來，恭身做了個鞠。\n"NOR, 
me);
      else 
message_vision("\n$N唱完最後一字，仰天一聲長嘯，嘯聲遠遠傳了開去。\n", me);
          }
    }
}

int query_autoload()
{
return 1;
}