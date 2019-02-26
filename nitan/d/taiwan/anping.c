// Room: /d/taiwan/anping.c
// Last Modifyed by Ahda on Jan. 4 2002

#include <ansi.h>;
inherit ROOM;

void create()
{
        set("short", "安平鎮");
        set("long", @LONG
明朝末年，荷蘭人趁中國虛弱，登陸台灣南部，並在安平地區築熱
蘭遮城。從此荷蘭人自澎湖移台，與中國互市，並將此處視為與日本貿
易的中途站。漢人漁商此後接踵而至，即在城廓外自建新街市，城堡東
方的「台灣街」是台灣最早的商業街。永曆十五年，國姓爺東征，次年
收復此城，改名「安平鎮」。
LONG );
        set("exits", ([
                "west"      : __DIR__"luermen",
                "southeast" : __DIR__"zhenbeifang",
        ]));
        set("objects", ([
                __DIR__"npc/shangren": 2,
                __DIR__"npc/yufu": 1,
        ]));
        set("outdoors", "taiwan");
        set("coor/x", 2500);
        set("coor/y", -7030);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
