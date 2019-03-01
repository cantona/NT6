//ROOM: /d/yanziwu/lanyue.c

inherit ROOM;
#include <ansi.h>

int check_pass(object me);
int end_whisper(object me);

void create()
{
        set("short", "攬月居");
        set("long", @LONG
這是慕容公子的臥室，房中陳設普通，收拾得頗為整潔，屋角一
架茂蘭盆景(penjing)長得很是旺盛。晚上月光從窗戶射進來，滿室銀
光，是燕子塢的一大美景。
LONG );
        set("exits", ([
            "west": __DIR__"shuwu",
        ]));

        set("item_desc", ([
            "penjing" : HIW "這盆景似乎很平常，獨有其邊沿特別光滑。\n" NOR,
        ]));

        setup();
}

void init()
{
        add_action("do_knock","knock");
        add_action("do_say","whisper");
}

int do_knock(string arg)
{
        object me;
        me=this_player();

        if (!arg || (arg!="penjing" ) )
                 return  notify_fail("你要敲什麼？\n");

        if( query_temp("marks/pen", me) )
                 return notify_fail("別敲了！\n");

        set_temp("marks/pen", 1, me);
        write(HIC "你在盆景上敲了幾下...\n" NOR, me);
        remove_call_out("check_pass");
        call_out("check_pass", 4, me);

        return 1;
}

int check_pass(object me)
{
       write(HIC "不一會兒，只聽不遠處隱約傳來一陣說話聲：“洒國夢語…”\n" NOR);
       write(HIY "你想了想，覺得像是一句暗語，你很想回答(whisper)但又不知道說些什麼！\n" NOR);
       set_temp("can_whisper", 1, me);
       remove_call_out("end_whisper");
       call_out("end_whisper", 9, me);
       return 1;
}

int end_whisper(object me)
{
      if (! me) return 0;
      write(HIM "過了良久，只聽見一陣不耐煩的聲音傳來：“算了，沒事別在這來搗亂。”\n" NOR);
      delete_temp("marks/pen", me);
      delete_temp("can_whisper", me);
      return 1;
}

int do_say(string arg)
{
     object me = this_player();
     
     if( !arg || !query_temp("can_whisper", me) )
              return notify_fail("你自言自語不知道在說什麼！\n");

     if(arg != "光復大燕")
     {
              write(HIG "你悄悄地說道：“" + arg + "”，卻沒什麼反應。\n");
              return 1;
     }
 
     write(HIG "你悄悄地說道：“光復大燕”……\n" NOR);
     write(HIC "裡面的人笑了笑說道：“既然是主人的吩咐，那你就進來吧！”\n");
     write(HIY "忽然，轟轟幾聲過後，花盆後露出一條路來，你趕忙順著走了下去……\n");
     me->move(__DIR__"huanshi");
     delete_temp("can_whisper", me);
     return 1;

}


