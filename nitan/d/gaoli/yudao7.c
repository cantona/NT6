// /d/gaoli/yudao1
// Room in 高麗
// rich 99/03/28
inherit ROOM;
void create()        
{
        set("short", "皇城御道");
        set("long", @LONG
這裏的街道寬敞而乾淨，漢白玉砌的路面被雨水衝得光明如鏡，街
道內側是高大宏偉的皇城城牆。牆內飄來了一陣陣喧譁。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "south":__DIR__"yudao5", 
                "west":__DIR__"yudao8",
        ]));
set("objects",([
 __DIR__"npc/gongzi":1,
 ]));
       setup();
        replace_program(ROOM);
}        
