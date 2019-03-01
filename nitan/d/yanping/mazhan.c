// /d/yanping/mazhan.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short","馬站");
        set("long",@LONG
這個馬站只為朝廷公文傳遞和官員接送，對老百姓和江湖人物卻恕
不接待了。所以，雖然這裡也有飯食，你卻只有幹挨額的份。由此往東
南，是通往福州的官道，北面馬廄有驛馬可以直達中原揚州，西邊渡過
浮橋，就是延平府城了。
LONG);
        set("outdoors", "yanping");
        set("no_fight", "1");
        set("no_beg", "1");
        set("exits", ([
                "north" : __DIR__"majiu",
                "south" : __DIR__"guandao3",
                "westdown"  : __DIR__"fuqiao1",
        ]));
        set("objects", ([
                __DIR__"npc/yibing": 1,
        ]));
        set("coor/x", 1550);
        set("coor/y", -6170);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}