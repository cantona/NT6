// Room: /d/mobei/caocong.c
// Last Modified by winder on May. 25 2001

inherit ROOM;

void create()
{
        set("short", "草叢中");
        set("long", @LONG
西方天邊黑雲重重疊疊的堆積，頭頂卻是一片暗藍色的天空，更無
片雲。西北風一陣緩，一陣急，明月漸至中天，月旁一團黃暈。月光之
下，草叢中三堆白色的東西，模樣甚是詭奇。
LONG
        );
        set("objects", ([ /* sizeof() == 1 */
                __DIR__"npc/obj/baigu" : 3,
        ]));
        set("outdoors","mobei");
        set("exits", ([ /* sizeof() == 1 */
                "west" : __DIR__"hill1",
        ]));
        set("coor/x", -200);
        set("coor/y", 5230);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}