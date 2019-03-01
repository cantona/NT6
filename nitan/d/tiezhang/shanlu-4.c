// Room: /u/zqb/tiezhang/shanlu-4.c

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條崎嶇的山路上，道旁山峰壁立，長草過腰，中間一條羊腸小
路，僅容一人勉強過去。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "southdown" : __DIR__"shanlu-3",
  "northup" : __DIR__"pingtai",
]));
        set("no_clean_up", 0);
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}