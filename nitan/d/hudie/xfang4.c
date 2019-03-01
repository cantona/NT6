// 廂房 xfang4.c
 
#include <ansi.h>
#include <room.h>

inherit ROOM;

void create() 
{ 
        set("short", "廂房");
        set("long", @LONG
這是一間別致的廂房，推開房門，揭開門簾，但見房內黑沉沉的
宛似夜晚，房間內所有的窗戶都用氈子遮住了，床上的帳簾也關得嚴
嚴實實。看來這裡就是「見死不救」胡青牛休息的地方了。
LONG );

        set("exits", ([
              "out" : __DIR__"caotang",
        ]));

        set("objects",([
            __DIR__"npc/hu" : 1,
        ]));
        set("no_fight",1);

        create_door("out", "竹門", "enter", DOOR_CLOSED);
        setup();
}