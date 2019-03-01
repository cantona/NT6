// Room: /huanghe/huanghegate.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "黃河幫寨門");
        set("long", @LONG
這是一所氣勢壯觀的寨門，正中高掛著一面匾額─寫著「黃河幫」
三個大字。寨裡旗幟高掛，規模不小。黃河幫是黃河沿岸的一個大幫會，
平日飛揚跋扈，欺壓百姓，作惡多端。幫主沙通天武功深湛，並與彭連
虎、樑子翁和靈智上人等高手結交，因此聲勢浩大。據聞其與金人勾結，
欲侵略中土。
LONG );
        set("exits", ([
                "east"  : __DIR__"huanghe1",
                "west"  : __DIR__"guangchang",
        ]));
        set("objects", ([
                __DIR__"npc/ma" : 1,
                __DIR__"npc/shen" : 1,
        ]));
//        set("no_clean_up", 0);
        set("outdoors", "huanghe");
        set("coor/x", -2000);
        set("coor/y", 520);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}