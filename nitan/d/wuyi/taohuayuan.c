// Room: /d/wuyi/taoyuan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "桃花源");
        set("long", @LONG
過了石門，豁然開朗，“到此已非塵世客，過來便是桃源人”。只
見四周群巒環繞，田疇平曠，阡陌縱橫，屋舍儼然，桃花盛開，燦若雲
霞。屋舍邊翠竹叢叢，裊娜搖曳，引人入勝。宋代陳石堂、吳正理皆在
此避世隱居。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "out" : __DIR__"taoyuandong",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1370);
        set("coor/y", -4970);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
