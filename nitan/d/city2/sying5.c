#include <ansi.h>
#include <room.h>
inherit ROOM;

int do_attack(string arg);

void create()
{
        set("short", "城牆上");
        set("long", @LONG
這裡就是「大宋」軍營前城牆。
LONG );

        set("no_magic", "1");
        set("exits", ([ /* sizeof() == 5 */
               "down" :   __DIR__"syuanmen1",
        ]));

        create_door("down", "鐵門", "up", DOOR_CLOSED);
        setup();
}

void init()
{
        if (interactive(this_player()))
        add_action("do_attack", ({ "throw", "touzhi", "luoshi" }));
}
 
int do_attack(string arg)
{
        object me, ob, room, env;
        string dir, who;
        string zhen, craft;
        mapping exits;

        me = this_player();
        env = environment(me);

        if (! arg) return notify_fail("你要指揮部隊朝誰發起進攻？\n");

        /*
        if( query("env/auto_war", me) )
                return notify_fail("你已經設置為由系統自動指揮作戰！如想自己操作，請修改設置。\n");
*/
        
        if( query_temp("warquest/attack", me) )
                return notify_fail("你的隊伍正在列陣進攻，不要亂發號令了！\n");

        if( !query("craft/siegecity/luoshi", me) )
                return notify_fail("你目前還沒有通曉「守城系兵法」中「落石」這種兵法！\n");
                
        if( !query_temp("warquest/train", me) )
                return notify_fail("你未帶一兵一卒，指揮個什麼呀？\n");

        if( query_temp("warquest/train", me) != "infantry" )
                return notify_fail("你又不是率領步兵，如何實施落石？\n");
        
        if( query_temp("warquest/group", me)<1 )
                return notify_fail("你的隊伍已經損失殆盡，無法列陣沖鋒了！\n");

        if (WAR_D->query_stones(me) < 1)
                return notify_fail("你的軍營裡已經沒有任何檑木滾石，無法實施落石了！\n");
                                
        if (sscanf(arg, "%s on %s", who, dir) != 2)
                return notify_fail("指令格式錯誤，請用 luoshi <軍隊> on <方向> 指揮你的隊伍！\n");

        if( !mapp(exits=query("exits", env)) || undefinedp(exits[dir]) )
                return notify_fail("無法找到目標，請用 luoshi <軍隊> on <方向> 指揮你的隊伍！\n");

        room = get_object(exits[dir]);
        if (! room) return notify_fail("無法找到目標，請用 luoshi <軍隊> on <方向> 指揮你的隊伍！\n");

        if( query("no_fight", room) )
                return notify_fail("那裡不允許撕殺！！\n");

        if (! objectp(ob = present(who, room)))
                    return notify_fail("無法找到目標，請用 luoshi <軍隊> on <方向> 指揮你的隊伍！\n");

        if( !query_temp("warquest", ob) || query_temp("warquest/party", ob) != "meng" )
                    return notify_fail("你軍務在身，還是不要輕易招惹是非的好！\n");

        message_vision(HIY "$N將手中寶劍一揮，大喝道：步兵營準備向敵軍落石！！\n" NOR, me, ob);
        
        zhen = "普通陣";
        craft = "落石";
         set_temp("warquest/attack", 1, me);
        me->start_call_out((: call_other, WAR_D, "attack_over", me :), 10);
        WAR_D->do_attack(me, ob, zhen, craft, env, dir, room);
        return 1;
}