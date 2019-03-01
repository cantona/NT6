#include <ansi.h> 
#include <room.h>  
inherit CREATE_CHAT_ROOM; 
int is_chat_room() { return 1; }  

void create()
{
        set("short", "蛇精洞");
        set("long",@LONG
此處乃蛇精洞，洞內幽深恐怖，四處可見黑色的骸骨，周圍盡是
毒蛇，洞頂不時地滴下發臭的液體，置身此地，心中有一種莫名的恐
懼，據說，九頭蛇精就藏在此洞深處。

LONG);


        set("exits", ([
                "out"  : __DIR__"shedong4.8",
        ]));

        set("no_rideto",1);
        set("no_flyto", 1);
        set("no_clean_up", 1);
        setup();

}

// 檢查今天是否已經參加過蛇精戰
void init()
{
        object me = this_player();

        // 24小時只能參加一次
        if (time() - query("boss/shejing", me) < 2 * 3600 && userp(me) && !wizardp(me)  || query("schedule", me) || query("doing", me) == "trigger")
        {
                tell_object(me, HIG "\n對不起，你參加蛇精對抗戰間隔時不足2小時(也不準計劃練功請你取消計劃及所有觸發)。\n");
                tell_object(me, HIC "你距離上次參加蛇精對抗戰間隔： " + HIY +
                                  sprintf("%d", (time() - query("boss/shejing", me)) / 3600) + HIC " 小時。\n\n" NOR);
                me->move(__DIR__"shedong4.8");
                return;
        }

        // 設置參加時間
        tell_object(me, HIG "\n你進入蛇精洞準備參加對抗蛇精戰鬥，請不要離開，否則2小時內無法再次進入。\n" NOR);
        set("boss/shejing", time(), me);

        me->save();

        return;
}

void start_move()
{
        object *ob;
        int i;

        ob = all_inventory(this_object());

        // 清出清場標志
        delete("doing");

        if (! sizeof(ob))return;

        for (i = 0; i < sizeof(ob); i++)
        {
                if (! ob[i]->is_character())
                {
                        destruct(ob[i]);
                        continue;
                }

                if( query("id", ob[i]) == "jiutoushejing" )
                        continue;

                ob[i]->move("/d/shenlong/shedong4.8");
        }

        return;
}

// 來自蛇精文件的呼叫，當蛇精死亡後延遲將所有房間內的ID
// 移動到蛇精洞外，如delay_time = 0 則不延遲
void move_all_player_out(int delay_time)
{
        if (! delay_time)
        {
                start_move();
        }
        else
        {
                remove_call_out("start_move");
                call_out("start_move", delay_time);
        }

        return;

}
