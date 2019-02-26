inherit ROOM;

#include <ansi.h> 

int do_take(string arg);

void create()
{
        set("short", "冰車");
        set("long", @LONG
這裏是凌霄城的冰車 (che)下山之處，此冰車是凌霄城為了
能直達山腳，所特製而成，能從這雪山之巔飛速滑下，是從雪山
去往山下的交通工具。你可以乘坐(take)它下山。
LONG);
        set("outdoors", "lingxiao");
        set("exits", ([
            "east"  : __DIR__"iceroad3",
        ])); 
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ])); 

        set("item_desc", ([
                "che": "一台以上好的紅杉木所制的冰車，是凌霄弟子下山之用。\n"
        ]) );
        setup();
}
  
void init()
{
        add_action("do_take", "take");
}


int do_take(string arg)
{
        object me = this_player();

        if (! arg || arg != "che" )
                return notify_fail("你要坐什麼？\n");

        if( query("family/family_name", me) != "凌霄城" )
                return notify_fail(CYN "凌霄弟子道瞟了你一眼，冷笑道：你自個沒長"
                                   "腿，非要大爺我服侍你不成？\n" NOR);

        message_vision(HIW "\n$N" HIW "穩穩當當坐上冰車，向凌霄弟子打個手勢。那"
                       "弟子點了點頭，將\n開關一扳，冰車就如離弦之箭，向下飛射而"
                       "出。頓時只見萬里雪山\n在$N" HIW "身邊逝過，如白駒之逝，"
                       "飛翼之行。$N" HIW "心神大快，忍不住縱聲\n長嘯。不一會兒"
                       "，$N" HIW "乘座的冰車已滑到了山腳之下。\n\n" NOR,
                       this_player());

        me->move("/d/xuedao/sroad1");
        tell_object(me, HIC "你順利的到達了山腳下！\n" NOR);

        message("vision", HIW "忽見從山澗中急速滑下一隻冰車，停至山腳之下。一人"
                          "輕身一縱，躍出冰車，身法甚是矯健！\n" NOR,
                          environment(me), ({ me }));

        return 1;
}
