// Room: /d/yueyang/xijiaochi.c
// Last Modifyed by Winder on Dec. 4 2001

inherit ROOM;

void create()
{
        set("short", "洗腳池");
        set("long", @LONG
仙人洗腳池在龍口東邊巖下，為整塊石頭凹下而成，傳說八仙之一
的呂洞賓曾在此洗腳。雨天積水，池底綠苔清新可人。
LONG );
        set("outdoors", "dongting");
        set("no_clean_up", 0);
        set("exits", ([
                "northup" : __DIR__"langyinting",
        ]));
        set("coor/x", -1690);
        set("coor/y", 2280);
        set("coor/z", -20);
        setup();
        replace_program(ROOM);
}