// dating1

inherit ROOM;

void create()
{
        set("short", "堂廳");
        set("long", @LONG
這是『日月神教』下第一大堂：風雷堂的大廳，四目望去，滿樸
素的，堂樑上有一副聯子(vote)。
LONG );
        
        set("exits", ([
            "south" : __DIR__"grass2",
            "northdown" : __DIR__"linjxd5",
        ]));
 
        set("objects",([
            __DIR__"npc/jiaotu" : 2,
        ]));
        set("item_desc", ([
            "vote": "日月神教，文成武德，澤被蒼生。\n"
        ]) );
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}