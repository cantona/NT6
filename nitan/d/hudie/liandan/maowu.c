// Room: maowu.c

inherit ROOM;

void create()
{
        set("short", "茅屋");
        set("long", @LONG
你穿過內堂來到山腰，不遠處有一茅屋。遠處望去，千葉
重台，萬山蒼翠，清溪飛瀑，映帶其間，極目煙波千里，映照
峯巒巖嶺。近處青苔綠草，蒼潤欲流，經日頭一照，絲毫不覺
灼熱，反而清涼怡人，萬紫奼紅，點綴其間，直如世外桃源！
LONG
        );
       set("no_fight", 1);
        set("exits", ([ /* sizeof() == 2 */
  "northeast" : __DIR__"liupeng",
  "southwest" : __DIR__"diecong4",
]));
        set("objects", ([ 
//  __DIR__"npc/hu" : 1,
]));
        set("no_clean_up", 0);

        setup();
        replace_program(ROOM);
}
