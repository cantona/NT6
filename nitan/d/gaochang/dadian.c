// Room: /d/gaochang/dadian.c
// Last Modified by Winder on Jul. 15 2000

inherit ROOM;

void create()
{
        set("short", "高昌大殿");
        set("long", @LONG
這裏就是傳説中埋藏着無數寶藏高昌迷宮的大殿，四壁供的都是泥
塑木雕的佛像。大殿之上有一個大大的龍椅，大堂之上透着一股威嚴，
有一塊大匾，上書：

                ****************
                *              * 
                *   文成武德   *
                *              *
                ****************

東西兩面都是殿堂。
LONG
        );
        set("exits", ([
                "west" : __DIR__"wroom1",
                "east" : __DIR__"eroom1", 
        ]));
        set("no_clean_up", 0);
        set("coor/x", -36500);
        set("coor/y", 10050);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}