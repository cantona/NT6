// /d/gaoli/qianzhuang
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "高麗錢莊");
        set("long", @LONG
這是高麗規模最大的一家錢莊，錢莊的門口掛着一塊很大的金字招
牌，“高麗錢莊”長長的櫃枱，都打掃的乾乾淨淨。櫃枱後幾個賬房先
生與小活計正在忙的焦頭爛額。
LONG
        );
set("exits", ([
               "east":__DIR__"xuanwu-1", 
        ]));
   set("objects", ([
                "/d/gaoli/npc/jin" : 1,
        ]));
       setup();
        replace_program(ROOM);
}        
