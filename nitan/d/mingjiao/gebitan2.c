//gebitan2.c

inherit ROOM;

void create()
{
        set("short", "戈壁灘");
        set("long", @LONG
眼前是一望無際的戈壁灘，沒有路標，也沒有一個行人，天顯得
很高，遠山披雪，蒼鷹翱翔，走在這茫茫戈壁之上，你似乎迷路了。
LONG );
         set("outdoors", "mingjiao");
        set("exits",([
            "east" : __DIR__"gebitan1",
            "west" : __DIR__"gebitan3",        
            "north" : __DIR__"gebitan2",
            "south" : __DIR__"gebitan2",                                  
        ]));
        set("objects", ([
                __DIR__"obj/xiaohuangshi": random(3),
        ]));
        setup();
        replace_program(ROOM);
}