#include <ansi.h>
inherit ROOM;

#define JOBNAME "安南"

void create ()
{
  set ("short","鹽局");
  set ("long", @LONG
這裡是安南的鹽局，總管安南的鹽運。但是由于戰亂，民間販賣私
鹽的事情屢禁不止，所以鹽局的生意並不是很好。進來官府征召一些人
力來運鹽，但是還要防止有人半路搶劫鹽車，所以來應召的大部分都是
武林中的人物。只見一個鹽局的官差威風凜凜地站在那裡，不時有人從
他那裡領走鹽車朝外走去。
LONG);

  set("exits", ([ 
 "south":__DIR__"xijie2",
       ]));
  set("job_name",JOBNAME);
  set("valid_startroom", 1);
  setup();
 
}
