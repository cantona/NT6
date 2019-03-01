// Summer 9/25/96
#include "room.h"

inherit ROOM;

void create()
{
        set("short", "紅殿");
        set("long", @LONG
這裡是雪山寺的紅殿，殿內光線暗淡，壁上畫像色暗。殿正中供
著密集金剛。金剛三面，戴寶冠，主面三睛，耳飾大環，上身裸，下
著長裙，結跏趺坐，六臂，兩主臂擁明妃，其余兩臂分張兩側各執法
器，明妃亦六臂，與金剛相向而擁，兩腿盤腰後。金剛座(zuo)下有石
蓮花、海石榴花、太平花和十字花。
LONG );
        set("exits", ([
                "northeast" : "/d/xueshan/dating",
        ]));
        set("item_desc", ([
                "zuo" :
        "金剛座高高在上。\n",
        ]) );

        set("cost", 1);
        setup();
}
void init()
{
        add_action("do_jump", "jump");
}


int do_jump(string arg)
{
        object me;
        me = this_player();

        if( !arg || arg=="" )
                return 0;
        if( arg=="zuo")
        {
                if (me->query_skill("dodge") < 30){
                    write("你試圖跳上金剛座，無奈身法不夠敏捷，只好做罷。\n");
                return 1;
                }
                else {
                    write("你縱身躍上了金剛座。\n");
                    message("vision",
                             me->name() + "一縱身躍上了金剛座。\n",
                             environment(me), ({me}) );
                    me->move("/d/xueshan/zuo");
                    message("vision",
                             me->name() + "從下面躍了上來。\n",
                             environment(me), ({me}) );
                return 1;
         }
     }
}

int valid_leave(object me, string dir)
{
        return ::valid_leave(me, dir);
}

