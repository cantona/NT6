// /d/gaoli/yudao1
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裡的街道寬敞而幹凈，漢白玉砌的路面被雨水沖得光明如鏡，街
道內側是高大宏偉的皇城城牆。北面通向皇城的正門，東西兩面圍繞皇
宮的皇城御道。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north":__DIR__"gongmen", 
                "south":__DIR__"zhuque-1",
                "west":__DIR__"yudao2",
                 "east":__DIR__"yudao3",
        ]));
       setup();
        replace_program(ROOM);
}        
