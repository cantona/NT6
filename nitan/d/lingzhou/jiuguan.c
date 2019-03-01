// Room: /lingzhou/jiuguan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "酒館");
        set("long", @LONG
這是一家小酒館，緊挨著靈州西門，五開間的門面，規模頗大。來
來往往的行人多到這裡來打尖歇腳，叫上一盤阿訇宰殺的牛羊肉，喝上
幾口醇香的馬奶酒，酒足飯飽離店之際帶上幾個有臉盆大小的□，花錢
不多又很實惠，生意特別興旺。北面是廚房，南面是上樓的樓梯，東面
有條布簾。
LONG );
        set("exits", ([
                "east" : __DIR__"nandajie",
        ]));
        set("objects", ([
                __DIR__"npc/xiaoer2" : 1,
        ]));
        set("coor/x", -6285);
        set("coor/y", 2925);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}