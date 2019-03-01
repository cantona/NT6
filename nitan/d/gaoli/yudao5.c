// /d/gaoli/yudao5
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裡的街道寬敞而幹凈，漢白玉砌的路面被雨水沖得光明如鏡，街
道內側是高大宏偉的皇城城牆。東面是高麗的武士行館，進進出出的多
是一些高麗的武士。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"yudao7", 
                "south":__DIR__"yudao3", 
                "east":__DIR__"baihu-1", 
                "west":__DIR__"xingguan",
        ]));
       setup();
        replace_program(ROOM);
}        
