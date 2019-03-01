// Room: /d/huijiang/xiagu.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;
#include <ansi.h>;

void create()
{
        set("short","峽谷");
        set("long",@LONG
這裡是一道峽谷，兩旁石壁峨然筆立，有如用刀削成，抬頭望天，
只覺天色又藍又亮，宛如潛在海底仰望一般。峽內巖石全系深黑，烏光
發亮。道路彎來彎去，異常曲折。
LONG );
        set("outdoors", "huijiang");
        set("exits", ([
                "southeast" : __DIR__"caoyuan6",
                "north"     : __DIR__"damen",
        ]));
        set("objects", ([
                CLASS_D("honghua")+"/yang-chengxie" : 1,
        ]));
        set("coor/x", -50060);
        set("coor/y", 9130);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}