// Room: /d/jiaxing/Yanyu3.c  煙雨樓頂
// Last Modified by winder on Nov. 17 2000

inherit ROOM;

void create()
{
        set("short", "煙雨樓頂");
        set("long", @LONG
這裡是煙雨樓的樓頂，放眼一片空闊，東西兩湖如鴛鴦交頸，輕煙
拂渚，微雨欲來，曉靄迷蒙，正是歷代文人騷客把酒憑欄、吊古吟詠的
好所在。
LONG );
        set("no_sleep_room",1);
        
        set("exits", ([
            "down"     : __DIR__"yanyu2",
        ]));
        
        set("objects", ([
                //CLASS_D("ouyang")+"/ouyangfeng": 1
        ]));
        set("coor/x", 1520);
        set("coor/y", -1020);
        set("coor/z", 20);
        setup();
}
