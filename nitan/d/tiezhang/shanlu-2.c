// Room: /u/zqb/tiezhang/shanlu-2.c

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
你走在一條崎嶇的山路上，道旁山峯壁立，長草過腰，中間一條羊腸小
路，僅容一人勉強過去。
LONG        );
        set("exits", ([ /* sizeof() == 2 */
  "north" : __DIR__"guangchang.c",
  "south" : __DIR__"shanlu-1.c",
]));
        set("no_clean_up", 0);
   set("objects", ([ /* sizeof() == 3 */
      __DIR__"npc/huiyi" : 2, ]));
        set("outdoors", "tiezhang");

        setup();
        replace_program(ROOM);
}