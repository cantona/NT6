// Room: /d/lingzhou/xidian.c

inherit ROOM;

void create()
{
        set("short", "西偏殿");
        set("long", @LONG
這裡是西偏殿，是皇上上朝是必經之處，朝上議事的時候內侍們就
在這裡候著。地板是白玉舖成，四周是白色的帷幄。東面的走廊通向議
事大殿，西面是一條回廊通向御書房和寢宮，北面的牆上懸著歷代先皇
的畫像，南面是一排落地長窗。幾個內侍肅立，鴉雀無聲。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "west" : __DIR__"yushufang",
                "east" : __DIR__"huilang",
        ]));
        set("objects", ([
                __DIR__"npc/neishi" : 2,
        ]));
        set("coor/x", -6275);
        set("coor/y", 2975);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}