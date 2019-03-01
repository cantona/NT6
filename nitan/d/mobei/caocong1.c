// Room: /d/mobei/caocong1.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "草叢中");
        set("long", @LONG
西方天邊黑雲重重疊疊的堆積，頭頂卻是一片暗藍色的天空，更無
片雲。西北風一陣緩，一陣急，明月漸至中天，月旁一團黃暈。月光之
下，草叢中露出石板一角。
LONG
        );
        set("no_clean_up", 0);
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 1 */
                "southeast" : __DIR__"hill1",
        ]));
        set("coor/x", -220);
        set("coor/y", 5240);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}