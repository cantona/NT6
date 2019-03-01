// Room: /city/kedian4.c
// SMALLFISH 1995/12/04

#include <ansi.h>
#include <room.h>

inherit ROOM;

int is_chat_room() { return 1; }

void create() 
{
        set("short", "天龍殿");
        set("long", @LONG
[1；33m   永  黑  長  巨  他  古  它  古  它  遙  它  遙   永  
眼  成  龍  們  老  的  老  的  遠  的  遠   遠  睛  以  腳 
 全  的  名  的  名  的  名  的   遠  黑  後  底  都  東  字
  東  字  東  字  東   是  頭  是  下  是  方  就  方  就  方
  就  方   龍  發  龍  我  龍  有  叫  有  叫  有  叫  有   
的  黃  的  成  的  一  中  一  黃  一  長  一   傳  皮  傳 
 長  傳  群  國  條  河  條  江  條   人  膚  人      人  人
      龍      河      江[2；37；0m
LONG );

        set("no_fight", 1);
        set("no_steal", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1);

        set("exits", ([
                "up"   : "/d/city/kedian",
        ]));

        setup();

        "/clone/board/kedian_b"->foo();
}