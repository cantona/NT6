// Room: /d/kunlun/shanmen.c
// Last Modified by Winder on Nov. 15 2000

#include <ansi.h>
#include <room.h>
inherit ROOM;

void create()
{
        set("short", "崑崙派山門");
        set("long",@long
你一路走來，飽受大風黃沙之苦，漸漸樹木多了起來，不時可聽見
枝葉中傳來的鳥鳴，路邊草叢偶爾也能發現一些開着的野花。到得這裏，
已是綠樹紅花，十分茂盛，你萬萬沒想到深山中卻有如此所在，精神大
為一振。前面是一座山門，寫着“崑崙派”三個大字。
long);
        set("exits",([
                "eastup"    : __DIR__"shanlu01",
                "southdown" : __DIR__"klshanlu",
        ]));
        set("objects",([
                CLASS_D("kunlun")+"/jiangtao" : 1,
                __DIR__"npc/kl-dizi1" :  1,
                __DIR__"npc/kl-dizi2" :  1,
                "/clone/npc/walker" : 1,
        ]));
        set("outdoors", "kunlun");
        set("coor/x", -120000);
        set("coor/y", 35000);
        set("coor/z", 50);
        setup();
        replace_program(ROOM);
}