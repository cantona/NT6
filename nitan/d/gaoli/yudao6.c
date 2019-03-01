// /d/gaoli/yudao1
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裡的街道寬敞而幹凈，漢白玉砌的路面被雨水沖得光明如鏡，街
道內側是高大宏偉的皇城城牆。牆內飄來了一陣陣喧嘩。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south":__DIR__"yudao4", 
                "east":__DIR__"yudao8",
        ]));
       setup();
        replace_program(ROOM);
}        
