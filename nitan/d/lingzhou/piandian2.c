// Room: /d/lingzhou/piandian2.c

inherit ROOM;

void create()
{
        set("short", "偏殿");
        set("long", @LONG
這裏是皇上寢宮邊的偏殿，是侍衞們值班時休息的地方, 同樣也不
大，但擺了好幾張桌子，椅子卻不多。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"qingong.c",
                "south" : __DIR__"yushufang",
        ]));
        set("objects", ([
                __DIR__"npc/shiwei" : 3,
        ]));
        set("coor/x", -6285);
        set("coor/y", 2985);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}