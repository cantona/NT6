#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "水簾洞外洞");
        set("long", @LONG
這裏就是水蓮洞外洞，只見洞內怪石突現，洞高丈許，甚是開闊，
身後便是瀑布(pubu)，隨飛瀑而下的細小水末灑在臉上，令人頓感涼
爽之極，不斷有水滴順着洞內的怪石滴下，連成一條條細線，遠觀之
下猶如一幅幅窗簾， 水蓮洞也因此得名。
LONG );
        set("item_desc",([
               "pubu":HIC"\n你仰望瀑布，景緻甚為壯觀，可是你猛然發現外面"
                      "的平地卻在水蓮洞上方，要跳出去卻是萬難做到。\n\n"NOR,
        ]));

        set("exits",([
               "enter":__DIR__"inhole1",
        ]));        
                     
       setup();
       replace_program(ROOM);
}