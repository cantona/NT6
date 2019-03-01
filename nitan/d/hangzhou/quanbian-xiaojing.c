// yuanyuantai
inherit ROOM;
#include <ansi.h>
void create()
{
        set("short", "泉邊小徑");
        set("long", @LONG
繞過玉泉，眼前出現一條蜿蜒的曲徑。人在窄窄的山道上行走，
兩旁是青翠的林木，頭頂是掩映的花樹，略帶鬆脂香味的濕潤空氣輕
輕地散逸著，微風吹過，林顫雲搖，時不時傳來的聲聲鳥語，更襯托
出這片山谷的清幽靜寂。
LONG );
        set("outdoors", "xihu");
        set("exits", ([
                "north" : "/d/hangzhou/shandao1",
                "south" : "/d/hangzhou/yuquan",
        ]));

//        set("no_clean_up", 0);
	set("coor/x", 770);
	set("coor/y", -2000);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}