// Room: /d/huashan/shangu.c

#include <room.h>
inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
這裡是中條山的一個隱秘山谷。四周是高可及天的山峰，雲深林
密，一徑小溪潺潺流過，濺入坡下塘中。溪畔有一漢子舞劍正酣。不
打擾的為妙。
LONG );
        set("exits", ([ /* sizeof() == 4 */
            "northdown" : __DIR__"jzroad7",
            "south"     : __DIR__"pingdi",
        ]));
        set("objects", ([
            CLASS_D("huashan")+"/cong-buqi": 1,
        ]));
        set("outdoors", "huashan");
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}
