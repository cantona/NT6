#include <room.h>
inherit ROOM;

void create()
{
        set("short", "凡陛橋");
        set("long", @LONG
凡陛橋是一座橋橫跨東西的天橋，橋上面人聲鼎沸，正是賣雜貨、
變把戲、跑江湖的閒雜人等聚居的所在。寬闊的大道向南北兩頭延伸。
向南方對直邁進可以到達北京城裡的名勝天壇。北方是一塊寬闊的空
地，那裡便是熱鬧的長安街廣場了。凡陛橋的東西兩個方向分別連接
了京城的永內東街和虎坊路。
LONG );
        set("exits", ([
                "south" : "/d/beijing/tiantan_n",
                "north" : "/d/beijing/cagc_s",
                "east" : "/d/beijing/yong_1",
                "west" : "/d/beijing/fu_2",
        ]));
        set("objects", ([
                "/d/beijing/npc/maiyi3" : 1,
                "/d/beijing/npc/xianren" : 2,
                "/d/beijing/npc/xiaofan" : 1,
                "/d/beijing/npc/old3" : 1,
                "/d/beijing/npc/boy2" : 1,
        ]));
        set("outdoors", "beijing");
	set("coor/x", -2800);
	set("coor/y", 7650);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}