//gebitan1.c

inherit ROOM;

void create()
{
        set("short", "戈壁灘");
        set("long", @LONG
終於穿出了密林，眼前是一望無際的戈壁灘，沒有路標，也沒有
一個行人，天顯得很高，遠山披雪，蒼鷹翱翔，好一派不同於中土的
異域風光。不遠處，幾隻白骨散落地上，似乎是犛牛的屍骨。走在這
茫茫戈壁之上，你似乎迷路了。
LONG );
         set("outdoors", "mingjiao");
         set("exits",([
                      "east" : __DIR__"westroad2",
                      "west" : __DIR__"gebitan2",        
                      "north" : __DIR__"gebitan1",
                      "south" : __DIR__"gebitan1",                                  
        ]));
        set("objects",([
                __DIR__"obj/shigu":3,        
                __DIR__"obj/xiaohuangshi": random(3),
        ]));
        setup();
        replace_program(ROOM);
}