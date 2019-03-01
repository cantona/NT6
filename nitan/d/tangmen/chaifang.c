//chaifang.c                四川唐門─柴房

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "柴房");
        set("long",
"這裡是後院的柴房，屋中堆滿了劈好的柴火，滿屋都是木材的香味，\n"
"在山也似的柴堆旁一扇小門通向後山，聽說那裡出沒著豺狼虎豹和蜈蚣蛇\n"
"蠍，工夫不夠高可不要亂跑呀！西邊就是廚房了！\n"
);
        set("exits", ([
                "northeast" : __DIR__"houzhai",
                "west" : __DIR__"chufang",
                "south" : __DIR__"nzlange1",
                "north" : __DIR__"exiaolu1",
        ]));
        create_door("northeast","木門","southwest",DOOR_CLOSED);
        set("objects", ([
                CLASS_D("tangmen") + "/tangpeng" : 1,
        ]));
        set("area", "tangmen");
        setup();
}
int valid_leave(object me, string dir)
{
        if( (dir == "north") && (query("family/family_name", me) != "唐門世家") && 
                !wizardp(me) && (objectp( present("tang peng", environment(me)) ) ))
                return notify_fail("唐朋一伸手，說道：“你不是唐門中人，不能再向前走了！”\n");
        else
                return ::valid_leave(me, dir);
}
