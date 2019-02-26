// Code of ShenZhou
// Summer 9/12/96
#include "room.h"

inherit ROOM;
int do_pray();
int do_pour(string);

void create()
{
        set("short", "舍利寶塔");
        set("long", @LONG
這裏就是貢奉歷代嘉木活佛舍利的地方，寶塔前有一個木案(mua
n)，塔身上刻的有彌勒佛和八大菩薩，塔頂覆以鎏金銅瓦，形式別至
小巧。
LONG );
        set("exits", ([
                "west" : "/d/xueshan/houdian",
        ]));
        set("item_desc", ([
                "muan" : "木案上放置了合種精巧別緻的吉祥銀鑑，淨水銀盃、酥油燈、銅
盆、銅盞等供器。\n",
        ]));
        set("objects", ([
                "/d/xueshan/npc/xiangke" : 2,
                "/d/xueshan/obj/lamp" : 1,
        ]));
        set("cost", 2);
        setup();
        set("outdoors","qilian-shan");
}
void init()
{
        add_action("do_pray","pray");
}

int do_pray()
{
    object ob, me = this_player();
    int check, wait_time = 0;
    remove_call_out("open_up");
    message_vision("$N心誠意真地跪下來默默祈禱。\n", me);
 
    if( query_temp("marks/油", me)){
    set_temp("marks/祈", 1, me);
    delete_temp("marks/油", me);
        }
    if( query_temp("marks/祈", me) && interactive(me) && !me->is_fighting()){
           call_out("open_up", random(300)+300, me);
        }
    return 1;
}

int open_up(object me)
{
                object lamp;
            /* make sure that only when lamp is lighted, the door opens */
                if ( objectp(lamp = present("lamp", this_object())) ) {
                   if( query("burning", lamp)){
              message_vision("$N心誠意真地祈禱了良久，突然舍利塔底打開了一道小門。\n", me);
              set_temp("marks/等", 1, me);
              set("exits/enter", "/d/xueshan/tadi");
              call_out("close_up", 8, me);
                   }
                }
        return 1; 
}

int close_up(object me)
{
        message_vision("小門又輕輕地合上了。\n", me);
        delete("exits/enter");
        delete_temp("marks/等", me);
        return 1;
}

int valid_leave(object me, string dir)
{
        if( !query_temp("marks/等", me )
         && !query_temp("marks/祈", me) && dir == "enter" )
           return notify_fail("你心意不誠，不能進入寶塔。\n");
        else if( query_temp("marks/祈", me) && dir == "south"){
           remove_call_out("open_up");
        }

        return ::valid_leave(me, dir);
}

