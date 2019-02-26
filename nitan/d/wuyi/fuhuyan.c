// Room: /d/wuyi/fuhuyan.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "伏虎巖");
        set("long", @LONG
伏虎巖又名撞冠石，是五曲和六曲的分界石。其形如虎蹲踞，石壁
上有明代兵部侍郎陳省書勒“伏虎”二字。相傳古時此處羣虎為惡，民
不聊生。觀音大士化成人身，收降羣虎，並以楊柳瓶鎮住最後一隻雌虎。
如今，在二曲仙榜巖上，瓶虎栩栩如在。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "east"  : __DIR__"yunwo",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1350);
        set("coor/y", -5010);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
