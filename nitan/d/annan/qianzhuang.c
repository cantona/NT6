inherit ROOM;


void create ()
{
  set ("short","安南錢莊");
  set ("long", @LONG
這裏是安南的錢莊。這裏的信譽很好，有很多人來這裏存錢。老闆
正在那裏打着算盤，夥計在門前熱情地招呼着客人。
LONG);

  set("exits", ([ 

 "south":__DIR__"dongjie2",
      ]));
 
  set("objects",([
          __DIR__"npc/wu":1,
          ]));
  
  set("valid_startroom", 1);
  setup();
 
}
