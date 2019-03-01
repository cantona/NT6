//Room: /d/suzhou/hong-damen.c
// by llm 99/06/12

#include <ansi.h>

inherit ROOM;

void create()
{
        set("short", "紅娘莊大門");
        set("long", @LONG
眼前是一座氣勢雄偉的大莊庭，門廊高大、朱牆黃瓦，竟有些與
皇宮相似的味道，只是大門兩邊立的不是麒麟、獅獸，而是笑眯眯的
喜財童子童女，而且大門敞開，任人隨意進入，正中上面一塊巨大的
烏木匾牌
            紅    娘    莊

LONG );
        set("exits", ([
                "west" : "/d/suzhou/canlangting",
                "east" : "/d/suzhou/hong-zoulang",
   ]) );


   set("objects", ([
//           "/d/suzhou/npc/meipo" : 1,
      ]) );
   set("coor/x", 210);
        set("coor/y", -200);
        set("coor/z", 0);
        setup();
   replace_program(ROOM);
}

