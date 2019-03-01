//Room: /d/ruzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "紅娘莊大門");
   set("long",
"眼前是一座氣勢雄偉的大莊庭，門廊高大、朱牆黃瓦，竟有些與皇宮\n"
"相似的味道，只是大門兩邊立的不是麒麟、獅獸，而是笑眯眯的喜財童子\n"
"童女，而且大門敞開，任人隨意進入，正中上面一塊巨大的烏木匾牌\n"
HIR"            紅    娘    莊\n"NOR
"\n");
        set("exits", ([
                "west" : __DIR__"nandajie",
                "east" : __DIR__"hong-zoulang",
   ]) );


   set("objects", ([
//           __DIR__"npc/meipo" : 1,
      ]) );
	set("coor/x", -6750);
	set("coor/y", 1850);
	set("coor/z", 0);
	setup();
   replace_program(ROOM);
}