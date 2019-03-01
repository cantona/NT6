// Room: /d/qilian/danshan.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "丹山");
        set("long", @LONG
此地又名裝山，自古以產銅著稱，在嘉峪關西一百八十裡，峰巒高
聳，下有小紅石，可以煉銅，相傳是女蝸補天時撒下。南望山下一條商
路穿過嘉峪關貫通東西。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"yumenguan",
                "southeast" : "/d/xingxiu/jiayuguan",
        ]));
        set("coor/x", -20000);
        set("coor/y", 1000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}