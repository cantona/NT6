// This program is a part of NT MudLIB

#include <room.h>
#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "牛家村");
        set("long", @LONG
錢塘江浩浩江水，日日夜夜無窮無休的從臨安牛家村邊繞過，東
流入海。江畔一排數十株烏柏樹，葉子似火燒般紅。村前村後的野草
剛起始變黃，更增了幾分蕭索。兩株大鬆樹下圍著一堆村民，男男女
女和十幾個小孩，正自聚精會神的聽著一個瘦削的老者說話。村東頭
挑出一個破酒簾，似是酒店模樣。
LONG );

        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"jiudian",
                "west" : __DIR__"qiantang",
        ]));

        set("objects", ([
                __DIR__"npc/yang" : 1,
                __DIR__"npc/guo" : 1,
         ]));

         set("outdoors", "xihu");

         set("coor/x", 3900);
        set("coor/y", -1800);
        set("coor/z", 0);
        setup();

         replace_program(ROOM);
}