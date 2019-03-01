// Room in 高麗
inherit ROOM;
void create()        
{
        set("short", "海港");
        set("long", @LONG
這裡是從高麗出海的必經之地，從這裡上船可以直接到達揚州。這
裡非常熱鬧，停泊著各種船只，有貨船，商船等等。很多旅客從這裡進
出港口，有從中原來的，也有從其他地方來的。許多小販在這裡叫賣。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "west" : __DIR__"yucun",
        ]));
       setup();
        replace_program(ROOM);
}        
