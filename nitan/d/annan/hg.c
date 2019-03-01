#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short",HIY"安南皇宮"NOR);
  set ("long", @LONG
安南皇宮採用了北京故宮的圖紙，所以你會發現自己進入
了一個縮小版的北京故宮。內有紫禁城，紫禁城裡又分為兩部
分，前面有皇帝平處理政務的勤政殿，後面有皇帝居住的乾成
殿，皇後住的坤泰宮，皇太子居住的光明殿，其他後妃居住的
順輝院等。皇城內還設有旗台、太和殿和祭祀歷代皇帝的宮廣
殿和廟宇。。
LONG);

  set("exits", ([ 
"east":__DIR__"suishilu2",        

       ]));
  set("objects",([
          __DIR__"npc/bing":4,
          ]));

set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
