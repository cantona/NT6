// Room: /d/yanping/yidao2.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "閩浙驛道");
        set("long", @LONG
自古入閩無敞途。往來貨運全靠肩挑背扛，逶迤入閩，車馬不通。
古驛道沿建溪溪流南下，經此一個高坡逶迤而上，眼前林海如浪，遠處
雲霧籠罩，好一個風光所在。站在山頂隘口，遠眺延平街市，雙溪拱饒
直如棋盤一般。
LONG );
        set("exits", ([
                "northdown" : __DIR__"yidao1",
                "southup"   : __DIR__"gubao",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        set("coor/x", 1500);
        set("coor/y", -6100);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}