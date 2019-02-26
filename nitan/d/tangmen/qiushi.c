//room: /d/tangmen/qiushi.c

inherit ROOM;
#include <ansi.h>
void create()
{
  set("short","囚室");
  set("long",
      "這裏四面一片漆黑，你藉着剛剛打開的出口一點點亮光，發現裏面竟然有一個\n"
"人。這個人被精鋼鐐銬鎖着，不能動彈，蓬頭垢面，但仍然看得出氣度不凡。\n"
     );
   set("objects", ([
           __DIR__"npc/xiaoqiushui" : 1,
                 ]));        
  set("exits",([
      
          ]));

 setup();

}
void init()
{
        add_action("do_break", "break");
}
int do_break(string arg)
{
    int n;
        object me = this_player();

    if( !arg || arg!="bagua" )
        {
        write("唐門的財物豈是你隨便能破壞的！\n");
        return 1;
    }

    message_vision(
    "$N走到八卦前，騰身而起，運起全身內力，雙掌斜斜擊向八卦。\n", this_player());


    n=query("neili", me);
    if (n >= 1500)
        {
        message_vision(
        HIR"$N只聽一聲巨響！！！！！！！！！\n"NOR, this_player());
        set("exits/up", "/d/tangmen/dating");
        set("neili", n-1500, this_player());
        remove_call_out("close");
        call_out("close", 10, this_object());
    }
    else
        {
                message_vision(
                HIW"結果只聽一聲悶哼，$N被八卦陣的反彈力震得眼前一黑....\n"NOR, this_player());
set("neili", 0,                 this_player());
                this_player()->unconcious();
    }
return 1;
} 



void close(object room)
{
    message("vision","只聽見一陣嘎嘎的響聲，八卦又翻了轉來，恢復了原樣。\n", room);
    delete("exits/up", room);
}


