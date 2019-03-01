// /d/gaoli/yudao4
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裡的街道寬敞而幹凈，漢白玉砌的路面被雨水沖得光明如鏡，街
道內側是高大宏偉的皇城城牆。東面是高麗的城防衙門，進進出出的多
是一些士兵。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"yudao6", 
                "south":__DIR__"yudao2", 
                "west":__DIR__"qinglong-1", 
                "east":__DIR__"yamen",
        ]));
       setup();
        replace_program(ROOM);
}        
