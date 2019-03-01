// Room: /d/qilian/jiuquan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "酒泉");
        set("long", @LONG
相傳這裡就是漢大將軍霍去病大破樓蘭後犒軍之地，武帝贈御酒二
十瓶，霍不忍獨享，盡傾于十泉內，與三軍共飲。後聞以酒泉之水釀酒，
香馥可口。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "northeast" : __DIR__"shalu2",
                "southwest" : __DIR__"loulan",
        ]));
        set("coor/x", -20200);
        set("coor/y", 280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}