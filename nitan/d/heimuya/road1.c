//road1.c 黃土路
// by Xiang

inherit ROOM;

void create()
{
        set("short", "亂石坡");
        set("long", @LONG
這是一處亂石怪異的小山崗，向東北是通往平定州的小路。據說
前方經常有野獸出沒，不可久留。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "northeast" : __DIR__"road2",
            "southwest" : __DIR__"road4",
            "west"  : __DIR__"linjxd1",
            "east"  : __DIR__"dating4",
        ]));
        set("objects",([  
           __DIR__"npc/laozhe" : 1 ,
        ])); 
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}