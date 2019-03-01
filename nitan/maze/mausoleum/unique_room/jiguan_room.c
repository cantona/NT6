#include <ansi.h>

void init()
{
       object me = this_player();
       object ob;

       if( !objectp(ob = FUBEN_D->query_maze_mainobj(me)) ) {
             write(HIR "TSR 物件載入出錯，請與本站 (admin) 聯系。\n" NOR);
             return;
       }

       //if( wizardp(me) || present("dispay serial", me) ) {
       if( userp(me) ) {

                write(HIG "\n房間ID：" + query("room_id") + "\n");
                write(HIG "管理物件分配該房間的序列號：" + query(query("room_id"), ob) +"\n"NOR);
                write(HIG "正確開鎖順序：A、B、C、D\n" NOR);
       }

       add_action("do_move", "move");
}

int do_move(string arg)
{
       object me = this_player();
       object ob;
       string room_id;

       if( !arg || arg != "desk" )
             return notify_fail("你想移動什麼？\n");

       if( me->is_busy() || me->is_fighting() )
             return notify_fail("等你忙完了再說吧！\n");

       ob = FUBEN_D->query_maze_mainobj(me);

       if( !objectp(ob) )
             return notify_fail("TSR 物件載入出錯，請與巫師聯系！\n");

       if( query("lock/unlocked", ob) )
             return notify_fail("機關已經被打開了，這樣是多此一舉。\n");

       room_id = query("room_id");
       room_id = query(room_id, ob);

       if( !stringp(ob->openlock(me, room_id)) )
             return notify_fail("TSR 數據出錯，請與巫師聯系！\n");

       me->start_busy(1 + random(2));

       message_vision(HIC "$N" HIC "將石桌用力的旋轉，只聽得不遠處傳來"
                      "一陣轟隆隆的像是觸動機關的聲音。\n" NOR, me);

       return 1;
}
