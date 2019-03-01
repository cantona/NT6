#include <ansi.h>
#include <room.h>
inherit RIVER;

void create()
{
          set ("short", "中州渡");
          set ("long", @LONG
這是通往揚州城的渡口，前面就是滾滾長江 (river)，濁
流滾滾，萬舟競發。兩岸渡船來來往往。向南通過中州大橋徑
直走就是中州府了。
LONG);
        set("arrive_room", "/d/zhongzhou/yangzhoudu");
          set("exits", ([
                  "south" : __DIR__"dukoulu",
        ]));
        set("resource/fish", ({ "/clone/fish/liyu",
                                "/clone/fish/jiyu",
                                "/clone/fish/qingyu",
                                "/clone/fish/caoyu", }));

          set("outdoors", "zhongzhou");
        set("coor/x", -150);
        set("coor/y", 70);
        set("coor/z", 10);
        setup();
        replace_program(RIVER);
}