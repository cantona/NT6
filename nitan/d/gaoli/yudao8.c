// /d/gaoli/yudao8
// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裏的街道寬敞而乾淨，漢白玉砌的路面被雨水衝得光明如鏡，街
道內側是高大宏偉的皇城城牆。南面是高麗的迎賓館，進進出出來來往
往的有客商，還有各國使節。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"xuanwu-1", 
                "south":__DIR__"yingbinguan", 
                "west":__DIR__"yudao6", 
                "east":__DIR__"yudao7",
        ]));
       setup();
        replace_program(ROOM);
}        
